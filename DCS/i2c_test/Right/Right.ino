#include <Wire.h>

#include "libs/CustomInputs.h"
#include "libs/MfdModule.h"

#define REMOTE 0x21
#define SELF 0x02

JoyButtonMessage msg = {};

void press(uint8_t button)
{
    Serial.println("hi");

    msg.mode = Mode::Left;
    msg.button = 31;
    msg.value = State::Pressed;

    Wire.beginTransmission(REMOTE);
    Wire.write((byte *)&msg, sizeof msg);
    Wire.endTransmission();
}

void release(uint8_t button)
{
    Serial.println("bye");

    msg.mode = Mode::Left;
    msg.button = 31;
    msg.value = State::Released;

    Wire.beginTransmission(0x21);
    Wire.write((byte *)&msg, sizeof msg);
    Wire.endTransmission();
    // Wire.beginTransmission(0x21);
    // Wire.write(msg.mode);
    // Wire.write(msg.button);
    // Wire.write(msg.value);
    // Wire.endTransmission();
}

CustomInputs::Button btn1(2, press, release, 1);

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    btn1.begin();
    Wire.beginTransmission(0x21);
    uint8_t busStatus = Wire.endTransmission();
    if (busStatus != 0x00)
    {
        Serial.print("I2C Bus communication problem...!");
        while (1)
            ; // wait for ever
    }
    Serial.println("Slave found!");
}

void loop()
{
    unsigned long now = millis();
    btn1.process(now);
}