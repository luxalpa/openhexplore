//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_FILEDB_H
#define OPENHEXPLORE_FILEDB_H

#include <windows.h>

struct struc_2 {
    char *text;
    int field_4;
    int field_8;
};

struct FileEntryStruct {
    char *pData;
    int size;
    short flags;
    short isInUse; // TODO: This can also equal 2
};

void initTextDB();
bool initFileDB(int maxSize);
char * allocFile(size_t fileSize, int flags);
void deallocFile(char *pFileData);

void loadFile(LPCSTR filePath, char **destination, bool isEncrypted);
void getString(char *fileData, unsigned int entryID, struc_2 *output);
bool convertToGamePath(char *relPath);

#endif //OPENHEXPLORE_FILEDB_H
