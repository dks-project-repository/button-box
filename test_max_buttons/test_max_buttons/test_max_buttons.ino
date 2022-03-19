// Program used to test using the Arduino Joystick Library
// to create multiple Joystick objects on a single Arduino
// Leonardo or Arduino Micro.
//
// Each joystick has a unique configuration.
//
// Matthew Heironimus
// 2016-05-13
//------------------------------------------------------------
#include <Joystick.h>

#define JOYSTICK_COUNT 1

Joystick_ Joystick[JOYSTICK_COUNT] = {
  Joystick_(0x01, JOYSTICK_TYPE_JOYSTICK, 128, 0)
};


void setup()
{
  for (int index = 0; index < JOYSTICK_COUNT; index++)
  {
      Joystick[index].begin();
  }
}

void loop()
{ 
}
