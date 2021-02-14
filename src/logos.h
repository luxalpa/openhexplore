//
// Created by Smaug on 2020-04-06.
//

#ifndef OPENHEXPLORE_LOGOS_H
#define OPENHEXPLORE_LOGOS_H

#include "game_window.h"

struct UnkStruct {
    void *pData;
    int unk1;
    int unk2;
};

void sub_420130(UnkStruct *a1, int numEntries);
void showHexploreLogo();
void showPCX(char *filename, HexpPaletteEntry **pImagePalette);
void adjustPaletteBrightness(HexpPaletteEntry *srcPalette, HexpPaletteEntry *targetPalette, float brightness);
bool showLogos();

#endif //OPENHEXPLORE_LOGOS_H
