//* dataManager.cpp
#include "dataManager.h"
#include "other.h"

// Insert target_data into the set
void WATER_DATA_MANAGER::insert_data(WATER_DATA::target_data& data)
{
    water_data_set.insert(data);
}

// Remove data from the set based on ID
void WATER_DATA_MANAGER::delete_data(int id)
{

    // Find the element
    auto iter = std::find_if(water_data_set.begin(), water_data_set.end(),
        [id](const WATER_DATA::target_data& d) { return d.id == id; });

    // Erase it if we found a match
    if (iter != water_data_set.end()) {
        water_data_set.erase(iter);
    }
}

// Prints the sorted data
void WATER_DATA_MANAGER::print_all_data()
{
    std::cout << "WATER_DATA:\n";
    for (auto data : water_data_set) {

        debug("ID: ");
        debug(data.id);

        debug(", Name: ");
        debug(data.name);

        debug(", HP: ");
        debug(data.hp);
        debug(", HF: ");
        debug(data.hf);

        debug(", VP: ");
        debug(data.vp);
        debug(", VF: ");
        debug(data.vf);

        debug(", SP: ");
        debug(data.sp);
        debug(", SF: ");
        debug(data.sf);

        debug(", RWT: ");
        debug(data.rwt);

        debug(", WATER: ");
        debug(data.water);
        debugln("");
    }
    debugln("");
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void WATER_DATA_MANAGER::testWaterData() {

  WATER_DATA::target_data sample_data1 = {1, "Test name 1", 100, 5, 350,
                                          4, 125,           2,   5, false};
  WATER_DATA::target_data sample_data2 = {2, "Test name 2", 320, 5, 350,
                                          4, 125,           2,   5, false};
  WATER_DATA::target_data sample_data3 = {3, "Test name 3", 200, 5, 350,
                                          4, 125,           2,   5, false};
  WATER_DATA::target_data sample_data4 = {4, "Test name 4", 400, 5, 350,
                                          4, 125,           2,   5, false};
  WATER_DATA::target_data sample_data5 = {5, "Test name 5", 400, 5, 350,
                                          4, 125,           2,   5, false};

  insert_data(sample_data1);
  insert_data(sample_data2);
  insert_data(sample_data3);
  insert_data(sample_data4);
  insert_data(sample_data5);

  //  Print it out, delete one entry and print again
  print_all_data(); // View data before deletion
  delete_data(5);   // remove sample_data5
  print_all_data(); // View dta after deletion
}