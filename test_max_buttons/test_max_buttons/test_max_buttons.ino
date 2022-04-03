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
    Joystick_(0x0A, JOYSTICK_TYPE_JOYSTICK, 128, 0)};
char pin = A4;

void setup()
{
  Serial.begin(250000);
  for (int index = 0; index < JOYSTICK_COUNT; index++)
  {
    Joystick[index].begin();
  }
  pinMode(pin, INPUT_PULLUP);
}
static bool prevValue = false;
void loop()
{
  bool value = digitalRead(pin);
  if (prevValue != value)
  {
    prevValue = value;
    if (value)
    {
      Serial.println("pressed");
      Joystick[0].pressButton(0);
    }
    else
    {
      Serial.println("released");
      Joystick[0].releaseButton(0);
    }
  }
}
