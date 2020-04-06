//
// Created by Smaug on 2020-04-06.
//

#include <windows.h>
#include <cstdio>
#include "logos.h"
#include "globals.h"
#include "global_fns.h"
#include "game_window.h"
#include "files.h"
#include "pcx.h"

// @ 4206C0
signed int showLogos() {
    signed int result; // eax
    int v3; // eax
    int v4; // ecx
    char *v5; // edx
    signed int v6; // esi
    int v7; // eax
    char *v8; // ecx
    __int16 v9; // si
    signed int v10; // edx
    int v11; // eax
    int v12; // eax
    int v13; // edx
    char *v14; // esi
    signed int v15; // ecx
    int v16; // eax
    char *v17; // ecx
    __int16 v18; // si
    signed int v19; // edx
    int v20; // eax
    char *imageData; // [esp+10h] [ebp-40Ch]
    int height; // [esp+14h] [ebp-408h]
    int width; // [esp+18h] [ebp-404h]
    CHAR Text[256]; // [esp+1Ch] [ebp-400h]
    char v25[768]; // [esp+11Ch] [ebp-300h]

    int tickCount = GetTickCount();
    int keyCode = sub_415B40();

    if (showLogosInternalState) {
        // Wait 1 sec on a black screen...
        if (showLogosInternalState == 1) {
            if ((signed int) (tickCount - dword_4EA330[41]) > 1000) {
                showLogosInternalState = 2;
                dword_4EA330[41] = tickCount;
            }
            paintDDSurface(0);
            result = 1;
        } else if (showLogosInternalState == 2) {
            sprintf(Text, "%s\\%s", "CLUT", "ocean.pcx");
            convertToGamePath(Text);

            if (!loadPCXFile(Text, &imageData, (char**)&dword_4EA330[40], &width, &height))
                Files::open(Text, Files::OpenMode::ReadOnly);

            memset(v25, 0, sizeof(v25));
            sub_4168D0(v25);
            memcpy(getDDrawSurfaceMemPtr(), imageData, dword_44E128 * dword_44E12C);
            releaseDDrawSurfaceMem();
            paintDDSurface(0);
            sub_415900((int*)imageData);
            result = 1;
            showLogosInternalState = 3;
            dword_4EA330[41] = tickCount;
        } else if (showLogosInternalState == 3) {
            if (keyCode == VK_ESCAPE) {
                result = 1;
                showLogosInternalState = 6;
            } else {
                v3 = (signed int) ((tickCount - dword_4EA330[41]) << 8) / 1000;
                if (v3 > 256) {
                    v3 = 256;
                    dword_4EA330[41] = tickCount;
                    showLogosInternalState = 4;
                }
                v4 = dword_4EA330[40];
                v5 = v25;
                v6 = 768;
                do {
                    ++v4;
                    ++v5;
                    --v6;
                    *(v5 - 1) = (unsigned __int16) (v3 * *(unsigned __int8 *) (v4 - 1)) >> 8;
                } while (v6);
                sub_4168D0(v25);
                paintDDSurface(0);
                result = 1;
            }
        } else if (showLogosInternalState == 4) {
            if (keyCode == VK_ESCAPE) {
                result = 1;
                showLogosInternalState = 6;
            } else {
                if ((signed int) (tickCount - dword_4EA330[41]) > 1000) {
                    showLogosInternalState = 5;
                    dword_4EA330[41] = tickCount;
                }
                paintDDSurface(0);
                result = 1;
            }
        } else if (showLogosInternalState == 5) {
            if (keyCode == VK_ESCAPE) {
                result = 1;
                showLogosInternalState = 6;
            } else {
                v7 = (signed int) ((tickCount - dword_4EA330[41]) << 8) / 1000;
                if (v7 > 256) {
                    v7 = 256;
                    dword_4EA330[41] = tickCount;
                    showLogosInternalState = 6;
                }
                v8 = v25;
                v9 = 256 - v7;
                v10 = 768;
                v11 = dword_4EA330[40];
                do {
                    ++v11;
                    ++v8;
                    --v10;
                    *(v8 - 1) = (unsigned __int16) (v9 * *(unsigned __int8 *) (v11 - 1)) >> 8;
                } while (v10);
                sub_4168D0(v25);
                paintDDSurface(0);
                result = 1;
            }
        } else if (showLogosInternalState == 6) {
            sub_415900((int*)dword_4EA330[40]);
            sprintf(Text, "%s\\%s", "CLUT", "helio.pcx");
            convertToGamePath(Text);
            if (!loadPCXFile(Text, &imageData, (char**)&dword_4EA330[40], &width, &height))
                Files::open(Text, Files::OpenMode::ReadOnly);
            memset(v25, 0, sizeof(v25));
            sub_4168D0(v25);
            memcpy(getDDrawSurfaceMemPtr(), imageData, dword_44E128 * dword_44E12C);
            releaseDDrawSurfaceMem();
            paintDDSurface(0);
            sub_415900((int*)imageData);
            result = 1;
            showLogosInternalState = 7;
            dword_4EA330[41] = tickCount;
        } else if (showLogosInternalState == 7) {
            if (keyCode == VK_ESCAPE) {
                result = 1;
                showLogosInternalState = 10;
            } else {
                v12 = (signed int) ((tickCount - dword_4EA330[41]) << 8) / 1000;
                if (v12 > 256) {
                    v12 = 256;
                    dword_4EA330[41] = tickCount;
                    showLogosInternalState = 8;
                }
                v13 = dword_4EA330[40];
                v14 = v25;
                v15 = 768;
                do {
                    ++v13;
                    ++v14;
                    --v15;
                    *(v14 - 1) = (unsigned __int16) (v12 * *(unsigned __int8 *) (v13 - 1)) >> 8;
                } while (v15);
                sub_4168D0(v25);
                paintDDSurface(0);
                result = 1;
            }
        } else if (showLogosInternalState == 8) {
            if (keyCode == VK_ESCAPE) {
                result = 1;
                showLogosInternalState = 10;
            } else {
                if ((signed int) (tickCount - dword_4EA330[41]) > 1000) {
                    showLogosInternalState = 9;
                    dword_4EA330[41] = tickCount;
                }
                paintDDSurface(0);
                result = 1;
            }
        } else if (showLogosInternalState == 9) {
            if (keyCode == VK_ESCAPE) {
                result = 1;
                showLogosInternalState = 10;
            } else {
                v16 = (signed int) ((tickCount - dword_4EA330[41]) << 8) / 1000;
                if (v16 > 256) {
                    v16 = 256;
                    dword_4EA330[41] = tickCount;
                    showLogosInternalState = 10;
                }
                v17 = v25;
                v18 = 256 - v16;
                v19 = 768;
                v20 = dword_4EA330[40];
                do {
                    ++v20;
                    ++v17;
                    --v19;
                    *(v17 - 1) = (unsigned __int16) (v18 * *(unsigned __int8 *) (v20 - 1)) >> 8;
                } while (v19);
                sub_4168D0(v25);
                paintDDSurface(0);
                result = 1;
            }
        } else {
            if (showLogosInternalState == 10) {
                sub_415900((int*)dword_4EA330[40]);
                memset(v25, 0, sizeof(v25));
                sub_4168D0(v25);
                memset(getDDrawSurfaceMemPtr(), 0, dword_44E128 * dword_44E12C);
                releaseDDrawSurfaceMem();
                paintDDSurface(0);
            }
            result = 0;
        }
    } else {
        result = 1;
        dword_4EA330[41] = tickCount;
        showLogosInternalState = 1;
    }
    return result;
}