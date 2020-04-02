//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBALS_H
#define OPENHEXPLORE_GLOBALS_H

#include <windows.h>
#include "interop/interop.hpp"

inline loco_global<int, 0x4EB780> gEpisode;
inline loco_global<int, 0x4EB784> gLevel;
inline loco_global<int, 0x4EB788> dword_4EB788; // map?

inline loco_global<void *, 0x44CDAC> dword_44CDAC;
inline loco_global<int, 0x44CDB0> dword_44CDB0;
inline loco_global<int, 0x44CDB4> dword_44CDB4;
inline loco_global<int, 0x44CDB8> dword_44CDB8;
inline loco_global<int, 0x44CDC0> dword_44CDC0;
inline loco_global<int, 0x44CDC4> dword_44CDC4;
inline loco_global<int, 0x44CDBC> dword_44CDBC;
inline loco_global<int, 0x44CDC8> dword_44CDC8;

inline loco_global<int, 0x5730DC> dword_5730DC;
inline loco_global<HWND, 0x5730E0> gHWnd;
inline loco_global<WNDCLASSA, 0x573500> gWndClass;
inline loco_global<HINSTANCE, 0x573528> gHInstance;
inline loco_global<HANDLE, 0x58B440> gHMutex;

#endif //OPENHEXPLORE_GLOBALS_H
