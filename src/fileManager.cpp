//*fileManager.cpp
#include "fileManager.h"

#include "other.h"
// initialize variables
String targetPathName = "/TARGET/T";
String maxPathName = "/MAX/";
char path[25] = { 0 }; // path to saved files
char dataBlock[254] = { 0 }; // Variable used to read and write files

//! Create Json file from water target data --------------------------------
void FileManager::makeWaterTarget(short int id, String name, int hp, short int hf, int vp,
    short int vf, int sp, short int sf, short int rwt, bool water)
{
    const int capacity = 256; // Buffer for StaticJsonDocument doc
    StaticJsonDocument<capacity> doc; // Declare StaticJsonDocument doc

    doc["id"] = id; //(Int) ID  for watering target
    doc["name"] = name;
    doc["hp"] = hp; // Horizontal steps from 'Home'
    doc["hf"] = hf; // Horizontal fluctuation for coverage
    doc["vp"] = vp; // Vertical steps from 'Home'
    doc["vf"] = vf; // Vertical fluctuation for coverage
    doc["sp"] = sp; // Spray steps for diffused spray
    doc["sf"] = sf; // Spray fluctuation for diffused spray
    doc["rwt"] = rwt; // Relative watering time (1-5)
    doc["water"] = water; // Turn water off ? (or leave on while moving to next spot)
    // Serialize the Json object and put into variable (output)
    serializeJson(doc, dataBlock);
    // TODO add in error handling for serializeJson function
}

//! Load saved water targets into the data_manager for sorting ------------
void FileManager::loadDataManager()
{
    int numFiles = getNumTargetFiles();
    if (numFiles == 0) {
        debugln("No saved TargetFiles exist!");
    } else {
        for (int i = 1; i < numFiles + 1; i++) { // Run through this code for each target file
            loadTarget(i); // Function to load a saved Target file

            StaticJsonDocument<255> doc; // Deserialize the  Target file in char array 'dataBlock'
            DeserializationError err = deserializeJson(doc, dataBlock);
            if (err) {
                Serial.print(F("deserializeJson() of dataBlock array failed with code "));
                Serial.println(err.f_str());

                //! SEE IF WE CAN USE DATAMANAGER TO HANDLE THESE VARIABLES
            } else {
                short int id = doc["id"]; // Computer created Target ID
                const char* name = doc["name"]; // Name of the Target Position
                int hp = doc["hp"]; // Horizontal position
                int vp = doc["vp"]; // Vertical Position
                int sp = doc["sp"]; // Spray position – a needle to break up the spray stream
                short int hf = doc["hf"]; // Horizontal fluctuation -small variations in the horizontal position over time
                short int vf = doc["vf"]; // Vertical fluctuation -small variations in the vertical position over time
                short int sf = doc["sf"]; // Spray fluctuation -small variations in the spray needle position over time
                short int rwt = doc["rwt"]; // Relative Watering Time (Certain plants will get more or less)
                bool water = doc["water"]; // Do we want the water on or off while traversing to next target?

                String s = "T" + String(i); // Combine 2 strings
                int n = s.length(); // Get length of combined string
                strcpy(path, s.c_str()); // Convert it to a char array

                WATER_DATA::target_data path = { id, name, hp, hf, vp, vf, sp, sf, rwt, water };
                insert_data(path);
            }
        }
        print_all_data(); // Show all data_manager water Targets
    }
}

// Loads target elements from saved target file----------------------------
void FileManager::loadTarget(int id)
{

    setFilePath(targetPathName, id);
    File file = LittleFS.open(path); // Open file
    if (!file || file.isDirectory()) { // Check if file structure is OK
        debugln("- failed to open Target directory for reading");
        return;
    }

    debug("- reading from /TARGET directory file: ");
    debugln(path);

    int x = 0;
    while (file.available()) {
        dataBlock[x] = file.read(); // Read each character
        x++;
    }
    dataBlock[x] = 0; // add a delimiter
    file.close(); // close this Target file
}

// Sets file path for writing a file to flash------------------------------
bool FileManager::setFilePath(String basePathName, int id)
{
    String s = basePathName + String(id); // Combine 2 strings
    if (s.length() <= 24) { // Make sure char path[25] is not overflowing!
        strcpy(path, s.c_str()); // Convert it to a char array
        deleteFile(LittleFS, path);
        return true;
    } else { // char path[25] has overflowed
        debug("Could not delete target. char path overflow!");
        return false;
    }
}

// Start LiitleFS file system. Called from steup() ------------------------
void FileManager::mountLFS()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
        debugln("LittleFS Mount Failed");
    }
}

// Returns # of files in directory ----------------------------------------
int FileManager::listFiles(fs::FS& fs, const char* dirname, uint8_t levels, int numFiles)
{
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        debugln("- failed to open directory");
        return 0;
    }
    if (!root.isDirectory()) {
        debugln(" - not a directory");
        return 0;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            debug("  DIR : ");
            debugln(file.name());
            if (levels) {
                debug("Levels = : ");
                debugln(levels);
                numFiles = listFiles(fs, file.path(), levels - 1, numFiles);
            }
        } else {
            debug("  List-FILE: ");
            debug(file.name());
            debug("\tSIZE: ");
            debugln(file.size());
            numFiles++;
        }
        file = root.openNextFile();
    }

    return numFiles;
}

// Returns 'True' if file is a directory ----------------------------------
bool FileManager::isDir(fs::FS& fs, const char* dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        debugln("- failed to open directory");
        return false;
    }
    if (!root.isDirectory()) {
        debugln(" - not a directory");
        return false;
    } else {
        return true;
    }
}

// Makes a directory using the supplied string ----------------------------
void FileManager::createDir(fs::FS& fs, const char* path)
{
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path)) {
        debugln("Dir created");
    } else {
        debugln("mkdir failed");
    }
}

// Removes an empty directory ---------------------------------------------
void FileManager::removeDir(fs::FS& fs, const char* path)
{
    Serial.printf("Removing Dir: %s\n", path);
    if (fs.rmdir(path)) {
        debugln("Dir removed");
    } else {
        debugln("rmdir failed");
    }
}

// Write a file to a directory --------------------------------------------
void FileManager::writeFile(fs::FS& fs, const char* path, const char* message)
{
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        debugln("- failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        debugln("- file written");
    } else {
        debugln("- write failed");
    }
    file.close();
}

// Delete a single file ---------------------------------------------------
void FileManager::deleteFile(fs::FS& fs, const char* path)
{
    Serial.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path)) {
        debugln("- file deleted");
    } else {
        debugln("- delete failed");
    }
}

// Delete all saved water targets -----------------------------------------
void FileManager::deleteAllTargets()
{
    int numFiles = getNumTargetFiles();
    if (numFiles == 0) {
        debugln("No saved TargetFiles exist!");
    } else {
        for (int i = 1; i < numFiles + 1; i++) { // Run through this code for each target file
            if (!setFilePath(targetPathName, i)) { // if set path did NOTwork then exit
                exit;
            }
        }
    }
}

// Returns the number of files in a directory -----------------------------
int FileManager::getNumTargetFiles()
{
    int numFiles = 0;
    numFiles = listFiles(LittleFS, "/TARGETS", 1, 0);
    debug("NumFiles in /TARGETS directory is ");
    debugln(numFiles);
    return numFiles;
}
