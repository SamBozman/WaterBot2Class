//*fileManager.h
#pragma once
#include "dataManager.h"

// class C: public A,public B
class FileManager : public WATER_DATA_MANAGER {

public:
    char path[25]; // path to saved files
    char dataBlock[254]; // variable to store temporary data files
    String targetPathName;
    String maxPathName;
    void makeWaterTarget(short int id, String name, int hp, short int hf, int vp,
        short int vf, int sp, short int sf, short int rwt, bool water);
    void loadDataManager();
    void loadTarget(int id); //* (cf) fileManager::loadDataManager()
    bool setFilePath(String basePathName, int id);
    void mountLFS();
    int listFiles(fs::FS& fs, const char* dirname, uint8_t levels, int numFiles);
    bool isDir(fs::FS& fs, const char* dirname, uint8_t levels);
    void createDir(fs::FS& fs, const char* path);
    void removeDir(fs::FS& fs, const char* path);
    void writeFile(fs::FS& fs, const char* path, const char* message);
    void deleteFile(fs::FS& fs, const char* path);
    void deleteAllTargets(); //* (cf) steppers::processIncoming() case 210
    int getNumTargetFiles();

private:
};