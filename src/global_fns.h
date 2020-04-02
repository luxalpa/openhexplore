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
inline auto sub_406E40 = (int (*const)(LPCSTR lpText, int a2)) 0x406E40;
inline auto sub_4157D0 = (int (*const)(size_t a1, int a2)) 0x4157D0;
inline auto sub_406FC0 = (int (*const)(int a1, void *a2, unsigned int a3)) 0x406FC0;
inline auto sub_407000 = (bool (*const)(int a1)) 0x407000;
//inline auto getSize = (bool (*const)(int fd)) 0x406F60;
//inline auto sub_416000 = (bool (*const)(char*, char**, bool)) 0x416000;

inline auto hexp_open = (bool (*const)(const char *filename, int mode)) 0x42B3E0;
inline auto hexp_close = (bool (*const)(int fd)) 0x42E030;
inline auto hexp_filelength = (bool (*const)(int fd)) 0x432360;


#endif //OPENHEXPLORE_GLOBAL_FNS_H
