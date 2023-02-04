//*fileManager.cpp
#include "fileManager.h"

#include "other.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
String FileManager::getTargetPath(int id)
{
    String s = "Hello";

    return s;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void FileManager::mountLFS()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
        debugln("LittleFS Mount Failed");
    }
}

// Returns # of files in directory+++++++++++++++++++++++++++++++++++++++++
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

// Returns 'True' if file is a directory ++++++++++++++++++++++++++++++++++
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

// Makes a directory using the supplied string ++++++++++++++++++++++++++++
void FileManager::createDir(fs::FS& fs, const char* path)
{
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path)) {
        debugln("Dir created");
    } else {
        debugln("mkdir failed");
    }
}

// Removes an empty directory +++++++++++++++++++++++++++++++++++++++++++++
void FileManager::removeDir(fs::FS& fs, const char* path)
{
    Serial.printf("Removing Dir: %s\n", path);
    if (fs.rmdir(path)) {
        debugln("Dir removed");
    } else {
        debugln("rmdir failed");
    }
}

// Write a file to a directory ++++++++++++++++++++++++++++++++++++++++++++
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void FileManager::deleteFile(fs::FS& fs, const char* path)
{
    Serial.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path)) {
        debugln("- file deleted");
    } else {
        debugln("- delete failed");
    }
}
