//* main
#include "fileManager.h"
#include "other.h"
#include "singleton.h"

Singleton* Singleton ::instancePtr = NULL; // Place this above setup() for global scope
FileManager waterBot; // FileManager inherits WATER_waterBot

void setup()
{
    Serial.begin(115200);
    waterBot.mountLFS(); //* Return message to app if failed?
    delay(5000);

    waterBot.testWaterData();
}

void loop()
{
    // put your main code here, to run repeatedly:
}