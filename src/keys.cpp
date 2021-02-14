//
// Created by Smaug on 2020-05-01.
//

#include <windows.h>
#include "keys.h"
#include "globals.h"
#include "global_fns.h"
#include "sound.h"
#include "helpers/debug.h"

// @ 4159A0
LRESULT keycodeHandler(UINT msg, WPARAM wparam, LPARAM lparam) {
    unsigned int result; // eax
    char v7; // cl
    int v8; // edx
    int v9; // edi

    result = true;
    switch (msg) {
        case WM_KEYDOWN:
            if (wparam == VK_SHIFT) {
                gModifierKeyState |= 1u;
                return TRUE;
            } else {
                if (wparam == VK_CONTROL) {
                    // TODO: We could remove this but it works based on the auto key repeat feature in windows, so there would be a delay.
                    // previous key state
                    if (!(lparam & 0x40000000))
                        gModifierKeyState |= 2u;
                } else {
                    int v4 = 0;
                    int *pKeyCode = gTrackedKeyStates;
                    while (*pKeyCode != wparam) {
                        ++pKeyCode;
                        ++v4;
                        if (pKeyCode >= &dword_4EA3B0)
                            goto LABEL_12;
                    }
                    dword_4EA2D8 |= 1 << v4;
                    LABEL_12:
                    unsigned int nextCachePos = (gKeyCacheIdx + 1) % 10;
                    if (nextCachePos == gKeyCacheIdxLastKey) { // If we run out of cache space
                        if (wparam != VK_BACK) {
                            playSoundAtFullVolume(gSysSmpBinPos, 20);
                            return TRUE;
                        }
                    } else if (wparam == VK_BACK || !(lparam & 0x40000000)) {
                        gKeyCache[gKeyCacheIdx] = wparam;
                        gKeyCacheIdx = nextCachePos;
                        return TRUE;
                    }
                }
                return TRUE;
            }
        case WM_KEYUP:
            if (wparam == VK_SHIFT) {
                result = gModifierKeyState & 0xFFFFFFFE;
                gModifierKeyState &= 0xFFFFFFFE;
            } else if (wparam != VK_CONTROL) {
                v7 = 0;
                result = (unsigned int) gTrackedKeyStates;
                while (*(int *) result != wparam) {
                    result += 4;
                    ++v7;
                    if (result >= (unsigned int) &dword_4EA3B0)
                        return result;
                }
                v8 = ~(1 << v7);
                result = v8 & dword_4EA2D8;
                dword_4EA2D8 &= v8;
            }
            break;
        case WM_CHAR:
            result = dword_44CDDC;
            if (dword_44CDDC) {
                v9 = dword_44CDD4;
                result = (dword_44CDD4 + 1) / 10;
                if (dword_44CDD8 == (dword_44CDD4 + 1) % 10) {
                    result = playSoundAtFullVolume(gSysSmpBinPos, 20);
                } else {
                    dword_44CDD4 = (dword_44CDD4 + 1) % 10;
                    dword_4EA308[v9] = wparam;
                }
            }
            break;
        default:
            return FALSE;
    }
    return result;
}

// Gets key from queue
// @ 415B40
int processKey() {
    if (gKeyCacheIdxLastKey == gKeyCacheIdx)
        return 0;

    int key = gKeyCache[gKeyCacheIdxLastKey];
    gKeyCacheIdxLastKey = (gKeyCacheIdxLastKey + 1) % 10;
    return key;
}

// @ 415BB0
bool trackKey(int keyCode, char bit) {
    if (bit >= 32)
        return false;

    gTrackedKeyStates[bit] = keyCode;
    return true;
}

// RNG for the voice lines
// @ 415CE0
void initVoiceRNG() {
    for(int i = 0; i < 128; i++) {
        voiceRNGTable[i] = rand();
    }
}

// @ 415D30
void sub_415D30() {
    for(int i = 0; i < 128; i++) {
        dword_44CFE8[i] = rand();
    }
}