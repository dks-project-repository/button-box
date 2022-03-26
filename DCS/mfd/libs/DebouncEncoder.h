#include <Joystick.h>

namespace CustomInputs {

enum StepsPerDetent { ONE_STEP_PER_DETENT = 1, TWO_STEPS_PER_DETENT = 2, FOUR_STEPS_PER_DETENT = 4 };

class RotaryEncoder {
 private:
	Joystick_* joy;
	uint8_t buttonInc_;
	uint8_t buttonDec_;
	// uint8_t val;
	uint8_t pinClk_;
	uint8_t pinData_;
	uint8_t lastState_;
	uint16_t delta_ = 0;

	void momentaryPress(uint8_t button) {
		joy->pressButton(button);
		delay(25);
		joy->releaseButton(button);
		delay(25);
	}

	void init(uint8_t clk, uint8_t data) {
		// void (*callback_)(char state, char* msg);
		pinClk_ = clk;
		pinData_ = data;
		pinMode(pinClk_, INPUT_PULLUP);
		pinMode(pinData_, INPUT_PULLUP);
	}

	void set_buttons(uint8_t buttonInc, uint8_t buttonDec) {
		buttonInc_ = buttonInc;
		buttonDec_ = buttonDec;
	}

	// A vald CW or  CCW move returns 1, invalid returns 0.
	int8_t read_rotary() {
		static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

		lastState_ <<= 2;
		if (digitalRead(pinData_)) lastState_ |= 0x02;
		if (digitalRead(pinClk_)) lastState_ |= 0x01;
		lastState_ &= 0x0f;

		// If valid then store as 16 bit data.
		if (rot_enc_table[lastState_]) {
			delta_ <<= 4;
			delta_ |= lastState_;
			// if (store==0xd42b) return 1;
			// if (store==0xe817) return -1;
			if ((delta_ & 0xff) == 0x2b) return -1;
			if ((delta_ & 0xff) == 0x17) return 1;
		}
		return 0;
	}
	void rotary_tick() {
		if (read_rotary()) {
			if (lastState_ == 0x0b) {
				momentaryPress(buttonInc_);
				Serial.print("eleven ");
				Serial.println(delta_, HEX);
			}

			if (lastState_ == 0x07) {
				momentaryPress(buttonDec_);
				Serial.print("seven ");
				Serial.println(delta_, HEX);
			}
		}
	}

 public:
	void pollInput() { rotary_tick(); }
	void setButtons(uint8_t buttonInc, uint8_t buttonDec) { set_buttons(buttonInc, buttonDec); }
	RotaryEncoder(char pinClk, char pinData, Joystick_& joystick, char buttonInc, char buttonDec) {
		joy = &joystick;
		pinClk_ = pinClk;
		pinData_ = pinData;
		pinMode(pinClk_, INPUT_PULLUP);
		pinMode(pinData_, INPUT_PULLUP);
		set_buttons(buttonInc, buttonDec);
		read_rotary();
	};
};
}	 // namespace CustomInputs