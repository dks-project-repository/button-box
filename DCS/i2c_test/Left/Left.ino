#include <Wire.h>

#include "libs/CustomInputs.h"
#include "libs/MfdModule.h"

volatile bool flag = false;
volatile JoyButtonMessage msg = {};

void callback(int cnt)
{
    if (cnt == 3)
    {
        msg.mode = Wire.read();
        msg.button = Wire.read();
        msg.value = Wire.read();
    }
    else
    {
        for (int i = 0; i <= cnt; i++)
        {
            Wire.read();
        }
    }

    flag = true;
}

void setup()
{
    msg.mode = Mode::Left;
    msg.button = 13;
    msg.value = State::Pressed;
    Serial.begin(115200);
    Wire.begin(0x21);
    Wire.onReceive(callback);
}

void loop()
{
    if (flag == true)
    {
        Serial.print(msg.mode);
        Serial.print(msg.button);
        Serial.println(msg.value);
        flag = false;
    }
}