//* main
#include "fileManager.h"
#include "other.h"
#include "singleton.h"

Singleton *Singleton ::instancePtr =
    NULL;             // Place this above setup() for global scope
FileManager waterBot; // FileManager inherits WATER_waterBot

void setup() {
  Serial.begin(115200);
  waterBot.mountLFS(); //* Return message to app if failed?
  delay(5000);

  waterBot.testWaterData();

  // String temp = waterBot.getTargetPath(1);
  String temp(waterBot.getTargetPath(1));
  debug("The string returned is ");
  debugln(temp);
}

void loop() {
  // put your main code here, to run repeatedly:
}