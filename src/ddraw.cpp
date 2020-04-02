//
// Created by Smaug on 2020-04-02.
//

#include "ddraw.h"
#include "globals.h"
#include "global_fns.h"
#include <ddraw.h>
#include <cstdio>

#pragma comment(lib, "ddraw.lib")

bool initDDraw() {
    if (DirectDrawCreate(nullptr, &gDD, nullptr))
        return false;
    if (gDD->SetCooperativeLevel(gHWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))
        return false;
    if (gDD->SetDisplayMode(640, 480, 8))
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
    ddsd2.dwWidth = 640;
    ddsd2.dwHeight = 480;
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
    gWndClass.lpfnWndProc = sub_4060B0;
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

// @ 416850;
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

// @ 4169A0
void fillDDrawPalette() {
    if (byte_44E104 == TRUE) {
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

// @ 416A20
[[noreturn]] void exitWithFileError(int errorCode, LPCSTR lpText) {
    CHAR Caption[256]; // [esp+8h] [ebp-100h]

    memset(getDDrawSurfaceMemPtr(), 0, 0x4B000u);
    releaseDDrawSurfaceMem();
    fillDDrawPalette();
    showCursor(1);
    sprintf(Caption, "FILE ERROR : %d", errorCode);
    MessageBoxA(gHWnd, lpText, Caption, 0);
    exit(-1);
}