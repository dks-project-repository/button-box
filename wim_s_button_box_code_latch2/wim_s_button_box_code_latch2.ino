#include <Keyboard.h>
#include <Joystick.h>
#include <Keypad.h>

//DEFINITIONS
#define ENABLE_PULLUPS
#define NUMROTARIES 6 //replace "?" with number of rotary encoders you are using
#define NUMBUTTONS 19 //replace "?"with number of buttong you are using
#define NUMROWS 3     //replace "?" with number of rows you have
#define NUMCOLS 6     //replace "?" with number of columns you have

//BUTTON MATRIX
//first change number of rows and columns to match your button matrix,
//then replace all "?" with numbers (starting from 0)
byte buttons[NUMROWS][NUMCOLS] = {
    {0, 1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10, 11},
    {12, 13, 14, 15, 16, 17}};

#define NUM_LATCHED_BUTTONS 0
char latchedButtons[NUM_LATCHED_BUTTONS] = {};
int latchedStates[NUMBUTTONS];

struct rotariesdef
{
  byte pin1;
  byte pin2;
  int ccwchar;
  int cwchar;
  volatile unsigned char state;
};

//ROTARY ENCODERS
//each line controls a different rotary encoder
//the first two numbers refer to the pins the encoder is connected to
//the second two are the buttons each click of the encoder wil press
//do NOT exceed 31 for the final button number
rotariesdef rotaries[NUMROTARIES]{
    {22, 23, 20, 21, 0}, //rotary 1 (pin1, pin2, ccw, cw, state)
    {24, 25, 22, 23, 0}, //rotary 2
    {26, 27, 24, 25, 0}, //rotary 3
    {28, 29, 26, 27, 0}, //rotary 4
    {30, 31, 28, 29, 0}, //rotary 5
    {32, 33, 30, 31, 0}  //rotary 6

};

#define DIR_CCW 0x10
#define DIR_CW 0x20
#define R_START 0x0

#define HALF_STEP

#ifdef HALF_STEP
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
    // R_START (00)
    {R_START_M, R_CW_BEGIN, R_CCW_BEGIN, R_START},
    // R_CCW_BEGIN
    {R_START_M | DIR_CCW, R_START, R_CCW_BEGIN, R_START},
    // R_CW_BEGIN
    {R_START_M | DIR_CW, R_CW_BEGIN, R_START, R_START},
    // R_START_M (11)
    {R_START_M, R_CCW_BEGIN_M, R_CW_BEGIN_M, R_START},
    // R_CW_BEGIN_M
    {R_START_M, R_START_M, R_CW_BEGIN_M, R_START | DIR_CW},
    // R_CCW_BEGIN_M
    {R_START_M, R_CCW_BEGIN_M, R_START_M, R_START | DIR_CCW},
};
#else
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
    // R_START
    {R_START, R_CW_BEGIN, R_CCW_BEGIN, R_START},
    // R_CW_FINAL
    {R_CW_NEXT, R_START, R_CW_FINAL, R_START | DIR_CW},
    // R_CW_BEGIN
    {R_CW_NEXT, R_CW_BEGIN, R_START, R_START},
    // R_CW_NEXT
    {R_CW_NEXT, R_CW_BEGIN, R_CW_FINAL, R_START},
    // R_CCW_BEGIN
    {R_CCW_NEXT, R_START, R_CCW_BEGIN, R_START},
    // R_CCW_FINAL
    {R_CCW_NEXT, R_CCW_FINAL, R_START, R_START | DIR_CCW},
    // R_CCW_NEXT
    {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif

//BUTTON MATRIX PART 2
byte rowPins[NUMROWS] = {8, 9, 10};         //change "?" to the pins the rows of your button matrix are connected to
byte colPins[NUMCOLS] = {1, 2, 3, 4, 5, 6}; //change "?" to the pins the rows of your button matrix are connected to

Keypad buttbx = Keypad(makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

//JOYSTICK SETTINGS
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
int total = 0;             // the running total
int currentOutputLevel = 0;

//POTENTIOMETERS PART 1
//add all the axis' which are enabled above
int zAxis_ = 0;
int RxAxis_ = 0;

const bool initAutoSendState = true;

void CheckAllButtons(void)
{
  if (buttbx.getKeys() && buttbx.keyStateChanged())
  {
    for (int i = 0; i < LIST_MAX; i++)
    {
      if (buttbx.key[i].stateChanged)
      {
        bool isLatchedButton = false;
        for (int lb = 0; lb < NUM_LATCHED_BUTTONS; lb++)
        {
          if (latchedButtons[lb] == buttbx.key[i].kchar)
          {
            isLatchedButton = true;
          }
        }
        if (isLatchedButton)
        {
          if (buttbx.key[i].kstate == RELEASED)
          {
            latchedStates[i] = latchedStates[i] ? 0 : 1;
            Joystick.setButton(buttbx.key[i].kchar, latchedStates[i]);
          }
        }
        else
        {
          switch (buttbx.key[i].kstate)
          {
          case PRESSED:
          case HOLD:
            Joystick.setButton(buttbx.key[i].kchar, 1);
            break;
          case RELEASED:
          case IDLE:
            Joystick.setButton(buttbx.key[i].kchar, 0);
            ;
            break;
          }
        }
      }
    }
  }
}

void rotary_init()
{
  for (int i = 0; i < NUMROTARIES; i++)
  {
    pinMode(rotaries[i].pin1, INPUT);
    pinMode(rotaries[i].pin2, INPUT);
#ifdef ENABLE_PULLUPS
    digitalWrite(rotaries[i].pin1, HIGH);
    digitalWrite(rotaries[i].pin2, HIGH);
#endif
  }
}

void latched_init()
{
  for (int i = 0; i < NUMBUTTONS; i++)
  {
    latchedStates[i] = 0;
  }
}

unsigned char rotary_process(int _i)
{
  unsigned char pinstate = (digitalRead(rotaries[_i].pin2) << 1) | digitalRead(rotaries[_i].pin1);
  rotaries[_i].state = ttable[rotaries[_i].state & 0xf][pinstate];
  return (rotaries[_i].state & 0x30);
}

void CheckAllEncoders(void)
{
  for (int i = 0; i < NUMROTARIES; i++)
  {
    unsigned char result = rotary_process(i);
    if (result == DIR_CCW)
    {
      Joystick.setButton(rotaries[i].ccwchar, 1);
      delay(50);
      Joystick.setButton(rotaries[i].ccwchar, 0);
    };
    if (result == DIR_CW)
    {
      Joystick.setButton(rotaries[i].cwchar, 1);
      delay(50);
      Joystick.setButton(rotaries[i].cwchar, 0);
    };
  }
}

void setup()
{
  Joystick.begin();
  Keyboard.begin();
  rotary_init();
  latched_init();
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    readings[thisReading] = 0;
  }
}

void loop()
{
  // Serial.println("LOOP");
  CheckAllEncoders();
  CheckAllButtons();
}
