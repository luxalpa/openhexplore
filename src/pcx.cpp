//
// Created by Smaug on 2020-04-06.
//

#include <windows.h>
#include <cstdio>
#include "pcx.h"
#include "filedb.h"
#include "global_fns.h"
#include "files.h"
#include "globals.h"
#include "game_window.h"

// @ 0x401000

struct PCXHeader {
    char magicValue;
    char version;
    char isEncoded;
    char colorDepth;
    short minX;
    short minY;
    short maxX;
    short maxY;
    short dpiX;
    short dpiY;
    char egaPalette[48];
    char reserved;
    char numColorPlanes;
    short numPlaneBytes;
    short mode;
    short resolutionX;
    short resolutionY;
    char reserved2[54];
};

bool loadPCXFile(LPCSTR fileName, char **ppData, HexpPaletteEntry **ppPaletteData, int *pWidth, int *pHeight) {
    *ppData = nullptr;
    *ppPaletteData = nullptr;
    *pWidth = 0;
    *pHeight = 0;

    if (!Files::exists(fileName))
        return 0;

    int fd = Files::open(fileName, Files::OpenMode::ReadOnly);
    if (fd == -1)
        return 0;

    int size = Files::getSize(fd);
    if (!size)
        return 0;

    char *pData = (char*)allocFile(size, 0x8001);
    Files::read(fd, pData, size);
    Files::close(fd);

    PCXHeader *header = (PCXHeader *) pData;

    if (header->magicValue != 0xA || header->version != 5 || !header->isEncoded ||
        header->colorDepth != 8) {
        deallocFile(pData);
        return 0;
    }

    int width = header->maxX - header->minX + 1;
    int height = header->maxY - header->minY + 1;

    int area = width * height;
    char *pImage = pData + 0x80;

    char *dest = (char*)allocFile(width * height, 0x8001);
    *ppData = dest;

    for (int y = 0; y < height; y++) {
        int x = 0;
        while (x < width) {
            char curByte = *pImage;
            if ((curByte & 0xC0) == 0xC0) {
                char runLength = curByte - 192;

                pImage++;
                char color = *pImage;

                x += runLength;
                for (int i = 0; i < runLength; i++) {
                    if (dest < area + *ppData)
                        *dest = color;
                    ++dest;
                }
                pImage++;
            } else {
                x++;
                if (dest < area + *ppData)
                    *dest = curByte;
                pImage++;
                ++dest;
            }
        }
        dest += (width - header->numPlaneBytes);
    }

    *ppPaletteData = (HexpPaletteEntry*) allocFile(0x300, 0x8001);
    memcpy(*ppPaletteData, pImage + 1, 0x300u);

    *pWidth = width;
    *pHeight = height;

    deallocFile(pData);
    return true;
}