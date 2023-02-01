#include "other.h"
#include "dm.h"
#include "sgt.h"

// initializing instancePtr with NULL
Singleton *Singleton ::instancePtr = NULL;

void setup() {
  Serial.begin(115200);
  delay(5000);
  // put your setup code here, to run once:
short int id = 23;
    short int hp = 856;
    String name = "Angel Asian Tree";
    short int vp = 234;
    short int sp = 523;
    short int hf = 5;
    short int vf = 5;
    short int sf = 5;
    short int rwt = 3;
    bool water = true;

    // Sample use of data manager
    WATER_DATA_MANAGER data_manager; // Create a Data Manager variable

    // Add some data
    WATER_DATA::target_data sample_data1 = {1, "Test name 1", 100, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data2 = {2, "Test name 2", 320, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data3 = {3, "Test name 3", 200, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data4 = { 4, "Test name 4", 400, 5, 350, 4, 125, 2, 5, false};
    WATER_DATA::target_data sample_data6 = { id, name, hp, hf, vp, vf, sp, sf, rwt, water };
    //  WATER_DATA::target_data sample_data5;
    //  sample_data5.id = 15;

    data_manager.insert_data(sample_data1);
    data_manager.insert_data(sample_data2);
    data_manager.insert_data(sample_data3);
    data_manager.insert_data(sample_data4);
    data_manager.insert_data(sample_data6);
    //  Print it out, delete one entry and print again
    data_manager.print_all_data();
    data_manager.delete_data(3);
    data_manager.print_all_data();
  
}

void loop() {
  // put your main code here, to run repeatedly:
}