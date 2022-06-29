#include "TimerOne.h";
byte OEM_NIBP_REQUEST = 0xA0;
byte OEMResponse[10];

void setup() {
  Serial.begin(115200);
  Timer1.initialize(2000000); //2 s
  Timer1.attachInterrupt(timerInterrupt);
}

void loop() {
  if (Serial.available() > 0) {
    byte data = Serial.read();
    OEMResponse[0] = data;
    OEMResponse[1] = random(115,135); //sys
    OEMResponse[2] = random(65,79);   //dia
    OEMResponse[3] = random(65,135);  //current
//    for (int i = 1; i < sizeof(OEMResponse); i++) {
//      OEMResponse[i] = i;
//    }
    Serial.write(OEMResponse, sizeof(OEMResponse));
  }

/*  if (Serial1.available() > 0){
    for (int i = 0; i < Serial1.available() - 1; i++)
    {
      OEMResponse[i] = Serial.Read();
    }*/
}

void timerInterrupt(){
}
