//
// Created by Smaug on 2020-04-02.
//

#include <cstdio>
#include <windows.h>
#include "filedb.h"
#include "globals.h"
#include "global_fns.h"
#include "files.h"
#include "game_window.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

// @ 411F80
void initTextDB() {
    struc_2 a3;
    char filepath[0x100];

    sprintf(filepath, "%s\\%s%s", "COMMON", gLangPrefix, "txt.st1");
    convertToGamePath(filepath);
    loadFile(filepath, &gTextDBData, true);
    getString(gTextDBData, 100u, &a3);
    strcpy(gText_Strength, a3.text);
    getString(gTextDBData, 101u, &a3);
    strcpy(gText_Mechanism, a3.text);
    getString(gTextDBData, 102u, &a3);
    strcpy(gText_Incantation, a3.text);
    getString(gTextDBData, 103u, &a3);
    strcpy(gText_Agility, a3.text);
    getString(gTextDBData, 104u, &a3);
    strcpy(gText_ToNextLevel, a3.text);
}

// @ 4156E0
int initFileDB(int maxSize) {
    if (gLoadedFiles)
        return 0;
    gLoadedFiles = (FileEntryStruct *) hexp_malloc(24000u);
    if (!gLoadedFiles)
        return 0;
    memset(gLoadedFiles, 0, 24000u);
    gMaxTotalSize = maxSize;
    gCurrentTotalSize = 0;
    dword_44CDB8 = 0;
    dword_44CDC0 = 0;
    dword_44CDC4 = 0;
    gNumFiles = 0;
    dword_44CDC8 = 0;
    return 1;
}

// Allocates Memory for the file
// @ 4157D0
char *allocFile(size_t fileSize, int flags) {
    signed int v7; // eax

    if (!gLoadedFiles)
        return 0;
    if (!fileSize)
        return 0;

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

FileEntryStruct *findFile(const char *const ptr) {
    for(int i = 0; i < 2000; i++) {
        FileEntryStruct *file = &gLoadedFiles[i];
        if(file->isInUse && file->pData == ptr && file->flags & 0x8000) {
            return file;
        }
    }
    return nullptr;
}

// @ 415900
void deallocFile(char *pFileData) {
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

// @ 4159A0
LRESULT keycodeHandler(UINT msg, WPARAM wparam, LPARAM lparam) {
    unsigned int result; // eax
    char v7; // cl
    int v8; // edx
    int v9; // edi

    result = true;
    switch (msg) {
        case WM_KEYDOWN:
            if (wparam == VK_SHIFT) {
                gModifierKeyState |= 1u;
                return TRUE;
            } else {
                if (wparam == VK_CONTROL) {
                    // TODO: We could remove this but it works based on the auto key repeat feature in windows, so there would be a delay.
                    // previous key state
                    if (!(lparam & 0x40000000))
                        gModifierKeyState |= 2u;
                } else {
                    int v4 = 0;
                    int *pKeyCode = dword_4EA330;
                    while (*pKeyCode != wparam) {
                        ++pKeyCode;
                        ++v4;
                        if (pKeyCode >= &dword_4EA3B0)
                            goto LABEL_12;
                    }
                    dword_4EA2D8 |= 1 << v4;
                    LABEL_12:
                    unsigned int v6 = (dword_44CDCC + 1) % 10;
                    if (v6 == dword_44CDD0) { // TODO: Find out when this is true, doesn't appear to happen
                        if (wparam != VK_BACK) {
                            sub_4227B0(dword_4E5F58, 20);
                            return TRUE;
                        }
                    } else if (wparam == VK_BACK || !(lparam & 0x40000000)) {
                        dword_4EA2E0[dword_44CDCC] = wparam;
                        dword_44CDCC = v6;
                        return TRUE;
                    }
                }
                return TRUE;
            }
        case WM_KEYUP:
            if (wparam == VK_SHIFT) {
                result = gModifierKeyState & 0xFFFFFFFE;
                gModifierKeyState &= 0xFFFFFFFE;
            } else if (wparam != VK_CONTROL) {
                v7 = 0;
                result = (unsigned int) dword_4EA330;
                while (*(int *) result != wparam) {
                    result += 4;
                    ++v7;
                    if (result >= (unsigned int) &dword_4EA3B0)
                        return result;
                }
                v8 = ~(1 << v7);
                result = v8 & dword_4EA2D8;
                dword_4EA2D8 &= v8;
            }
            break;
        case WM_CHAR:
            result = dword_44CDDC;
            if (dword_44CDDC) {
                v9 = dword_44CDD4;
                result = (dword_44CDD4 + 1) / 10;
                if (dword_44CDD8 == (dword_44CDD4 + 1) % 10) {
                    result = sub_4227B0(dword_4E5F58, 20);
                } else {
                    dword_44CDD4 = (dword_44CDD4 + 1) % 10;
                    dword_4EA308[v9] = wparam;
                }
            }
            break;
        default:
            return FALSE;
    }
    return result;
}

int sub_415B40() {
    if (dword_44CDD0 == dword_44CDCC)
        return 0;

    int v0 = dword_4EA2E0[dword_44CDD0];
    dword_44CDD0 = (dword_44CDD0 + 1) % 10;
    return v0;
}

// @ 416000
void loadFile(LPCSTR filePath, char **destination, bool isEncrypted) {
    *destination = 0;
    int fd = Files::open(filePath, Files::OpenMode::ReadOnly);

    int filesize = Files::getSize(fd);
    *destination = allocFile(filesize, 0x8003);
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

// Converts the provided parameter and replaces it inplace with the full path to the game
// @ 417090
bool convertToGamePath(char *relPath) {
    char filePath[0x100];
    sprintf(filePath, "%s\\%s", gGame.directory, relPath);
    if (Files::exists(filePath)) {
        strcpy(relPath, filePath);
        return true;
    }
    sprintf(filePath, "%s\\%s", gGame.directory2, relPath);
    strcpy(relPath, filePath);
    return false;
}
