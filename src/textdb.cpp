//
// Created by Smaug on 2020-04-02.
//

#include <cstdio>
#include <windows.h>
#include "textdb.h"
#include "globals.h"
#include "global_fns.h"
#include "files.h"
#include "ddraw.h"
#include "interop/memory.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

// @ 411F80
void initTextDB() {
    struc_2 a3;
    char filepath[0x100];

    sprintf(filepath, "%s\\%s%s", "COMMON", gLangPrefix, "txt.st1");
    convertToGamePath(filepath);
    sub_416000(filepath, &gTextDBData, true);
    sub_4160A0(gTextDBData, 100u, &a3);
    strcpy(gText_Strength, a3.field_0);
    sub_4160A0(gTextDBData, 101u, &a3);
    strcpy(gText_Mechanism, a3.field_0);
    sub_4160A0(gTextDBData, 102u, &a3);
    strcpy(gText_Incantation, a3.field_0);
    sub_4160A0(gTextDBData, 103u, &a3);
    strcpy(gText_Agility, a3.field_0);
    sub_4160A0(gTextDBData, 104u, &a3);
    strcpy(gText_ToNextLevel, a3.field_0);
}

// Allocates Memory for the file
// @ 4157D0
char * allocFile(size_t fileSize, int flags) {
    signed int v7; // eax

    if (!gLoadedFiles)
        return 0;
    if (!fileSize)
        return 0;

    FileEntryStruct *currentEntry = gLoadedFiles;
    for(int i = 0; i < 2000; i++, currentEntry++) {
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

    char *mem = (char*) hexp_malloc(fileSize);
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

// @ 416000
void sub_416000(LPCSTR lpText, char **a2, int a3) {
    int v3; // eax
    int v4; // ebx
    int filesize; // eax
    unsigned int v6; // edi
    char *v7; // eax
    char v8; // edx
    char v9; // ecx
    char *v10; // esi
    char *v11; // eax
    char v12; // bl

    *a2 = 0;
    v3 = Files::open(lpText, Files::OpenMode::ReadOnly);
    v4 = v3;
    filesize = Files::getSize(v3);
    v6 = filesize;
    v7 = (char *) allocFile(filesize, 0x8003);
    *a2 = v7;
    Files::read(v4, v7, v6);
    Files::close(v4);
    if (a3) {
        v9 = 55;
        v10 = *a2;
        v11 = &(*a2)[v6];
        if (&v10[v6] > v10) {
            do {
                v8 = *v10;
                v12 = *v10++ ^ v9;
                v9 += v8 + 51;
                *(v10 - 1) = v12;
            } while (v11 > v10);
        }
    }
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
