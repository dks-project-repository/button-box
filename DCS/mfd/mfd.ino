#include <InputDebounce.h>
#include <Joystick.h>

#include "libs/CustomInputs.h"

#define JOYSTICK_BASE_ADDRESS 0x0A

#define JOYSTICK_COUNT 4
Joystick_ joy[JOYSTICK_COUNT] = {
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x00, JOYSTICK_TYPE_JOYSTICK, 128, 0),
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x01, JOYSTICK_TYPE_JOYSTICK, 128, 0),
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x02, JOYSTICK_TYPE_JOYSTICK, 128, 0),
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x03, JOYSTICK_TYPE_JOYSTICK, 128, 0),
};
Joystick_* activeJoystick = &joy[1];

void handlePress(uint8_t button) {
	activeJoystick->pressButton(button);
}
void handleRelease(uint8_t button) {
	activeJoystick->releaseButton(button);
}
void handleMomentaryPress(uint8_t button) {
	handlePress(button);
	delay(16);
	handleRelease(button);
	delay(1);
}

#define NUM_ROTARIES 4
CustomInputs::RotaryEncoder rotaries[NUM_ROTARIES] = {
		CustomInputs::RotaryEncoder(0, 1, handleMomentaryPress, 21, 22),
		CustomInputs::RotaryEncoder(3, 4, handleMomentaryPress, 23, 24),
		CustomInputs::RotaryEncoder(8, 9, handleMomentaryPress, 25, 26),
		CustomInputs::RotaryEncoder(11, 12, handleMomentaryPress, 27, 28),
};

#define NUM_BUTTONS 20
CustomInputs::Button buttons[NUM_BUTTONS] = {
		//TOP:
		CustomInputs::Button(34, handlePress, handleRelease, 1),
		CustomInputs::Button(36, handlePress, handleRelease, 2),
		CustomInputs::Button(38, handlePress, handleRelease, 3),
		CustomInputs::Button(40, handlePress, handleRelease, 4),
		CustomInputs::Button(42, handlePress, handleRelease, 5),
		// RIGHT:
		CustomInputs::Button(35, handlePress, handleRelease, 6),
		CustomInputs::Button(37, handlePress, handleRelease, 7),
		CustomInputs::Button(39, handlePress, handleRelease, 8),
		CustomInputs::Button(41, handlePress, handleRelease, 9),
		CustomInputs::Button(43, handlePress, handleRelease, 10),
		// BOTTOM:
		CustomInputs::Button(44, handlePress, handleRelease, 11),
		CustomInputs::Button(46, handlePress, handleRelease, 12),
		CustomInputs::Button(48, handlePress, handleRelease, 13),
		CustomInputs::Button(50, handlePress, handleRelease, 14),
		CustomInputs::Button(52, handlePress, handleRelease, 15),
		// LEFT:
		CustomInputs::Button(45, handlePress, handleRelease, 16),
		CustomInputs::Button(47, handlePress, handleRelease, 17),
		CustomInputs::Button(49, handlePress, handleRelease, 18),
		CustomInputs::Button(51, handlePress, handleRelease, 19),
		CustomInputs::Button(53, handlePress, handleRelease, 20),
};

void setup() {
	// Serial.begin(250000);
	for (int j = 0; j < JOYSTICK_COUNT; j++) {
		joy[j].begin();
	}
}

void loop() {
	for (int r = 0; r < NUM_ROTARIES; r++) {
		rotaries[r].pollInput();
	}

	unsigned long now = millis();
	for (int b = 0; b < NUM_BUTTONS; b++) {
		buttons[b].process(now);
	}
}
