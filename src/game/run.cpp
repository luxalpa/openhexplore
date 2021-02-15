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
#include "../keys.h"
#include "../sound.h"
#include "../sounddb.h"
#include "../random.h"
#include "engine_init.h"

void sub_414530() {
    sub_4214F0(25);
    sub_421580(0, 1, 1, 150, 90, 2);
    sub_421580(0, 0, 90, 640, 300, 1);
    sub_421580(0, 614, 1, 25, 25, 5);
    sub_421580(0, 614, 27, 25, 25, 6);
    sub_421580(0, 614, 53, 25, 25, 7);
    sub_421580(0, 1, 1, 637, 89, 3);
    sub_421580(0, 268, 391, 108, 86, 8);
    sub_421580(0, 1, 390, 637, 88, 4);
    dword_4E5F7C = 305;
    dword_4E5F80 = 80;
    dword_4E5F84 = 40;
    dword_4E5F94 = 305;
    dword_4E5F98 = 80;
    dword_4E5F9C = 40;
    dword_4E5F78 = 236;
    dword_4E5F90 = 324;
}

// @ 414C80
void playVideo(PlayVideoMode mode, int episode, int level) {
    if (mode == PlayVideoMode::LevelVideo) {
        sprintf(gCurrentVideoPath, "%s\\%s\\%s\\%s%01d%s%02d%s", "SAMPLE", gLangPrefix, "video", "E", episode, "L",
                level,
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
bool sub_426590() {
    int v1; // eax
    unsigned int v2; // eax
    int v3; // eax
    int *v4; // ecx
    int v5; // eax

    static int introState = -1;

    if (dword_4E5FA8) {
        // Set at the end of the program when pressing quit
        return false;
    }

    // This is only true at the start
    if (introState == -1) {
        showCursor(false);
        introState = 0;
    }

    if (introState == 0) {
        if (showLogos())
            return true;

        // Reached after the 2 logo screens
        dword_4DBCF4 = (int) &dword_4DBD00;
        dword_4E6098 = 0;
        dword_4E5FF4 = 0;
        dword_4E5FAC = 1;
        sub_429620(); // Shows Hexplore Screen
        playVideo(PlayVideoMode::GameIntro, 0, 0);
        dword_4E5FB8 = 2;
        introState = 1;
        return true;
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
            return true;
        case 3:
            // Credits
            sub_414E40();
            return true;
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
    }
    return true;
}

// @ 429620
int sub_429620() {
    initDirectSound(0, 0x180000);

    loadSoundbankHeaders();
    loadTxtSmpBin();
    initSoundBuffer(102400);

    dword_4EB77C = static_cast<char *>(allocFile(192000, 0x8001));

    loadFonts();

    sub_415D80(); // TODO: Find out wtf this is // sets dword_4E6198 to 397425
    showHexploreLogo();

    gMusicSmpBinPos = loadMusicSmpBin();
    gSysSmpBinPos = loadSysSmpBin();

    playSoundEffect(gSysSmpBinPos, 5);

    createRandArray();
    initVoiceRNG(); // creates arrays with random numbers
    sub_415D30(); // -----^

    sub_414530();

    sub_420130(&dword_4DBCE8, 0x6000);

    initAnimatedObjects();
    sub_409050();
    sub_406B60(dword_4EB750);
    sub_40B7E0();
    sub_410E10(&gGame);
    sub_425700(&gGame);
    sub_4112A0(&gGame);
    sub_417DB0();
    sub_4257D0(&gGame);
    sub_40C830(&gGame);

    trackKey(VK_LEFT, 0);
    trackKey(VK_UP, 1);
    trackKey(VK_RIGHT, 2);
    trackKey(VK_DOWN, 3);
    trackKey(VK_INSERT, 4);
    trackKey(VK_HOME, 5);
    trackKey(VK_PRIOR, 6);
    trackKey(VK_DELETE, 7);
    trackKey(VK_END, 8);
    trackKey(VK_NEXT, 9);

    sub_40B760(&Fnt16);
    sub_40B770(-10);

    int initialTickCount = GetTickCount();
    while (GetTickCount() < initialTickCount + 1500);

    sub_420480();
    return sub_420170(&gGame);
}