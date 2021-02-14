//
// Created by Smaug on 2020-06-07.
//

#include <cstdio>
#include "debug.h"
#include <windows.h>
#include "../globals.h"

void printMessage(const char *formatStr, ...) {
    va_list args;

    char buf[1024];
    va_start(args, formatStr);
    vsprintf_s(buf, sizeof(buf), formatStr, args);
    va_end(args);
    MessageBoxA(gHWnd, buf, "Debug", MB_OK);
}