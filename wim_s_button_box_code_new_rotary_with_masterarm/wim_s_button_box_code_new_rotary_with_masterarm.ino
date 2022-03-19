#define ENABLE_PULLUPS
#include <Keypad.h>
#include <Joystick.h>
#include <RotaryEncoder.h>

//DEFINITIONS
#define NUMROTARIES 6 //replace "?" with number of rotary encoders you are using
#define NUMBUTTONS 19 //replace "?"with number of buttong you are using
#define NUMROWS 3     //replace "?" with number of rows you have
#define NUMCOLS 6     //replace "?" with number of columns you have
#define NUMAUXPINS 2
#define ROTARY_DELAY 25

// //JOYSTICK SETTINGS
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK,
                   32, //number of buttons
                   0,  //number of hat switches
                   //Set as many axis to "true" as you have potentiometers for
                   false,  // y axis
                   false,  // x axis
                   false,  // z axis
                   false,  // rx axis
                   false,  // ry axis
                   false,  // rz axis
                   false,  // rudder
                   false,  // throttle
                   false,  // accelerator
                   false,  // brake
                   false); // steering wheel

const int numReadings = 55;

int readings[numReadings]; // the readings from the analog input
int readIndex = 0;         // the index of the current reading

//BUTTON MATRIX BUTTON NUMBERS
//first change number of rows and columns to match your button matrix,
//then replace all "?" with numbers (starting from 0)
byte buttons[NUMROWS][NUMCOLS] = {
    {0, 1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10, 11},
    {12, 13, 14, 15, 16, 17}};
//BUTTON MATRIX 1 PIN MAPPING
byte rowPins[NUMROWS] = {8, 9, 10};         //change "?" to the pins the rows of your button matrix are connected to
byte colPins[NUMCOLS] = {1, 2, 3, 4, 5, 6}; //change "?" to the pins the rows of your button matrix are connected to


#define NUM_LATCHED_BUTTONS 0
char latchedButtons[NUM_LATCHED_BUTTONS] = {};
int latchedStates[NUMBUTTONS];

Keypad buttbx = Keypad(makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

void latched_init()
{
  for (int i = 0; i < NUMBUTTONS; i++)
  {
    latchedStates[i] = 0;
  }
}

void CheckAllButtons(Keypad& box)
{
  if (box.getKeys() && box.keyStateChanged())
  {
    for (int i = 0; i < LIST_MAX; i++)
    {
      if (box.key[i].stateChanged)
      {
        bool isLatchedButton = false;
        for (int lb = 0; lb < NUM_LATCHED_BUTTONS; lb++)
        {
          if (latchedButtons[lb] == box.key[i].kchar)
          {
            isLatchedButton = true;
          }
        }
        if (isLatchedButton)
        {
          if (box.key[i].kstate == RELEASED)
          {
            latchedStates[i] = latchedStates[i] ? 0 : 1;
            Joystick.setButton(box.key[i].kchar, latchedStates[i]);
          }
        }
        else
        {
          switch (box.key[i].kstate)
          {
          // case HOLD:
          case PRESSED:
            Joystick.setButton(box.key[i].kchar, 1);
            break;
          // case IDLE:
          case RELEASED:
            Joystick.setButton(box.key[i].kchar, 0);
            break;
          }
        }
      }
    }
  }
}

struct rotariesdef
{
  int pin1;
  int pin2;
  int ccwchar;
  int cwchar;
  long state;
  RotaryEncoder *rotary;
};

// //ROTARY ENCODERS
// //each line controls a different rotary encoder
// //the first two numbers refer to the pins the encoder is connected to
// //the second two are the buttons each click of the encoder wil press
// //do NOT exceed 31 for the final button number
rotariesdef rotaries[NUMROTARIES]{
    {22, 23, 20, 21}, //rotary 1 (pin1, pin2, ccw, cw, initialState)
    {24, 25, 22, 23},
    {26, 27, 24, 25},
    {28, 29, 26, 27},
    {30, 31, 28, 29},
    {32, 33, 30, 31},
};

void handleInterrupt0()
{
  rotaries[0].rotary->tick();
}

void handleInterrupt1()
{
  rotaries[1].rotary->tick();
}

void handleInterrupt2()
{
  rotaries[2].rotary->tick();
}

void handleInterrupt3()
{
  rotaries[3].rotary->tick();
}

void handleInterrupt4()
{
  rotaries[4].rotary->tick();
}

void handleInterrupt5()
{
  rotaries[5].rotary->tick();
}

void handleInterrupt6()
{
  rotaries[6].rotary->tick();
}

void rotary_init()
{
  for (int i = 0; i < NUMROTARIES; i++)
  {
    rotaries[i].rotary = new RotaryEncoder(rotaries[i].pin1, rotaries[i].pin2, RotaryEncoder::LatchMode::FOUR3);
    rotaries[i].state = 0;
  }

  attachInterrupt(digitalPinToInterrupt(rotaries[0].pin1), handleInterrupt0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaries[0].pin2), handleInterrupt0, CHANGE);

  attachInterrupt(digitalPinToInterrupt(rotaries[1].pin1), handleInterrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaries[1].pin2), handleInterrupt1, CHANGE);

  attachInterrupt(digitalPinToInterrupt(rotaries[2].pin1), handleInterrupt2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaries[2].pin2), handleInterrupt2, CHANGE);

  attachInterrupt(digitalPinToInterrupt(rotaries[3].pin1), handleInterrupt3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaries[3].pin2), handleInterrupt3, CHANGE);

  attachInterrupt(digitalPinToInterrupt(rotaries[4].pin1), handleInterrupt4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaries[4].pin2), handleInterrupt4, CHANGE);

  attachInterrupt(digitalPinToInterrupt(rotaries[5].pin1), handleInterrupt5, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaries[5].pin2), handleInterrupt5, CHANGE);
}

void CheckAllEncoders(void)
{
  for (int i = 0; i < NUMROTARIES; i++)
  {
    long newPos = rotaries[i].rotary->getPosition();
    if (rotaries[i].state != newPos)
    {
      int direction = (int)(rotaries[i].rotary->getDirection());

    //   Serial.print("state:");
    //   Serial.print(rotaries[i].state);
    //   Serial.print(" pos:");
    //   Serial.print(newPos);
    //   Serial.print(" dir:");
    //   Serial.println(direction);

      if (direction < 0)
      {
        PulseJoyButton(rotaries[i].ccwchar, ROTARY_DELAY);
      }
      if (direction > 0)
      {
        PulseJoyButton(rotaries[i].cwchar, ROTARY_DELAY);
      }
      rotaries[i].state = newPos;
    }
  }
}

bool prevArmState = false;
bool curArmState = false;


void handleArmHotInterrupt()
{
  curArmState = true;
}

void handleArmColdInterrupt()
{
  curArmState = false;
}

void init_masterArm(){
  attachInterrupt(digitalPinToInterrupt(52), handleArmHotInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(53), handleArmColdInterrupt, RISING);
}

void CheckMasterArm(){
  if(curArmState != prevArmState){ 
    if(prevArmState == 0){
      PulseJoyButton(18, 50);
    } else {
      PulseJoyButton(19, 50);
    }
    prevArmState = curArmState;
  }
}

void PulseJoyButton(int key, int msDelay){
  Joystick.setButton(key, 1);
  delay(msDelay);
  Joystick.setButton(key, 0);
  delay(msDelay);
}

void setup()
{
  Joystick.begin();
  rotary_init();
  latched_init();
  init_masterArm();

  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    readings[thisReading] = 0;
  }
  Serial.begin(115200);
}

void loop()
{
  CheckAllEncoders();
  CheckAllButtons(buttbx);
  CheckMasterArm();
}
