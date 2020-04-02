//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBALS_H
#define OPENHEXPLORE_GLOBALS_H

#include <windows.h>
#include "interop/interop.hpp"

inline hexp_global<int, 0x4EB780> gCmdEpisode;
inline hexp_global<int, 0x5730DC> dword_5730DC;
inline hexp_global<HWND, 0x5730E0> gHWnd;
inline hexp_global<HINSTANCE, 0x573528> gHInstance;
inline hexp_global<HANDLE, 0x58B440> gHMutex;
inline hexp_global<void *, 0x44CDAC> dword_44CDAC;
inline hexp_global<int, 0x44CDB0> dword_44CDB0;
inline hexp_global<int, 0x44CDB4> dword_44CDB4;
inline hexp_global<int, 0x44CDB8> dword_44CDB8;
inline hexp_global<int, 0x44CDC0> dword_44CDC0;
inline hexp_global<int, 0x44CDC4> dword_44CDC4;
inline hexp_global<int, 0x44CDBC> dword_44CDBC;
inline hexp_global<int, 0x44CDC8> dword_44CDC8;

#endif //OPENHEXPLORE_GLOBALS_H
