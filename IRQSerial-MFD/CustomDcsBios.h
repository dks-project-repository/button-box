#include "DcsBios.h"

namespace CustomDcsBios {
    
    const unsigned long DEBOUNCE_DELAY = 10;

    void dcsBiosCallback(char buttonState, char* msg ){
        DcsBios::tryToSendDcsBiosMessage(msg, buttonState == HIGH ? "0" : "1");
    }

    class CallbackSwitch : DcsBios::PollingInput {
    private:
        void (*callback_)(char state, char* msg);
        char* msg_;
        char pin_;
        char buttonState = digitalRead(pin_);
        char lastButtonState;
        bool reverse_;
        unsigned long lastDebounceTime = 0;
        void init_(char pin, bool reverse = false, char* msg = "") {
			msg_ = msg;
			pin_ = pin;
			pinMode(pin_, INPUT_PULLUP);
			lastButtonState = digitalRead(pin_);
			reverse_ = reverse;
        }
        void pollInput() {
			char reading = digitalRead(pin_);
			if (reverse_) reading = !reading;
			if (reading != lastButtonState) {
				lastDebounceTime = millis();
			}
			if((millis() - lastDebounceTime) > DEBOUNCE_DELAY ){
				if (reading != buttonState) {
				buttonState = reading;
				callback_(buttonState, msg_);
				}
			}
			lastButtonState=reading;
        }
    public:
        void setMessage(char* msg) { msg_ = msg; }
        void setCallback(void (*callback)(char state, char* msg)){ callback_ = callback; }
        CallbackSwitch(char* msg, char pin, bool reverse) { init_(pin, reverse, msg); }
        CallbackSwitch(char* msg, char pin) { init_(pin, false, msg); setCallback(dcsBiosCallback); }
        CallbackSwitch(char pin) { init_(pin); setCallback(dcsBiosCallback); }
    };


    class RotaryEncoder : DcsBios::PollingInput {
		private:
			const char* msg_;
			const char* decArg_;
			const char* incArg_;
			char pinA_;
			char pinB_;
			char lastState_;
			signed char delta_;
			char stepsPerDetent_;
			char readState() {
				return (digitalRead(pinA_) << 1) | digitalRead(pinB_);
			}
			void pollInput() {
				char state = readState();
				switch(lastState_) {
					case 0:
						if (state == 2) delta_--;
						if (state == 1) delta_++;
						break;
					case 1:
						if (state == 0) delta_--;
						if (state == 3) delta_++;
						break;
					case 2:
						if (state == 3) delta_--;
						if (state == 0) delta_++;
						break;
					case 3:
						if (state == 1) delta_--;
						if (state == 2) delta_++;
						break;
				}
				lastState_ = state;
				
				if (delta_ >= stepsPerDetent_) {
					if (DcsBios::tryToSendDcsBiosMessage(msg_, incArg_))
						delta_ -= stepsPerDetent_;
				}
				if (delta_ <= -stepsPerDetent_) {
					if (DcsBios::tryToSendDcsBiosMessage(msg_, decArg_))
						delta_ += stepsPerDetent_;
				}
			}
		public:
            void setMessage(char* msg) { msg_ = msg; }
			RotaryEncoder(const char* msg, const char* decArg, const char* incArg, char pinA, char pinB, DcsBios::StepsPerDetent stepsPerDetent = DcsBios::FOUR_STEPS_PER_DETENT) {
				msg_ = msg;
				decArg_ = decArg;
				incArg_ = incArg;
				pinA_ = pinA;
				pinB_ = pinB;
				stepsPerDetent_ = stepsPerDetent;
				pinMode(pinA_, INPUT_PULLUP);
				pinMode(pinB_, INPUT_PULLUP);
				delta_ = 0;
				lastState_ = readState();
			}
	};
}



