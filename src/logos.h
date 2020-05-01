//
// Created by Smaug on 2020-04-06.
//

#ifndef OPENHEXPLORE_LOGOS_H
#define OPENHEXPLORE_LOGOS_H

#include "game_window.h"

void showPCX(char *filename, HexpPaletteEntry **pImagePalette);
void adjustPaletteBrightness(HexpPaletteEntry *srcPalette, HexpPaletteEntry *targetPalette, float brightness);
bool showLogos();

#endif //OPENHEXPLORE_LOGOS_H
