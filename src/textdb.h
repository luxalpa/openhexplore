//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_TEXTDB_H
#define OPENHEXPLORE_TEXTDB_H

struct struc_2 {
    char *text;
    int field_4;
    int field_8;
};

struct FileEntryStruct {
    char *pData;
    int size;
    short flags;
    short isInUse;
};

void initTextDB();
char * allocFile(size_t fileSize, int flags);
void loadFile(LPCSTR filePath, char **destination, bool isEncrypted);
void getString(char *fileData, unsigned int entryID, struc_2 *output);
bool convertToGamePath(char *relPath);

#endif //OPENHEXPLORE_TEXTDB_H
