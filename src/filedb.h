//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_FILEDB_H
#define OPENHEXPLORE_FILEDB_H

#include <windows.h>
#include "game/meta.h"

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

struct SB0Header {
    char magicNumber[4];
    int version;
    int numBlock1;
    int numBlock2;
    int zero1;
    int zero2;
    int offsetBlock1;
    int offsetBlock2;
    int unk1;
    int unk2;
    int unk3;
    int zero3;
    int zero4;
    int unk4;
    int unk5;
};

union SB0File {
    SB0Header header;
    char data[];
};

struct SB0Info {
    int minX;
    int maxX;
    int minY;
    int maxY;
    int width;
    int height;
    SB0File *pData;
    int field_1C;
    int characterHeight;
    int field_24;
    int field_28;
    int field_2C;
};

void loadFonts();

void initTextDB();

void loadTxtSmpBin();

bool initFileDB(int maxSize);

void *allocFile(size_t fileSize, int flags);

void deallocFile(void *pFileData);

void loadFile(const char* filePath, char **destination, bool isEncrypted);

void getString(char *fileData, unsigned int entryID, struc_2 *output);

void readFileContents(const char *filename, void **ppData);

void initSB0CharacterHeight(SB0Info *sb0Info);

void sub_4164B0(SB0Info *a1, int a2);

#endif //OPENHEXPLORE_FILEDB_H
