/*
  Tell DCS-BIOS to use a serial connection and use interrupt-driven
  communication. The main program will be interrupted to prioritize
  processing incoming data.
  
  This should work on any Arduino that has an ATMega328 controller
  (Uno, Pro Mini, many others).
 */
// #define DCSBIOS_IRQ_SERIAL
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#include "CustomDcsBios.h"



/* paste code snippets from the reference documentation here */
CustomDcsBios::CallbackSwitch topLeftButton = CustomDcsBios::CallbackSwitch(A15);
CustomDcsBios::CallbackSwitch topRightButton = CustomDcsBios::CallbackSwitch(A12);
CustomDcsBios::CallbackSwitch bottomLeftButton = CustomDcsBios::CallbackSwitch(A7);
CustomDcsBios::CallbackSwitch bottomRightButton = CustomDcsBios::CallbackSwitch(A4);

// CustomDcsBios::RotaryEncoder topLeftKnob = CustomDcsBios::RotaryEncoder("AMPCD_SYM_SW", "DEC", "INC", 31, 33);
// CustomDcsBios::RotaryEncoder topRightKnob = CustomDcsBios::RotaryEncoder("AMPCD_SYM_SW", "DEC", "INC", 30, 32);
CustomDcsBios::RotaryEncoder bottomLeftKnob = CustomDcsBios::RotaryEncoder("RIGHT_DDI_BRT_CTL", "-3200", "+3200", A6, A5);
CustomDcsBios::RotaryEncoder bottomRightKnob = CustomDcsBios::RotaryEncoder("RIGHT_DDI_CONT_CTL", "-3200", "+3200", A3, A2);

CustomDcsBios::CallbackSwitch top01 = CustomDcsBios::CallbackSwitch(44);
CustomDcsBios::CallbackSwitch top02 = CustomDcsBios::CallbackSwitch(46);
CustomDcsBios::CallbackSwitch top03 = CustomDcsBios::CallbackSwitch(48);
CustomDcsBios::CallbackSwitch top04 = CustomDcsBios::CallbackSwitch(50);
CustomDcsBios::CallbackSwitch top05 = CustomDcsBios::CallbackSwitch(52);

CustomDcsBios::CallbackSwitch right01 = CustomDcsBios::CallbackSwitch(34);
CustomDcsBios::CallbackSwitch right02 = CustomDcsBios::CallbackSwitch(36);
CustomDcsBios::CallbackSwitch right03 = CustomDcsBios::CallbackSwitch(38);
CustomDcsBios::CallbackSwitch right04 = CustomDcsBios::CallbackSwitch(40);
CustomDcsBios::CallbackSwitch right05 = CustomDcsBios::CallbackSwitch(42);

CustomDcsBios::CallbackSwitch bottom01 = CustomDcsBios::CallbackSwitch(35);
CustomDcsBios::CallbackSwitch bottom02 = CustomDcsBios::CallbackSwitch(37);
CustomDcsBios::CallbackSwitch bottom03 = CustomDcsBios::CallbackSwitch(39);
CustomDcsBios::CallbackSwitch bottom04 = CustomDcsBios::CallbackSwitch(41);
CustomDcsBios::CallbackSwitch bottom05 = CustomDcsBios::CallbackSwitch(43);

CustomDcsBios::CallbackSwitch left01 = CustomDcsBios::CallbackSwitch(45);
CustomDcsBios::CallbackSwitch left02 = CustomDcsBios::CallbackSwitch(47);
CustomDcsBios::CallbackSwitch left03 = CustomDcsBios::CallbackSwitch(49);
CustomDcsBios::CallbackSwitch left04 = CustomDcsBios::CallbackSwitch(51);
CustomDcsBios::CallbackSwitch left05 = CustomDcsBios::CallbackSwitch(53);




void dcsBiosCallback(char buttonState, char* msg ){
  DcsBios::tryToSendDcsBiosMessage(msg, buttonState == HIGH ? "0" : "1");
}

void topLeftCallback(char buttonState, char* msg){
  if(buttonState == HIGH){
    bottomLeftKnob.setMessage("LEFT_DDI_BRT_CTL");
    bottomRightKnob.setMessage("LEFT_DDI_CONT_CTL");

    top01.setMessage("LEFT_DDI_PB_06");
    top02.setMessage("LEFT_DDI_PB_07");
    top03.setMessage("LEFT_DDI_PB_08");
    top04.setMessage("LEFT_DDI_PB_09");
    top05.setMessage("LEFT_DDI_PB_010");

    right01.setMessage("LEFT_DDI_PB_11");
    right02.setMessage("LEFT_DDI_PB_12");
    right03.setMessage("LEFT_DDI_PB_13");
    right04.setMessage("LEFT_DDI_PB_14");
    right05.setMessage("LEFT_DDI_PB_15");

    bottom01.setMessage("LEFT_DDI_PB_16");
    bottom02.setMessage("LEFT_DDI_PB_17");
    bottom03.setMessage("LEFT_DDI_PB_18");
    bottom04.setMessage("LEFT_DDI_PB_19");
    bottom05.setMessage("LEFT_DDI_PB_20");
    
    left01.setMessage("LEFT_DDI_PB_01");
    left02.setMessage("LEFT_DDI_PB_02");
    left03.setMessage("LEFT_DDI_PB_03");
    left04.setMessage("LEFT_DDI_PB_04");
    left05.setMessage("LEFT_DDI_PB_05");
  }
};



void topRightCallback(char buttonState, char* msg){
  if(buttonState == HIGH){
    bottomLeftKnob.setMessage("RIGHT_DDI_BRT_CTL");
    bottomRightKnob.setMessage("RIGHT_DDI_CONT_CTL");

    top01.setMessage("RIGHT_DDI_PB_06");
    top02.setMessage("RIGHT_DDI_PB_07");
    top03.setMessage("RIGHT_DDI_PB_08");
    top04.setMessage("RIGHT_DDI_PB_09");
    top05.setMessage("RIGHT_DDI_PB_010");

    right01.setMessage("RIGHT_DDI_PB_11");
    right02.setMessage("RIGHT_DDI_PB_12");
    right03.setMessage("RIGHT_DDI_PB_13");
    right04.setMessage("RIGHT_DDI_PB_14");
    right05.setMessage("RIGHT_DDI_PB_15");

    bottom01.setMessage("RIGHT_DDI_PB_16");
    bottom02.setMessage("RIGHT_DDI_PB_17");
    bottom03.setMessage("RIGHT_DDI_PB_18");
    bottom04.setMessage("RIGHT_DDI_PB_19");
    bottom05.setMessage("RIGHT_DDI_PB_20");

    left01.setMessage("RIGHT_DDI_PB_01");
    left02.setMessage("RIGHT_DDI_PB_02");
    left03.setMessage("RIGHT_DDI_PB_03");
    left04.setMessage("RIGHT_DDI_PB_04");
    left05.setMessage("RIGHT_DDI_PB_05");
  }
}

void bottomLeftCallback(char buttonState, char* msg){
  if(buttonState == HIGH){
    // bottomLeftKnob.setMessage("AMPCD_BRT_CTL");
    // bottomRightKnob.setMessage("AMPCD_CONT_CTL");

    top01.setMessage("AMPCD_PB_06");
    top02.setMessage("AMPCD_PB_07");
    top03.setMessage("AMPCD_PB_08");
    top04.setMessage("AMPCD_PB_09");
    top05.setMessage("AMPCD_PB_010");

    right01.setMessage("AMPCD_PB_11");
    right02.setMessage("AMPCD_PB_12");
    right03.setMessage("AMPCD_PB_13");
    right04.setMessage("AMPCD_PB_14");
    right05.setMessage("AMPCD_PB_15");

    
    bottom01.setMessage("AMPCD_PB_16");
    bottom02.setMessage("AMPCD_PB_17");
    bottom03.setMessage("AMPCD_PB_18");
    bottom04.setMessage("AMPCD_PB_19");
    bottom05.setMessage("AMPCD_PB_20");

    left01.setMessage("AMPCD_PB_01");
    left02.setMessage("AMPCD_PB_02");
    left03.setMessage("AMPCD_PB_03");
    left04.setMessage("AMPCD_PB_04");
    left05.setMessage("AMPCD_PB_05");


  }
}

void bottomRightCallback(char buttonState, char* msg){
  bottomLeftCallback(buttonState, msg);
}

void initCallbacks(){
  topRightCallback(HIGH, "");
  topLeftButton.setCallback(topLeftCallback);
  topRightButton.setCallback(topRightCallback);
  bottomRightButton.setCallback(bottomRightCallback);
  bottomLeftButton.setCallback(bottomLeftCallback);
}

void setup() {
  initCallbacks();
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}


