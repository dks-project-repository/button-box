#include <InputDebounce.h>
#include <Joystick.h>

#include "libs/CustomInputs.h"

#define JOYSTICK_BASE_ADDRESS 0x0A

enum Mode {
	Base = 0,
	Left = 1,
	Right = 2,
	Bottom = 3
};

#define JOYSTICK_COUNT 4
Joystick_ joy[JOYSTICK_COUNT] = {
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x00, JOYSTICK_TYPE_JOYSTICK, 128, 0),	// BASE JOYSTICK (doesn't change with mode)
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x01, JOYSTICK_TYPE_JOYSTICK, 128, 0),	// RIGHT MFD
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x02, JOYSTICK_TYPE_JOYSTICK, 128, 0),	// LEFT MFD
		Joystick_(JOYSTICK_BASE_ADDRESS + 0x03, JOYSTICK_TYPE_JOYSTICK, 128, 0),	// BOTTOM MFD
};
uint8_t activeJoystick = Mode::Right;
void handleChangeMode(uint8_t mode) {
	activeJoystick = mode;
}

void doNothing(uint8_t mode) {}

/*BASE JOYSTICK FUNCTIONS*/
void handleBasePress(uint8_t button) {
	joy[Mode::Base].pressButton(button);
}
void handleBaseRelease(uint8_t button) {
	joy[Mode::Base].releaseButton(button);
}
void handleBaseMomentaryPress(uint8_t button) {
	joy[Mode::Base].pressButton(button);
	delay(16);
	joy[Mode::Base].releaseButton(button);
	delay(1);
}

/*DYNAMIC MFD FUNCTIONS*/
void handleDynamicPress(uint8_t button) {
	joy[activeJoystick].pressButton(button);
}
void handleDynamicRelease(uint8_t button) {
	joy[activeJoystick].releaseButton(button);
}
void handleMfdMomentaryPress(uint8_t button) {
	handleDynamicPress(button);
	delay(16);
	handleDynamicRelease(button);
	delay(1);
}

#define NUM_BUTTONS 40
CustomInputs::Button buttons[NUM_BUTTONS] = {
		/**********BASE JOYSTICK BUTTON**********/
		/*MODE BUTTONS*/
		CustomInputs::Button(2, handleChangeMode, doNothing, Mode::Left),			// TOP LEFT
		CustomInputs::Button(5, handleChangeMode, doNothing, Mode::Right),		// TOP RIGHT
		CustomInputs::Button(10, handleChangeMode, doNothing, Mode::Bottom),	// BOTTOM RIGHT
		CustomInputs::Button(13, handleChangeMode, doNothing, Mode::Bottom),	// BOTTOM LEFT

		/*ARMING PANEL*/
		CustomInputs::Button(A8, handleBasePress, handleBaseRelease, 0),	 // Master Mode AA
		CustomInputs::Button(A9, handleBasePress, handleBaseRelease, 1),	 // Master Mode AG
		CustomInputs::Button(A10, handleBasePress, handleBaseRelease, 2),	 // Master Arm SAFE
		CustomInputs::Button(A11, handleBasePress, handleBaseRelease, 3),	 // Master Arm ARM

		/*SOFT KEYS*/
		CustomInputs::Button(22, handleBasePress, handleBaseRelease, 4),	// Option Select PB 1
		CustomInputs::Button(24, handleBasePress, handleBaseRelease, 5),	// Option Select PB 2
		CustomInputs::Button(26, handleBasePress, handleBaseRelease, 6),	// Option Select PB 3
		CustomInputs::Button(28, handleBasePress, handleBaseRelease, 7),	// Option Select PB 4
		CustomInputs::Button(30, handleBasePress, handleBaseRelease, 8),	// Option Select PB 5

		/*UFC*/
		CustomInputs::Button(A0, handleBasePress, handleBaseRelease, 9),	 // AP
		CustomInputs::Button(A1, handleBasePress, handleBaseRelease, 10),	 // IFF
		CustomInputs::Button(A2, handleBasePress, handleBaseRelease, 11),	 // TCN
		CustomInputs::Button(A3, handleBasePress, handleBaseRelease, 12),	 // ILS
		CustomInputs::Button(A4, handleBasePress, handleBaseRelease, 13),	 // DL
		CustomInputs::Button(A5, handleBasePress, handleBaseRelease, 14),	 // BCN
		CustomInputs::Button(A6, handleBasePress, handleBaseRelease, 15),	 // ON OFF

		/**********MFD BUTTONS**********/
		/*TOP PBs*/
		CustomInputs::Button(34, handleDynamicPress, handleDynamicRelease, 0),	// PB6
		CustomInputs::Button(36, handleDynamicPress, handleDynamicRelease, 1),	// PB7
		CustomInputs::Button(38, handleDynamicPress, handleDynamicRelease, 2),	// PB8
		CustomInputs::Button(40, handleDynamicPress, handleDynamicRelease, 3),	// PB9
		CustomInputs::Button(42, handleDynamicPress, handleDynamicRelease, 4),	// PB10
		/*RIGHT PBs*/
		CustomInputs::Button(35, handleDynamicPress, handleDynamicRelease, 5),	// PB11
		CustomInputs::Button(37, handleDynamicPress, handleDynamicRelease, 6),	// PB12
		CustomInputs::Button(39, handleDynamicPress, handleDynamicRelease, 7),	// PB13
		CustomInputs::Button(41, handleDynamicPress, handleDynamicRelease, 8),	// PB14
		CustomInputs::Button(43, handleDynamicPress, handleDynamicRelease, 9),	// PB15
		/*BOTTOM PBs*/
		CustomInputs::Button(44, handleDynamicPress, handleDynamicRelease, 10),	 // PB16
		CustomInputs::Button(46, handleDynamicPress, handleDynamicRelease, 11),	 // PB17
		CustomInputs::Button(48, handleDynamicPress, handleDynamicRelease, 12),	 // PB18
		CustomInputs::Button(50, handleDynamicPress, handleDynamicRelease, 13),	 // PB19
		CustomInputs::Button(52, handleDynamicPress, handleDynamicRelease, 14),	 // PB20
		/*LEFT PBs*/
		CustomInputs::Button(45, handleDynamicPress, handleDynamicRelease, 15),	 // PB1
		CustomInputs::Button(47, handleDynamicPress, handleDynamicRelease, 16),	 // PB2
		CustomInputs::Button(49, handleDynamicPress, handleDynamicRelease, 17),	 // PB3
		CustomInputs::Button(51, handleDynamicPress, handleDynamicRelease, 18),	 // PB4
		CustomInputs::Button(53, handleDynamicPress, handleDynamicRelease, 19),	 // PB5
};

#define NUM_ROTARIES 4
CustomInputs::RotaryEncoder rotaries[NUM_ROTARIES] = {
		/**********UFC ROTARIES**********/
		CustomInputs::RotaryEncoder(0, 1, handleBaseMomentaryPress, 16, 17),	// TOP LEFT
		CustomInputs::RotaryEncoder(3, 4, handleBaseMomentaryPress, 18, 19),	// TOP RIGHT
		/**********MFD ROTARIES**********/
		CustomInputs::RotaryEncoder(8, 9, handleMfdMomentaryPress, 20, 21),		 // BOTTOM RIGHT (MFD)
		CustomInputs::RotaryEncoder(11, 12, handleMfdMomentaryPress, 22, 23),	 // BOTTOM LEFT (MFD)
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
