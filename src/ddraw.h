//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_DDRAW_H
#define OPENHEXPLORE_DDRAW_H

#include <windows.h>
#include <ddraw.h>

bool createGameWindow(HINSTANCE hInstance, int nCmdShow);
void destroyDDraw();
LPVOID getDDrawSurfaceMemPtr();
HRESULT releaseDDrawSurfaceMem();
void fillDDrawPalette();
int showCursor(BOOL bShow);
[[noreturn]] void exitWithFileError(int errorCode, LPCSTR lpText);

#endif //OPENHEXPLORE_DDRAW_H
