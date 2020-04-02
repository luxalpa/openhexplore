//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBALS_H
#define OPENHEXPLORE_GLOBALS_H

#include <windows.h>
#include "interop/interop.hpp"

#define gEpisode HEXP_GLOBAL(0x4EB780, int) // 0x4EB780
#define gLevel HEXP_GLOBAL(0x4EB784, int)
#define dword_4EB788 HEXP_GLOBAL(0x4EB788, int) // map?

#define dword_44CDAC HEXP_GLOBAL(0x44CDAC, void *)
#define dword_44CDB0 HEXP_GLOBAL(0x44CDB0, int)
#define dword_44CDB4 HEXP_GLOBAL(0x44CDB4, int)
#define dword_44CDB8 HEXP_GLOBAL(0x44CDB8, int)
#define dword_44CDC0 HEXP_GLOBAL(0x44CDC0, int)
#define dword_44CDC4 HEXP_GLOBAL(0x44CDC4, int)
#define dword_44CDBC HEXP_GLOBAL(0x44CDBC, int)
#define dword_44CDC8 HEXP_GLOBAL(0x44CDC8, int)

#define dword_5730DC HEXP_GLOBAL(0x5730DC, int)
#define gHWnd HEXP_GLOBAL(0x5730E0, HWND)
#define gWndClass HEXP_GLOBAL(0x573500, WNDCLASSA)
#define gHInstance HEXP_GLOBAL(0x573528, HINSTANCE)
#define gHMutex HEXP_GLOBAL(0x58B440, HANDLE)

#endif //OPENHEXPLORE_GLOBALS_H
