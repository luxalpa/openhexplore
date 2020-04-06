//
// Created by Smaug on 2020-04-06.
//

#ifndef OPENHEXPLORE_PCX_H
#define OPENHEXPLORE_PCX_H

#include <winnt.h>

bool loadPCXFile(LPCSTR fileName, char **ppData, char **ppPaletteData, int *pWidth, int *pHeight);

#endif //OPENHEXPLORE_PCX_H
