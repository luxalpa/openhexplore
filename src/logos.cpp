//
// Created by Smaug on 2020-04-06.
//

#include <windows.h>
#include <cstdio>
#include "globals.h"
#include "global_fns.h"
#include "game_window.h"
#include "pcx.h"
#include "keys.h"

// @ 4205E0
void showHexploreLogo() {
    HexpPaletteEntry *pImgPalette;
    char *pData;
    int width;
    int height;
    char filename[0x100];
    HexpPaletteEntry systemPalette[256];

    sprintf(filename, "%s\\%s", "clut", "logo256.pcx");
    convertToGamePath(filename);

    if (loadPCXFile(filename, &pData, &pImgPalette, &width, &height)) {
        memset(systemPalette, 0, sizeof(systemPalette));
        initDDrawPalette(systemPalette);

        memcpy(getDDrawSurfaceMemPtr(), pData, gWindowWidth * gWindowHeight);

        initDDrawPalette(pImgPalette);
        releaseDDrawSurfaceMem();
        paintDDSurface(nullptr);

        deallocFile(pImgPalette);
        deallocFile(pData);
    }
}

void showPCX(char *filename, HexpPaletteEntry **pImagePalette) {
    char *imageData;

    int width;
    int height;

    convertToGamePath(filename);

    loadPCXFile(filename, &imageData, pImagePalette, &width, &height);

    memcpy(getDDrawSurfaceMemPtr(), imageData, width * height);

    releaseDDrawSurfaceMem();
    paintDDSurface(nullptr);

    deallocFile(imageData);
}

void adjustPaletteBrightness(HexpPaletteEntry *srcPalette, HexpPaletteEntry *targetPalette, float brightness) {
    for (int i = 0; i < 0x100; i++) {
        HexpPaletteEntry srcColor = srcPalette[i];
        targetPalette[i] = {
                .red = static_cast<unsigned char>(brightness * srcColor.red),
                .green = static_cast<unsigned char>(brightness * srcColor.green),
                .blue = static_cast<unsigned char>(brightness * srcColor.blue)
        };
    }
}

// @ 4206C0
bool showLogos() {
    HexpPaletteEntry palette[0x100];

    // @ 4D5D70
    static int state = 0;
    // @ 4EA3D0
    static HexpPaletteEntry *pImagePalette;
    // @ 4EA3D4
    static int initialTickCount;

    int tickCount = GetTickCount();
    int keyCode = processKey();

    switch (state) {
        case 0:
            initialTickCount = tickCount;
            state = 1;
            break;
        case 1:
            // Wait 1 sec on a black screen...
            if (tickCount - initialTickCount > 1000) {
                state = 2;
                initialTickCount = tickCount;
            }
            paintDDSurface(nullptr);
            break;
        case 2: {
            memset(palette, 0, sizeof(palette));
            initDDrawPalette(palette);

            char filename[256] = {"CLUT\\ocean.pcx"};
            showPCX(filename, &pImagePalette);

            state = 3;
            initialTickCount = tickCount;
            break;
        }
        case 3:
            if (keyCode == VK_ESCAPE) {
                state = 6;
            } else {
                float brightness = (tickCount - initialTickCount) / 1000.0;
                if (brightness > 1) {
                    brightness = 1;
                    initialTickCount = tickCount;
                    state = 4;
                }

                adjustPaletteBrightness(pImagePalette, palette, brightness);

                initDDrawPalette(palette);
                paintDDSurface(nullptr);
            }
            break;
        case 4:
            if (keyCode == VK_ESCAPE) {
                state = 6;
            } else {
                if ((tickCount - initialTickCount) > 1000) {
                    state = 5;
                    initialTickCount = tickCount;
                }
                paintDDSurface(nullptr);
            }
            break;
        case 5:
            if (keyCode == VK_ESCAPE) {
                state = 6;
            } else {
                float brightness = (tickCount - initialTickCount) / 1000.0;
                if (brightness > 1) {
                    brightness = 1;
                    initialTickCount = tickCount;
                    state = 6;
                }

                adjustPaletteBrightness(pImagePalette, palette, 1.0 - brightness);

                initDDrawPalette(palette);
                paintDDSurface(nullptr);
            }
            break;
        case 6: {
            deallocFile((char *) pImagePalette);

            memset(palette, 0, sizeof(palette));
            initDDrawPalette(palette);

            char filename[0x100] = {"CLUT\\helio.pcx"};
            showPCX(filename, &pImagePalette);

            state = 7;
            initialTickCount = tickCount;
            break;
        }
        case 7:
            if (keyCode == VK_ESCAPE) {
                state = 10;
            } else {
                float brightness = (tickCount - initialTickCount) / 1000.0;
                if (brightness > 1) {
                    brightness = 1;
                    initialTickCount = tickCount;
                    state = 8;
                }

                adjustPaletteBrightness(pImagePalette, palette, brightness);

                initDDrawPalette(palette);
                paintDDSurface(nullptr);
            }
            break;
        case 8:
            if (keyCode == VK_ESCAPE) {
                state = 10;
            } else {
                if ((tickCount - initialTickCount) > 1000) {
                    state = 9;
                    initialTickCount = tickCount;
                }
                paintDDSurface(nullptr);
            }
            break;
        case 9:
            if (keyCode == VK_ESCAPE) {
                state = 10;
            } else {
                float brightness = (tickCount - initialTickCount) / 1000.0;
                if (brightness > 1) {
                    brightness = 1;
                    initialTickCount = tickCount;
                    state = 10;
                }

                adjustPaletteBrightness(pImagePalette, palette, 1.0 - brightness);

                initDDrawPalette(palette);
                paintDDSurface(nullptr);
            }
            break;
        case 10:
            deallocFile((char *) pImagePalette);

            memset(palette, 0, sizeof(palette));
            initDDrawPalette(palette);
            memset(getDDrawSurfaceMemPtr(), 0, gWindowWidth * gWindowHeight);
            releaseDDrawSurfaceMem();
            paintDDSurface(0);
            return false;
    }
    return true;
}