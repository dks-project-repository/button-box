#include <InputDebounce.h>

namespace CustomInputs {

enum StepsPerDetent {
	ONE_STEP_PER_DETENT = 1,
	TWO_STEPS_PER_DETENT = 2,
	FOUR_STEPS_PER_DETENT = 4
};

class RotaryEncoder {
 private:
	// Joystick_* joy;
	uint8_t buttonInc_;
	uint8_t buttonDec_;
	// uint8_t val;
	uint8_t pinClk_;
	uint8_t pinData_;
	uint8_t lastState_;
	uint16_t delta_ = 0;

	void (*callback_)(uint8_t button);

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
				callback_(buttonInc_);
				// Serial.print("eleven ");
				// Serial.println(delta_, HEX);
			}

			if (lastState_ == 0x07) {
				callback_(buttonDec_);
				// Serial.print("seven ");
				// Serial.println(delta_, HEX);
			}
		}
	}

 public:
	void pollInput() { rotary_tick(); }
	void setButtons(uint8_t buttonInc, uint8_t buttonDec) {
		set_buttons(buttonInc, buttonDec);
	}
	RotaryEncoder(uint8_t pinClk, uint8_t pinData, void (*callback)(uint8_t button), uint8_t buttonInc, uint8_t buttonDec) {
		callback_ = callback;
		pinClk_ = pinClk;
		pinData_ = pinData;
		pinMode(pinClk_, INPUT_PULLUP);
		pinMode(pinData_, INPUT_PULLUP);
		set_buttons(buttonInc, buttonDec);
		read_rotary();
	};
};

class Button : public InputDebounce {
 private:
	uint8_t pin_;
	uint8_t button_;
	void (*pressed_)(uint8_t button);
	void (*released_)(uint8_t button);
	void init(uint8_t pin, void (*pressed)(uint8_t button), void (*released)(uint8_t button), uint8_t button) {
		pin_ = pin;
		button_ = button;
		pressed_ = pressed;
		released_ = released;
	}
	virtual void pressed() { pressed_(button_); }
	virtual void released() { released_(button_); }

 public:
	void setButton(uint8_t button) { button_ = button; }
	void setCallbacks(void (*pressed)(uint8_t button), void (*released)(uint8_t button)) {
		pressed_ = pressed;
		released_ = released;
	}
	void begin() {
		setup(pin_, 10, PIM_INT_PULL_UP_RES, 0);
	}
	Button(uint8_t pin, void (*pressed)(uint8_t button), void (*released)(uint8_t button), uint8_t button) {
		init(pin, pressed, released, button);
	}
	Button(const Button&);
	Button& operator=(const Button&);
	virtual ~Button() {}
};

// class MyInputDebounce : public InputDebounce {
//  private:
// 	Joystick_* joystick_;
// 	char button_;

//  protected:
// 	virtual void pressed() { joystick_->pressButton(button_); }
// 	virtual void released() { joystick_->releaseButton(button_); }

//  public:
// 	MyInputDebounce(int8_t pin, Joystick_& joystick, char button, unsigned long debDelay = DEFAULT_INPUT_DEBOUNCE_DELAY, PinInMode pinInMode = PIM_INT_PULL_UP_RES, unsigned long pressedDuration = 0)
// 			: InputDebounce(pin, 6, pinInMode, pressedDuration) {
// 		joystick_ = &joystick;
// 		button_ = button;
// 	}
// 	MyInputDebounce(const MyInputDebounce&);
//   	MyInputDebounce& operator=(const MyInputDebounce&);
// 	virtual ~MyInputDebounce() {}
// 	void setButton(char button) { button_ = button; }
// 	void setJoystick(Joystick_& joystick) {joystick_ = &joystick;}
// };

}	 // namespace CustomInputs