#include "HLK_LD1115.h"
//#include <SoftwareSerial.h>

#define ld1115_rx 14
#define ld1115_tx 27

HLK_LD1115 ld1115(ld1115_rx, ld1115_tx, &Serial1);
//HLK_LD1115 ld1115(&Serial2);

void setup() {
  Serial.begin(115200);
  ld1115.begin();
  ld1115.setTh1(130);
  ld1115.setTh2(250);
  ld1115.setThIn(300);
  ld1115.setOutputMode(false);
  ld1115.setTons(30);
  ld1115.setUtons(100);
  ld1115.saveAllSettings();
}

void loop() {

  ld1115.getAllSettings();

  Serial.print("th1: ");
  Serial.println(ld1115.getTh1());
  Serial.print("th2: ");
  Serial.println(ld1115.getTh2());
  Serial.print("th_in: ");
  Serial.println(ld1115.getThIn());
  Serial.print("output_mode: ");
  Serial.println(ld1115.getOutputMode());
  Serial.print("tons: ");
  Serial.println(ld1115.getTons());
  Serial.print("utons: ");
  Serial.println(ld1115.getUtons());
  Serial.println("----------------------------------------");
  
  /*ld1115.read();

  Serial.print(ld1115.getDisType());
  Serial.print(" ");
  Serial.print(ld1115.getOccDis());
  Serial.print(" ");
  Serial.print(ld1115.getMovDis());
  Serial.print(" ");
  Serial.print(ld1115.getOccStr());
  Serial.print(" ");
  Serial.println(ld1115.getMovStr());*/
}
