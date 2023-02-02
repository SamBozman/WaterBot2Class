//* main
#include "fileManager.h"
#include "other.h"
#include "singleton.h"

Singleton *Singleton ::instancePtr = NULL; // Place this above setup() for global scope

void setup()
{
    Serial.begin(115200);
    delay(5000);
    // put your setup code here, to run once:
    //FileManager waterBot; //FileManager inherits WATER_waterBot
FileManager waterBot;
    WATER_DATA::target_data sample_data1 = {1, "Test name 1", 100, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data2 = {2, "Test name 2", 320, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data3 = {3, "Test name 3", 200, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data4 = {4, "Test name 4", 400, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data5 = {5, "Test name 5", 400, 5, 350, 4, 125, 2, 5, false};

    waterBot.insert_data(sample_data1);
    waterBot.insert_data(sample_data2);
    waterBot.insert_data(sample_data3);
    waterBot.insert_data(sample_data4);
    waterBot.insert_data(sample_data5);
   
    //  Print it out, delete one entry and print again
    waterBot.print_all_data(); // View data before deletion
    waterBot.delete_data(5);   // remove sample_data5
    waterBot.print_all_data(); // View dta after deletion

    waterBot.testPrint();
   
}

void loop()
{
    // put your main code here, to run repeatedly:
}