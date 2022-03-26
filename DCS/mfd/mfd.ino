#include <Joystick.h>

#include "libs/CustomInputDebounce.h"
#include "libs/DebouncEncoder.h"

static Joystick_ joy(0x03, JOYSTICK_TYPE_JOYSTICK, 128, 0);

CustomInputs::RotaryEncoder encoder1(0, 1, joy, 0, 1);
CustomInputs::RotaryEncoder encoder2(3, 4, joy, 2, 3);

void setup() {
	Serial.begin(115200);
	joy.begin();
}

void loop() {
	unsigned long now = millis();
	encoder1.pollInput();
	encoder2.pollInput();
}
