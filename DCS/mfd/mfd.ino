#include <Joystick.h>

#include "libs/CustomInputDebounce.h"
#include "libs/DebouncEncoder.h"

enum MFD {
	Left,
	Right,
	Bottom,
}

static MFD = Right;

Joystick_ Joystick(0x01, JOYSTICK_TYPE_JOYSTICK, 128, 0);

CustomInputs::Encoder encoder1 = CustomInputs::Encoder(0, 1);
CustomInputs::Encoder encoder2 = CustomInputs::Encoder(3, 4);

void handleRotaryInc(){
	Joystick.pressButton(button);
	delay(5);
	Joystick.releaseButton(button);
	delay(5);
};



void handleRotaryDec(){

};

void setup() {
	Serial.begin(115200);
	Joystick.begin();
}

void loop() {
	unsigned long now = millis();
	encoder1.rotary_tick();
	encoder2.rotary_tick();
}