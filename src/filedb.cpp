//
// Created by Smaug on 2020-04-02.
//

#include <cstdio>
#include "filedb.h"
#include "globals.h"
#include "global_fns.h"
#include "files.h"
#include "game_window.h"
#include "sound.h"
#include <sys/stat.h>

void loadSmallFont(SB0Info *info, const char *path) {
    SB0File *pData;

    readFileContents(path, (void **) &pData);

    *info = {
            .minX = 0,
            .maxX = 479,
            .minY = 0,
            .maxY = 639,
            .width = 640,
            .height = 480,
            .pData = pData,
    };

    initSB0CharacterHeight(info);
    sub_4164B0(info, -3);
}

// @ 411C50
void loadFonts() {
    SB0File *pData;
    char path[256];

    sprintf(path, "%s\\%s", "COMMON", "smfntw.sb0");
    convertToGamePath(path);
    loadSmallFont(&SmFntW, path);

    sprintf(path, "%s\\%s", "COMMON", "smfntr.sb0");
    convertToGamePath(path);
    loadSmallFont(&SmFntR, path);

    sprintf(path, "%s\\%s", "COMMON", "smfntb.sb0");
    convertToGamePath(path);
    loadSmallFont(&SmFntB, path);

    sprintf(path, "%s\\%s", "COMMON", "fnt10.sb0");
    convertToGamePath(path);
    readFileContents(path, (void **) &pData);

    Fnt10 = {
            .minX = 0,
            .maxX = 479,
            .minY = 2,
            .maxY = 637,
            .width = 640,
            .height = 480,
            .pData = pData,
    };

    initSB0CharacterHeight(&Fnt10);
    sub_4164B0(&Fnt10, -2);

    sprintf(path, "%s\\%s", "COMMON", "fnt16.sb0");
    convertToGamePath(path);
    readFileContents(path, (void **) &pData);

    Fnt16 = {
            .minX = 90,
            .maxX = 389,
            .minY = 0,
            .maxY = 639,
            .width = 640,
            .height = 480,
            .pData = pData,
    };

    initSB0CharacterHeight(&Fnt16);
    sub_4164B0(&Fnt16, -12);
}

// @ 411F80
void initTextDB() {
    struc_2 a3;
    char filepath[0x100];

    sprintf(filepath, "%s\\%s%s", "COMMON", gLangPrefix, "txt.st1");
    convertToGamePath(filepath);
    loadFile(filepath, &gTextDBData, true);
    getString(gTextDBData, 100, &a3);
    strcpy(gText_Strength, a3.text);
    getString(gTextDBData, 101, &a3);
    strcpy(gText_Mechanism, a3.text);
    getString(gTextDBData, 102, &a3);
    strcpy(gText_Incantation, a3.text);
    getString(gTextDBData, 103, &a3);
    strcpy(gText_Agility, a3.text);
    getString(gTextDBData, 104, &a3);
    strcpy(gText_ToNextLevel, a3.text);
}

// @ 412100
void loadTxtSmpBin() {
    unsigned int size;
    char filename[0x100];

    sprintf(filename, "%s\\%s%s", "COMMON", gLangPrefix, "txtsmp.bin");
    convertToGamePath(filename);

    gTxtSmpData = (SmpBinEntry*)Files::getContents(filename, &size, 0x8002);
    gTxtSmpInfoPos = createSmpInfo(gTxtSmpData, size, gPosSmpbank);
}

// @ 4156E0
bool initFileDB(int maxSize) {
    if (gLoadedFiles)
        return false;
    gLoadedFiles = (FileEntryStruct *) hexp_malloc(24000u);
    if (!gLoadedFiles)
        return false;
    memset(gLoadedFiles, 0, 24000u);
    gMaxTotalSize = maxSize;
    gCurrentTotalSize = 0;
    dword_44CDB8 = 0;
    dword_44CDC0 = 0;
    dword_44CDC4 = 0;
    gNumFiles = 0;
    dword_44CDC8 = 0;
    return true;
}

// Allocates Memory for the file
// @ 4157D0
void *allocFile(size_t fileSize, int flags) {
    if (!gLoadedFiles)
        return nullptr;
    if (!fileSize)
        return nullptr;

    FileEntryStruct *currentEntry = gLoadedFiles;
    for (int i = 0; i < 2000; i++, currentEntry++) {
        if (!currentEntry->isInUse)
            break;
    }
    // Reached the end. TODO: This will crash because it will point after the last entry
    if (currentEntry->isInUse)
        exitSilently(17);

    int hiFlags = flags & 0xF000;
    if (hiFlags == 0x2000 || hiFlags == 0x4000)
        return 0;
    if (hiFlags != 0x8000)
        return currentEntry->pData;

    if (gCurrentTotalSize + fileSize > gMaxTotalSize)
        exitSilently(3);

    char *mem = (char *) hexp_malloc(fileSize);
    currentEntry->pData = mem;
    if (!mem)
        exitSilently(14);

    currentEntry->size = fileSize;
    currentEntry->flags = flags;
    currentEntry->isInUse = 1;

    gCurrentTotalSize += fileSize;
    ++gNumFiles;
    if (dword_44CDC0 < gCurrentTotalSize)
        dword_44CDC0 = gCurrentTotalSize;
    if (dword_44CDC8 < gNumFiles)
        dword_44CDC8 = gNumFiles;

    return currentEntry->pData;
}

FileEntryStruct *findFile(const void *const ptr) {
    for (int i = 0; i < 2000; i++) {
        FileEntryStruct *file = &gLoadedFiles[i];
        if (file->isInUse && file->pData == ptr && file->flags & 0x8000) {
            return file;
        }
    }
    return nullptr;
}

// @ 415900
void deallocFile(void *pFileData) {
    if (!pFileData) return;

    auto fs = findFile(pFileData);
    hexp_free(fs->pData);

    if (fs->isInUse == 1)
        gCurrentTotalSize -= fs->size;

    if (fs->isInUse == 2)
        dword_44CDB8 -= fs->size;

    --gNumFiles;
    fs->pData = 0;
    fs->size = 0;
    fs->flags = 0;
    fs->isInUse = 0;
}

// @ 416000
void loadFile(const char* filePath, char **destination, bool isEncrypted) {
    *destination = 0;
    int fd = Files::open(filePath, Files::OpenMode::ReadOnly);

    int filesize = Files::getSize(fd);
    *destination = (char*)allocFile(filesize, 0x8003);
    Files::read(fd, *destination, filesize);

    Files::close(fd);

    if (isEncrypted) {
        char decVal = 55;
        char *data = *destination;

        for (int i = 0; i < filesize; i++) {
            char curVal = data[i];
            data[i] ^= decVal;
            decVal += 0x33 + curVal;
        }
    }
}

struct TextDBHeader {
    int magicNumber;
    int version;
    int numEntries;
    int offsetSection1;
    int area1;
    int areaStrings;
    int area2;
};

// @ 4160A0
void getString(char *fileData, unsigned int entryID, struc_2 *output) {
    TextDBHeader *header = (TextDBHeader *) fileData;

    if (!fileData) {
        return;
    }

    if (header->magicNumber != 'TXTB') {
        return;
    }

    if (header->numEntries == 0) {
        return;
    }

    if (!output) {
        return;
    }

    if (entryID > 99999999) {
        return;
    }

    output->field_4 = 0;
    output->field_8 = -1;
    output->text = 0;

    unsigned int *lowerBound = (unsigned int *) &fileData[header->offsetSection1];
    unsigned int *upperBound = &lowerBound[header->numEntries];
    unsigned int *currentID = &lowerBound[header->numEntries / 2];

    if (lowerBound >= upperBound) {
        return;
    }

    while (*currentID != entryID) {
        if (*currentID <= entryID)
            lowerBound = currentID + 1;
        else
            upperBound = currentID;

        currentID = &lowerBound[(upperBound - lowerBound) / 2];
        if (lowerBound >= upperBound)
            return;
    }

    output->text = &fileData[currentID[header->numEntries]];
    int *v8 = (int *) &fileData[header->area2];

    // TODO: These don't do anything.
    int v7 = (&currentID[-*((int *) fileData + 3) / 4] - (unsigned int *) fileData) / 2;
    output->field_4 = v8[v7];
    output->field_8 = v8[v7 + 1];
}

// @ 416410
void readFileContents(const char *filename, void **ppData) {
    *ppData = nullptr;
    int fd = Files::open(filename, Files::OpenMode::ReadOnly);
    int size = Files::getSize(fd);

    void *pData = allocFile(size, 0x801A);

    *ppData = pData;
    Files::read(fd, pData, size);

    Files::close(fd);
}

// @ 416490
void initSB0CharacterHeight(SB0Info *sb0Info) {
    if (sb0Info)
        sb0Info->characterHeight = *(unsigned __int16 *) &sb0Info->pData->data[sb0Info->pData->header.offsetBlock1 + 4];
}

// TODO: This sets a flag (or negative number). Name this.
// @ 4164B0
void sub_4164B0(SB0Info *a1, int a2) {
    if (a1)
        a1->field_1C = a2;
}
