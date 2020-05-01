//
// Created by Smaug on 2020-04-02.
//

#include "game_window.h"
#include "globals.h"
#include "global_fns.h"
#include "other.h"
#include <ddraw.h>
#include <cstdio>

#pragma comment(lib, "ddraw.lib")

bool initDDraw() {
    if (DirectDrawCreate(nullptr, &gDD, nullptr))
        return false;
    if (gDD->SetCooperativeLevel(gHWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))
        return false;
    if (gDD->SetDisplayMode(WINDOW_WIDTH, WINDOW_HEIGHT, 8))
        return false;

    DDSURFACEDESC primarySurface;
    primarySurface.dwSize = sizeof(primarySurface);
    primarySurface.dwFlags = DDSD_CAPS;
    primarySurface.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    if (gDD->CreateSurface(&primarySurface, &gPrimaryDDS, nullptr) != DD_OK) {
        return false;
    }

    DDSURFACEDESC ddsd2;
    ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd2.dwSize = sizeof(ddsd2);
    ddsd2.dwWidth = WINDOW_WIDTH;
    ddsd2.dwHeight = WINDOW_HEIGHT;
    ddsd2.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

    if (gDD->CreateSurface(&ddsd2, &gDDS2, nullptr) != DD_OK) {
        return false;
    }
    if (gDD->CreateClipper(0, &gClipper, nullptr) != DD_OK) {
        return false;
    }
    if (gClipper->SetHWnd(0, gHWnd) != DD_OK) {
        return false;
    }
    if (gPrimaryDDS->SetClipper(gClipper) != DD_OK) {
        return false;
    }
    return true;
}

// @ 405DC0
void destroyDDraw() {
    if (gDD) {
        if (gPrimaryDDS) {
            gPrimaryDDS->Release();
            gPrimaryDDS = nullptr;
        }
        if (gDDS2) {
            gDDS2->Release();
            gDDS2 = nullptr;
        }
        gDD->Release();
        gDD = nullptr;
    }
}

// @ 405E20
bool createGameWindow(HINSTANCE hInstance, int nCmdShow) {
    gWndClass.style = 3;
    gWndClass.lpfnWndProc = mainWindowHandler;
    gWndClass.cbClsExtra = 0;
    gWndClass.cbWndExtra = 0;
    gWndClass.hInstance = hInstance;
    gWndClass.hIcon = LoadIconA(hInstance, IDI_APPLICATION);
    gWndClass.hCursor = LoadCursorA(nullptr, IDI_APPLICATION);
    gWndClass.lpszMenuName = "HEXPLORE";
    gWndClass.lpszClassName = "HEXPLORE";
    gWndClass.hbrBackground = nullptr;
    RegisterClassA(&gWndClass);

    gHWnd = CreateWindowExA(WS_EX_TOPMOST, "HEXPLORE", "HEXPLORE", WS_POPUP, 0, 0, GetSystemMetrics(0),
                            GetSystemMetrics(1),
                            nullptr, nullptr, hInstance, nullptr);
    if (!gHWnd)
        return false;

    ShowWindow(gHWnd, nCmdShow);
    UpdateWindow(gHWnd);

    if (!initDDraw()) {
        destroyDDraw();
        DestroyWindow(gHWnd);
        return false;
    }

    return true;
}

// @ 416710
void paintDDSurface(const void *img) {
    if (!gIsWindowActive) return;

    if (img) {
        _DDSURFACEDESC surface;
        surface.dwSize = sizeof(surface);
        if (!gDDS2->Lock(nullptr, &surface, DDLOCK_SURFACEMEMORYPTR, nullptr)) {
            memcpy(surface.lpSurface, img, WINDOW_WIDTH * WINDOW_HEIGHT);
            gDDS2->Unlock(surface.lpSurface);
        }
    }

    while (true) {
        if (pointsTo1(dword_4EB750))
            sub_421130(dword_44E110, dword_44E114, 1);
        tagRECT rect;
        DDBLTFX ddbltfx;

        rect.left = 0;
        rect.top = 0;
        rect.right = WINDOW_WIDTH;
        rect.bottom = WINDOW_HEIGHT;
        memset(&ddbltfx, 0, sizeof(ddbltfx));
        ddbltfx.dwSize = sizeof(ddbltfx);
        HRESULT err = gPrimaryDDS->Blt(&rect, gDDS2, &rect, DDBLT_WAIT, &ddbltfx);
        if (err == DDERR_SURFACELOST) {
            if (gPrimaryDDS->Restore())
                break;
        }
        if (err != DDERR_WASSTILLDRAWING) {
            if (pointsTo1(dword_4EB750))
                sub_421470(1);
            break;
        }
    }
}

// @ 416850
LPVOID getDDrawSurfaceMemPtr() {
    _DDSURFACEDESC dds;

    if (!gpDDSurfaceMemory) {
        dds.dwSize = sizeof(_DDSURFACEDESC);
        if (gDDS2->Lock(0, &dds, 0, 0) != DD_OK)
            SendMessageA(gHWnd, WM_DESTROY, 0, 0);
        gpDDSurfaceMemory = dds.lpSurface;
    }
    return gpDDSurfaceMemory;
}

// @ 4168B0
HRESULT releaseDDrawSurfaceMem() {
    HRESULT result = gDDS2->Unlock(gpDDSurfaceMemory);
    gpDDSurfaceMemory = 0;
    return result;
}

// @ 4168D0
void initDDrawPalette(HexpPaletteEntry *palette) {
    if (!gIsPaletteInitialized) {
        HDC dc = GetDC(gHWnd);
        GetSystemPaletteEntries(dc, 0, 0x100u, gpPalEntries);
        ReleaseDC(gHWnd, dc);
        gIsPaletteInitialized = true;
    }
    if (palette) {
        for(int i = 0; i < 0x100; i++) {
            PALETTEENTRY *entry = &gpPalEntries2[i];
            HexpPaletteEntry *source = &palette[i];

            entry->peRed = source->red;
            entry->peGreen = source->green;
            entry->peBlue = source->blue;
            entry->peFlags = 5;
        }
    }
    if (gDDPalette) {
        gDDPalette->SetEntries(0, 0, 0x100, gpPalEntries2);
    } else {
        gDD->CreatePalette(DDPCAPS_ALLOW256 | DDPCAPS_8BIT, gpPalEntries2, &gDDPalette, nullptr);
        gPrimaryDDS->SetPalette(gDDPalette);
    }
}

// @ 4169A0
void fillDDrawPalette() {
    if (gIsPaletteInitialized == TRUE) {
        if (gDDPalette) {
            gDDPalette->SetEntries(0, 0, 256, gpPalEntries);
            memcpy(gpPalEntries2, gpPalEntries, 0x400u);
        }
    }
}

// @ 4169E0
int showCursor(BOOL bShow) {
    return ShowCursor(bShow);
}

// @ 4169F0
[[noreturn]] void exitSilently(int code) {
    setRegistryValue(true, nullptr, "LastError:", RegistryValueType::Number, (LPCSTR) &code);
    showCursor(true);
    exit(-1);
}

// @ 416A20
[[noreturn]] void exitWithFileError(int errorCode, LPCSTR lpText) {
    CHAR Caption[256];

    memset(getDDrawSurfaceMemPtr(), 0, WINDOW_HEIGHT * WINDOW_WIDTH);
    releaseDDrawSurfaceMem();
    fillDDrawPalette();
    showCursor(1);
    sprintf(Caption, "FILE ERROR : %d", errorCode);
    MessageBoxA(gHWnd, lpText, Caption, 0);
    exit(-1);
}

// @ 4060B0
LRESULT WINAPI mainWindowHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    LONG v5; // eax
    char v6; // [esp+10h] [ebp-44h]
    struct tagPAINTSTRUCT Paint; // [esp+14h] [ebp-40h]

    LRESULT result = keycodeHandler(msg, wParam, lParam);
    if (result) {
        // The message has already been handled.
        return 1;
    }

    switch (msg) {
        case WM_SETFOCUS:
            dword_44E11C = 0;
            break;
        case WM_DESTROY:
            sub_429AC0();
            sub_415750();
            destroyDDraw();
            ReleaseMutex(gHMutex);
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            BeginPaint(hWnd, &Paint);
            if (gDD)
                paintDDSurface(nullptr);
            EndPaint(hWnd, &Paint);
            break;
        case WM_ACTIVATEAPP:
            gIsWindowActive = wParam;
            dword_44E11C = 0;
            if (gIsWindowActive) {
                if (gPrimaryDDS)
                    gPrimaryDDS->Restore();
                if (gDDS2)
                    gDDS2->Restore();
                if (gDDPalette)
                    gDDPalette->SetEntries(0, 0, 256, gpPalEntries2);
            }
            break;
        case WM_SETCURSOR:
            SetCursor(gWndClass.hCursor);
            return 1;
        case WM_KEYDOWN:
            if (!dword_44E11C) {
                if (wParam == VK_SHIFT) {
                    gModifierKeyState |= 1u;
                } else if (wParam == VK_CONTROL) {
                    if (!(lParam & 0x40000000))
                        gModifierKeyState |= 2u;
                } else {
                    dword_44E11C = wParam;
                }
            }
            break;
        case WM_KEYUP:
            if (wParam == VK_SHIFT) {
                gModifierKeyState &= 0xFFFFFFFE;
            }
            break;
        case WM_MOUSEMOVE:
            if (dword_44E158 == 1) {
                dword_44E110 = (unsigned __int16) lParam;
                dword_44E148 = (unsigned __int16) lParam;
                dword_44E114 = (unsigned int) lParam >> 16;
                dword_44E14C = (unsigned int) lParam >> 16;
                if ((abs((unsigned __int16) lParam - dword_44E150) > 10 ||
                     abs(dword_44E114 - dword_44E154) > 10)
                    && GetMessageTime() - dword_440044 > 50) {
                    dword_44E158 = 2;
                }
            } else if (dword_44E158 == 2) {
                dword_44E110 = (unsigned __int16) lParam;
                dword_44E148 = (unsigned __int16) lParam;
                dword_44E114 = (unsigned int) lParam >> 16;
                dword_44E14C = (unsigned int) lParam >> 16;
            } else if (!(dword_44E118 & 1)) {
                dword_44E110 = (unsigned __int16) lParam;
                dword_44E114 = (unsigned int) lParam >> 16;
            }
            if (dword_44004C == 1
                && (abs(dword_4E60CC - dword_44E110) > 20
                    || abs(dword_4E60D0 - dword_44E114) > 20
                    || GetMessageTime() - dword_440048 > 120)) {
                dword_44004C = 2;
                dword_44E118 |= 8u;
            }
            dword_440040 = wParam;
            break;
        case WM_LBUTTONDOWN:
            dword_44004C = 0;
            dword_44E118 &= 0xFFFFFFF5;
            dword_44E110 = (unsigned __int16) lParam;
            dword_44E114 = (unsigned int) lParam >> 16;
            if (sub_421640(0, (unsigned __int16) lParam, (unsigned int) lParam >> 16,
                           (int *) &v6) != 1
                || dword_4E5FAC != 1) {
                dword_44E158 = 0;
                dword_44E118 |= 5u;
            } else {
                dword_44E148 = dword_44E110;
                dword_44E150 = dword_44E110;
                dword_44E14C = dword_44E114;
                dword_44E154 = dword_44E114;
                dword_440044 = GetMessageTime();
                dword_44E158 = 1;
                sub_429BB0(dword_4DBCF4 + 176, dword_44E150, dword_44E154, &dword_4E60D4,
                           &dword_4E60D8);
            }
            break;
        case WM_LBUTTONUP:
            dword_44E110 = (unsigned __int16) lParam;
            dword_44E114 = (unsigned int) lParam >> 16;
            if (dword_44E158) {
                dword_44E148 = dword_44E110;
                dword_44E14C = dword_44E114;
                if (dword_44E158 == 1
                    && (abs(dword_44E110 - dword_44E150) > 10 ||
                        abs(dword_44E114 - dword_44E154) > 10)
                    && GetMessageTime() - dword_440044 > 50) {
                    dword_44E158 = 2;
                }
                if (dword_44E158 == 2) {
                    dword_44E158 = 3;
                } else {
                    dword_44E118 |= 1u;
                    dword_44E110 = dword_44E150;
                    dword_44E158 = 0;
                    dword_44E114 = dword_44E154;
                }
            }
            dword_44E118 &= 0xFFFFFFFB;
            break;
        case WM_RBUTTONDOWN:
            dword_44E110 = (unsigned __int16) lParam;
            dword_44E118 &= 0xFFFFFFFA;
            dword_44E158 = 0;
            dword_44E114 = (unsigned int) lParam >> 16;
            if (sub_421640(0, (unsigned __int16) lParam, (unsigned int) lParam >> 16,
                           (int *) &v6) == 1) {
                dword_4E60CC = dword_44E110;
                dword_4E60D0 = dword_44E114;
                v5 = GetMessageTime();
                dword_44004C = 1;
                dword_440048 = v5;
            } else {
                dword_44004C = 0;
                dword_44E118 |= 0xAu;
            }
            break;
        case WM_RBUTTONUP:
            dword_44E110 = (unsigned __int16) lParam;
            dword_44E114 = (unsigned int) lParam >> 16;
            if (dword_44004C == 1) {
                if (abs(dword_4E60CC - dword_44E110) > 20
                    || abs(dword_4E60D0 - dword_44E114) > 20
                    || GetMessageTime() - dword_440048 > 120) {
                    dword_44004C = 0;
                } else {
                    dword_44004C = 0;
                    dword_4E60C8 = 1;
                }
                dword_44E118 = 0;
            } else {
                dword_44E118 &= 0xFFFFFFF7;
            }
            break;
        case WM_QUERYNEWPALETTE:
            if (gDDPalette)
                gDDPalette->SetEntries(0, 0, 256, gpPalEntries2);
            break;
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}