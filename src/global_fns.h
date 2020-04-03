//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBAL_FNS_H
#define OPENHEXPLORE_GLOBAL_FNS_H

#include <windef.h>
#include "game.h"
#include "textdb.h"

inline auto sub_426590 = (signed int (*const)()) 0x426590;
inline auto sub_4160A0 = (void (*const)(char *a1, unsigned int a2, struc_2*)) 0x4160A0;
inline auto sub_4060B0 = (LRESULT (WINAPI *const)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)) 0x4060B0;

inline auto hexp_open = (bool (*const)(const char *filename, int mode)) 0x42B3E0;
inline auto hexp_close = (bool (*const)(int fd)) 0x42E030;
inline auto hexp_filelength = (bool (*const)(int fd)) 0x432360;


#endif //OPENHEXPLORE_GLOBAL_FNS_H
