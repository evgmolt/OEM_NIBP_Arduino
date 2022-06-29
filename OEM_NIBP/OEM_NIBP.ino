//Serial  - 0 (RX), 1 (TX)
//Serial1 - 19 (RX), 18 (TX)
#include "TimerOne.h"

const byte CMD_MAN_ON = 0xAC;
const byte CMD_MAN_OFF = 0xAD;

const byte NUM_ECHO = 0;
const byte NUM_SYS = 1;
const byte NUM_DIA = 2;
const byte NUM_CURRENT = 3;
const byte NUM_STATUS = 4;

const byte NUM_SETTINGS = 6;

const byte NUM_ADDINDEX = 7;
const byte NUM_ADDPARAM = 8;

const byte MASK_PULSE = B00100000;

byte OEMResponse[10];
byte AddIndex = 0;
byte Command;
bool ManometerOn;
byte Mask;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Timer1.initialize(1000000); //2 s
  Timer1.attachInterrupt(timerInterrupt);
}

void loop() {
  if (Serial.available() > 0) {
    Command = Serial.read();

    EmulateResponse(Command);

    Serial1.write(Command);
    if (Serial1.available() > 0){
      for (int i = 0; i < Serial1.available() - 1; i++)
      {
        OEMResponse[i] = Serial1.read();
      }
    }
    Serial.write(OEMResponse, sizeof(OEMResponse));
  }
}

void EmulateResponse(byte cmd){
    if (cmd == CMD_MAN_ON) {
      ManometerOn = true;
      OEMResponse[NUM_SETTINGS] = B00010000;
    }
    if (cmd == CMD_MAN_OFF) {
      ManometerOn = false;
      OEMResponse[NUM_SETTINGS] = 0;
    }
    OEMResponse[NUM_ECHO] = Command;
    OEMResponse[NUM_SYS] = random(115,135); //sys
    OEMResponse[NUM_DIA] = random(65,79);   //dia
    OEMResponse[NUM_CURRENT] = 22;  //current
    OEMResponse[NUM_STATUS] = B10000000; 
    if (Mask != 0)
    {
      OEMResponse[NUM_STATUS] |= Mask;
      Mask = 0; 
    }
    OEMResponse[7] = AddIndex;
    AddIndex++;
    if (AddIndex > 7)
    {
      AddIndex = 0;
    }
    if (AddIndex == 7){
      OEMResponse[NUM_ADDPARAM] = random(75, 84); //pulse
    }  
}

void timerInterrupt(){
     Mask = MASK_PULSE;
}
