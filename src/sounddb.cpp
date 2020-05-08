//
// Created by Smaug on 2020-05-01.
//

#include "sounddb.h"
#include "globals.h"
#include "filedb.h"
#include "sound.h"
#include "global_fns.h"
#include "files.h"
#include <windows.h>
#include <cstdio>

// @ 40A430
void loadSoundbankHeaders() {
    CHAR filename[256]; // [esp+0h] [ebp-100h]

    sprintf(filename, "%s\\%s\\%s", "SAMPLE", gLangPrefix, "smpbank.sbk");
    convertToGamePath(filename);
    gPosSmpbank = loadSBK(filename);

    sprintf(filename, "%s\\%s\\%s", "SAMPLE", gLangPrefix, "musbank.sbk");
    convertToGamePath(filename);
    gPosMusbank = loadSBK(filename);
}

// @ 40A4E0
int loadSysSmpBin() {
    unsigned int size;
    CHAR filename[0x100];

    sprintf(filename, "%s\\%s", "COMMON", "syssmp.bin");
    convertToGamePath(filename);
    gSysSmpBinData = (SmpBinEntry *) Files::getContents(filename, &size, 32770);
    return createSmpInfo(gSysSmpBinData, size, gPosSmpbank);
}

// @ 40A570
int loadMusicSmpBin() {
    unsigned int size;
    char filename[256];

    sprintf(filename, "%s\\%s", "COMMON", "musicsmp.bin");
    convertToGamePath(filename);
    gMusicSmpBinData = (SmpBinEntry *) Files::getContents(filename, &size, 32770);
    return createSmpInfo(gMusicSmpBinData, size, gPosMusbank);
}

// @ 40A650
int sub_40A650(int sndBank, int snd) {
    if (dword_4E6098 & 4)
        return -1;
    else
        return sub_4227B0(sndBank, snd);
}