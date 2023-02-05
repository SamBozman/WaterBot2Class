//* dataManager.h
#pragma once
#include "other.h"

class WATER_DATA {

public:
    struct target_data {
        short int id; // Computer created Target ID
        String name; // User created Water Target 'Name'
        int hp; // Horizontal position
        short int hf; // Horizontal fluctuation -small variations in the horizontal position over time
        int vp; // Vertical Position
        short int vf; // Vertical fluctuation -small variations in the vertical position over time
        int sp; // Spray position – a needle to break up the spray stream
        short int sf; // Spray fluctuation -small variations in the spray needle position over time
        short int rwt; // Relative Watering Time (Certain plants will get more or less)
        bool water; // Do we want the water on or off while traversing to next target?

        bool operator<(const target_data& other) const
        {
            // Sort on hp ID, if they are equal use the id to sort
            if (hp < other.hp)
                return true;
            else if (hp > other.hp)
                return false;
            else
                return id < other.id;
        }
    } s_target_data;
};

class WATER_DATA_MANAGER {
public:
    // Define a sorted set of data elements
    typedef std::set<WATER_DATA::target_data> WATER_DATA_SET;
    WATER_DATA_SET water_data_set; // Create a Data set variable

    // Provide insert and delete access to it
    void testWaterData(); // uesed to test DataManager code :)
    void insert_data(WATER_DATA::target_data& data); // Adds a new data entry
    void delete_data(int id); // Removes the entry by ID if it exists
    void print_all_data(void); // prints the entire data structure
    // void send_data_to_app(void); // Send short Target list to app

private:
};