//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBAL_FNS_H
#define OPENHEXPLORE_GLOBAL_FNS_H

#include <windef.h>
#include "game/meta.h"
#include "textdb.h"

//inline auto sub_4060B0 = (LRESULT (WINAPI *const)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)) 0x4060B0;

inline auto hexp_open = (bool (*const)(const char *filename, int mode)) 0x42B3E0;
inline auto hexp_close = (bool (*const)(int fd)) 0x42E030;
inline auto hexp_filelength = (bool (*const)(int fd)) 0x432360;
inline auto hexp_malloc = (void * (*const)(size_t)) 0x42BAE0;

inline auto sub_406C80 = (int (*const)(int *a1)) 0x406C80;
inline auto sub_406E10 = (int (*const)(int*, int)) 0x406E10;
inline auto sub_406E20 = (int (*const)(int*)) 0x406E20;
inline auto sub_40A970 = (int (*const)()) 0x40A970;
inline auto sub_40A9F0 = (int (*const)()) 0x40A9F0;
inline auto sub_40AB10 = (int (*const)()) 0x40AB10;
inline auto sub_40B2A0 = (int (*const)()) 0x40B2A0;
inline auto sub_40EA00 = (int (*const)(int*, int)) 0x40EA00;
inline auto sub_413A80 = (int (*const)(int)) 0x413A80;
inline auto sub_414270 = (int (*const)(int)) 0x414270;
inline auto sub_414BD0 = (int (*const)()) 0x414BD0;
inline auto sub_414D30 = (int (*const)()) 0x414D30;
inline auto sub_414E40 = (int (*const)()) 0x414E40;
inline auto sub_415750 = (int (*const)()) 0x415750;
inline auto sub_415E70 = (int (*const)()) 0x415E70;
inline auto sub_416710 = (int (*const)(int)) 0x416710;
inline auto sub_416BB0 = (int (*const)()) 0x416BB0;
inline auto sub_416D40 = (int (*const)()) 0x416D40;
inline auto sub_416DD0 = (int (*const)()) 0x416DD0;
inline auto sub_41E450 = (int (*const)(Game*)) 0x41E450;
inline auto showLogos = (int (*const)()) 0x4206C0;
inline auto sub_420F90 = (int (*const)()) 0x420F90;
inline auto sub_421640 = (int (*const)(int, int, int, int*)) 0x421640;
inline auto sub_4227B0 = (int (*const)(int, int)) 0x4227B0;
inline auto sub_422860 = (int (*const)()) 0x422860;
inline auto sub_423360 = (int (*const)()) 0x423360;
inline auto sub_426A70 = (int (*const)()) 0x426A70;
inline auto sub_427290 = (int (*const)()) 0x427290;
inline auto sub_4279F0 = (int (*const)(int)) 0x4279F0;
inline auto sub_429620 = (int (*const)()) 0x429620;
inline auto sub_429AC0 = (int (*const)()) 0x429AC0;
inline auto sub_429BB0 = (int (*const)(int, int, int, int*, int*)) 0x429BB0;
inline auto sub_42AC70 = (int (*const)(int, int, int)) 0x42AC70;
inline auto sub_42AD50 = (int (*const)()) 0x42AD50;

#endif //OPENHEXPLORE_GLOBAL_FNS_H
