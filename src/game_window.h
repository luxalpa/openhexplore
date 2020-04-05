//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GAME_WINDOW_H
#define OPENHEXPLORE_GAME_WINDOW_H

#include <windows.h>
#include <ddraw.h>

bool createGameWindow(HINSTANCE hInstance, int nCmdShow);
void destroyDDraw();
LPVOID getDDrawSurfaceMemPtr();
HRESULT releaseDDrawSurfaceMem();
void fillDDrawPalette();
int showCursor(BOOL bShow);
[[noreturn]] void exitSilently(int code);
[[noreturn]] void exitWithFileError(int errorCode, LPCSTR lpText);
LRESULT WINAPI mainWindowHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#endif //OPENHEXPLORE_GAME_WINDOW_H
