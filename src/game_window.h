//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GAME_WINDOW_H
#define OPENHEXPLORE_GAME_WINDOW_H

#include <windows.h>
#include <ddraw.h>

struct HexpPaletteEntry {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void destroyDDraw();
bool createGameWindow(HINSTANCE hInstance, int nCmdShow);
void paintDDSurface(const void *img);
LPVOID getDDrawSurfaceMemPtr();
HRESULT releaseDDrawSurfaceMem();
void initDDrawPalette(const HexpPaletteEntry *palette);
void fillDDrawPalette();
int showCursor(BOOL bShow);
[[noreturn]] void exitSilently(int code);
[[noreturn]] void exitWithFileError(int errorCode, LPCSTR lpText);
LRESULT WINAPI mainWindowHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif //OPENHEXPLORE_GAME_WINDOW_H
