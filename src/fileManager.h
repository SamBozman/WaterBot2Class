//*fileManager.h
#pragma once
#include "dataManager.h"

// class C: public A,public B
class FileManager : public WATER_DATA_MANAGER {

public:
    String getTargetPath(int id);
    void mountLFS();
    int listFiles(fs::FS& fs, const char* dirname, uint8_t levels, int numFiles);
    bool isDir(fs::FS& fs, const char* dirname, uint8_t levels);
    void createDir(fs::FS& fs, const char* path);
    void removeDir(fs::FS& fs, const char* path);
    void writeFile(fs::FS& fs, const char* path, const char* message);
    void deleteFile(fs::FS& fs, const char* path);

private:
    static const String tPath;
};