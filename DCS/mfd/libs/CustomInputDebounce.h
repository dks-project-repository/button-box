#include <InputDebounce.h>

namespace CustomInputDebounce {
// const unsigned long BUTTON_DEBOUNCE_DELAY 20 // [ms]
// class MyInputDebounce : InputDebounce
// {
// public:
//   MyInputDebounce(int8_t pinIn = -1, unsigned long debDelay = DEFAULT_INPUT_DEBOUNCE_DELAY,
//   PinInMode pinInMode = PIM_INT_PULL_UP_RES, unsigned long pressedDuration = 0)
//       : InputDebounce(pinIn, debDelay, pinInMode, pressedDuration), _pinLED(-1)
//   {
//   }
//   virtual ~MyInputDebounce()
//   {
//   }
//   void setPinLED(int8_t pinLED)
//   {
//     _pinLED = pinLED;
//   }

// protected:
//   virtual void pressed()
//   {
//     // handle pressed state
//     if (_pinLED >= 0)
//     {
//       digitalWrite(_pinLED, HIGH); // turn the LED on
//     }
//     Serial.print("HIGH (pin: ");
//     Serial.print(getPinIn());
//     Serial.println(")");
//   }
//   virtual void released()
//   {
//     // handle released state
//     if (_pinLED >= 0)
//     {
//       digitalWrite(_pinLED, LOW); // turn the LED off
//     }
//     Serial.print("LOW (pin: ");
//     Serial.print(getPinIn());
//     Serial.println(")");
//   }
//   virtual void pressedDuration(unsigned long duration)
//   {
//     // handle still pressed state
//     Serial.print("HIGH (pin: ");
//     Serial.print(getPinIn());
//     Serial.print(") still pressed, duration ");
//     Serial.print(duration);
//     Serial.println("ms");
//   }
//   virtual void releasedDuration(unsigned long duration)
//   {
//     // handle released state
//     Serial.print("LOW (pin: ");
//     Serial.print(getPinIn());
//     Serial.print("), duration ");
//     Serial.print(duration);
//     Serial.println("ms");
//   }

// private:
//   int8_t _pinLED;
// };
}  // namespace CustomInputDebounce
