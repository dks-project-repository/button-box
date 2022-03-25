#include "libs/CustomInputDebounce.h"
#include "libs/DebouncEncoder.h"
#include <Joystick.h>

#define JOYSTICK_COUNT 1

Joystick_ Joystick[JOYSTICK_COUNT] = {
  Joystick_(0x01, JOYSTICK_TYPE_JOYSTICK, 128, 0)
};

CustomInputs::Encoder encoder1 = CustomInputs::Encoder(0, 1);
CustomInputs::Encoder encoder2 = CustomInputs::Encoder(3, 4);

void setup() { Serial.begin(115200); }

void loop() {
  unsigned long now = millis();
  encoder1.rotary_tick();
  encoder2.rotary_tick();

  // delay(1); // [ms]
}