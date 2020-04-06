//
// Created by Smaug on 2020-04-03.
//

#include <cstdio>
#include "run.h"
#include "../game_window.h"
#include "../globals.h"
#include "meta.h"
#include "../global_fns.h"
#include "../logos.h"

// @ 414C80
void playVideo(PlayVideoMode mode, int episode, int level) {
    if (mode == PlayVideoMode::LevelVideo) {
        sprintf(gCurrentVideoPath, "%s\\%s\\%s\\%s%01d%s%02d%s", "SAMPLE", gLangPrefix, "video", "E", episode, "L", level,
                ".SMK");
        convertToGamePath(gCurrentVideoPath);
        dword_4E5FAC = 2;
    } else if (mode == PlayVideoMode::GameIntro) {
        sprintf(gCurrentVideoPath, "%s\\%s\\%s\\%s%s", "SAMPLE", gLangPrefix, "video", "intro", ".SMK");
        convertToGamePath(gCurrentVideoPath);
        dword_4E5FAC = 2;
    } else {
        gCurrentVideoPath[0] = 0;
    }
}

// @ 426590;
signed int sub_426590() {
    signed int result; // eax
    int v1; // eax
    unsigned int v2; // eax
    int v3; // eax
    int *v4; // ecx
    int v5; // eax

    if (dword_4E5FA8) {
        // Set at the end of the program when pressing quit
        return 0;
    }

    // This is only true at the start
    if (dword_4E60E0 == -1) {
        showCursor(true);
        dword_4E60E0 = 0;
    }

    if (dword_4E60E0 == 0) {
        if (showLogos() == 1)
            return 1;

        // Reached after the 2 logo screens
        dword_4DBCF4 = (int) &dword_4DBD00;
        dword_4E6098 = 0;
        dword_4E5FF4 = 0;
        dword_4E5FAC = 1;
        sub_429620(); // Shows Hexplore Screen
        playVideo(PlayVideoMode::GameIntro, 0, 0);
        result = 1;
        dword_4E5FB8 = 2;
        dword_4E60E0 = 1;
        return result;
    }

    // Reached only after the Hexplore Splash Screen

    switch (dword_4E5FAC) {
        case 1:
            // Menu (and game?)
            sub_406C80(dword_4EB750);
            break;
        case 2:
            // Videos
            sub_414D30();
            return 1;
        case 3:
            // Credits
            sub_414E40();
            return 1;
    }
    if (!dword_4E5FB8 && sub_40A9F0()) {
        if (dword_4DBCF8 == -1) {
            v1 = *(int *) (dword_4DBCF4 + 248);
            if (v1 != -1)
                dword_4DBCF8 = sub_42AC70(dword_4E5DA8, v1, dword_4E5DB0);
        }
        sub_40A970();
    }
    if (dword_4E5FB0 & 1) {
        if (!dword_4DBCC0)
            dword_4DBCBC = GetTickCount();
        if (++dword_4DBCC0 == 21) {
            v2 = GetTickCount();
            dword_4DBCC0 = 0;
            dword_4DBCC8 = v2 - dword_4DBCBC;
            dword_4DBCC4 = 0x4E20 / (v2 - dword_4DBCBC);
        }
    }
    v3 = sub_415E70();
    if (v3) {
        if (v3 >= 1 && v3 <= 2) {
            if (dword_4E607C == 1) {
                dword_4E607C = 0;
                v3 |= 0x100u;
            }
            sub_414270(v3);
        }
    } else if (sub_40AB10()) {
        dword_4E5FB4 = 1;
        dword_4E5FC4 = 0;
        dword_4E5FBC = 0;
        dword_4E5FC0 = 0;
        dword_4E5FC8 = 0;
        dword_4E5FCC = 0;
        dword_4E5FD0 = 0;
        gModifierKeyState = 0;
        dword_4E60C8 = 0;
        dword_4E60DC = -1;
    } else {
        if (dword_4E5FB8)
            sub_413A80(1);
        dword_4E5FB4 = 0;
    }
    dword_4E5FB0 = sub_416BB0();
    if (dword_4E5FB0 == 2)
        ++dword_4E60B4;
    if (dword_4E5FB0 == 1)
        ++dword_4E60B8;
    sub_416DD0();
    if (dword_4E5FB0 & 2) {
        if (dword_4E6098 & 1 || !dword_4E6098)
            dword_574240 = 0;
        if (!dword_4E5FB8) {
            v4 = dword_44E400;
            dword_4E5FB8 = 1;
            do {
                if (*v4) {
                    v5 = *v4;
                    if (!(v5 & 0x1000))
                        dword_4E5FB8 = 0;
                }
                v4 += 244;
            } while (v4 < dword_44F340);
        }
    }
    if (dword_4E5FB4) {
        dword_4E5FC4 = 0;
        dword_4E5FBC = 0;
        dword_4E5FC0 = 0;
        dword_4E5FC8 = 0;
        dword_4E5FCC = 0;
        dword_4E5FD0 = 0;
        gModifierKeyState = 0;
        dword_4E60DC = -1;
        dword_4E60C8 = 0;
        if (!(dword_4E6098 & 6))
            goto LABEL_56;
    } else {
        dword_4E5FC4 = dword_44E118;
        dword_4E5FBC = dword_44E110;
        dword_4E5FC0 = dword_44E114;
        dword_4E5FC8 = dword_4E5FD4;
        dword_4E5FCC = dword_4E5FD8;
        dword_4E5FD0 = dword_4E5FDC;
        sub_427290();
        dword_44E11C = 0;
    }
    sub_426A70();
    LABEL_56:
    sub_414BD0();
    if (dword_4E5FB8) {
        dword_4E5FC4 = 0;
        dword_4E5FBC = 0;
        dword_4E5FC0 = 0;
        dword_4E5FC8 = 0;
        dword_4E5FCC = 0;
        dword_4E5FD0 = 0;
        gModifierKeyState = 0;
        dword_4E60C8 = 0;
        dword_4E60DC = -1;
        dword_44E118 = 0;
        sub_406E10(dword_4EB750, 0);
        sub_406E20(dword_4EB750);
        sub_40B2A0();
        paintDDSurface(0);
        result = 1;
    } else {
        if (dword_4E5FB0 & 2)
            sub_40EA00(&dword_4DBD00, dword_4DBCF4);
        sub_422860();
        sub_42AD50();
        sub_423360();
        sub_4279F0(dword_4DBCF4);
        if (dword_4E5FB0 & 1) {
            if (dword_4E5FB4 || sub_416D40()) {
                sub_406E10(dword_4EB750, 0);
                sub_40B2A0();
            } else {
                sub_420F90();
            }
            if (dword_4E5FAC == 1)
                paintDDSurface(0);
            sub_41E450(&gGame);
        }
        sub_422860();
        sub_42AD50();
        if (dword_4E5FB4 == 1 || dword_4E6098 & 9 || !dword_4E6098) {
            if (!dword_4E5FC4 || sub_416D40())
                dword_44E118 &= 0xFFFFFFFC;
            if (!(dword_44E118 & 8))
                dword_4E5FC4 &= 0xFFFFFFF7;
            gModifierKeyState &= 0xFFFFFFFD;
            if (dword_4E5FB0 & 2) {
                dword_4E60C8 = 0;
                dword_4E60DC = -1;
            }
        }
        result = 1;
    }
    return result;
}
