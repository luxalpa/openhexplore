//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBALS_H
#define OPENHEXPLORE_GLOBALS_H

#include "interop/interop.hpp"


#define gText_Strength HEXP_ADDRESS(0x44C500, char) // 0x32 elements
#define gText_Mechanism HEXP_ADDRESS(0x44C532, char) // 0x32 elements
#define gText_Incantation HEXP_ADDRESS(0x44C564, char) // 0x32 elements
#define gText_Agility HEXP_ADDRESS(0x44C596, char) // 0x32 elements
#define gText_ToNextLevel HEXP_ADDRESS(0x44C5C8, char) // 0x32 elements

#define gLoadedFiles HEXP_GLOBAL(0x44CDAC, FileEntryStruct *) // Lots of memory (24k)
#define gMaxTotalSize HEXP_GLOBAL(0x44CDB0, int)
#define gCurrentTotalSize HEXP_GLOBAL(0x44CDB4, int)
#define dword_44CDB8 HEXP_GLOBAL(0x44CDB8, int)
#define gNumFiles HEXP_GLOBAL(0x44CDBC, int)
#define dword_44CDC0 HEXP_GLOBAL(0x44CDC0, int) // Possibly max size ever used?
#define dword_44CDC4 HEXP_GLOBAL(0x44CDC4, int)
#define dword_44CDC8 HEXP_GLOBAL(0x44CDC8, int) // Possibly max number of files we had?

#define gDD HEXP_GLOBAL(0x44E0F4, LPDIRECTDRAW)
#define gPrimaryDDS HEXP_GLOBAL(0x44E0F8, IDirectDrawSurface*)
#define gDDS2 HEXP_GLOBAL(0x44E0FC, IDirectDrawSurface*)
#define gDDPalette HEXP_GLOBAL(0x44E100, IDirectDrawPalette*)
#define byte_44E104 HEXP_GLOBAL(0x44E104, BOOL)
#define gpDDSurfaceMemory HEXP_GLOBAL(0x44E15C, LPVOID)
#define gLangPrefix HEXP_ADDRESS(0x44E1F0, char) // 3 elements

#define gGame HEXP_GLOBAL(0x4EB780, Game)

#define dword_5730DC HEXP_GLOBAL(0x5730DC, int)
#define gHWnd HEXP_GLOBAL(0x5730E0, HWND)
#define gpPalEntries2 HEXP_ADDRESS(0x5730F0, PALETTEENTRY) // 0x100 elements
#define gClipper HEXP_GLOBAL(0x5734F0, IDirectDrawClipper*)
#define gWndClass HEXP_GLOBAL(0x573500, WNDCLASSA)
#define gHInstance HEXP_GLOBAL(0x573528, HINSTANCE)
#define gpPalEntries HEXP_ADDRESS(0x573530, PALETTEENTRY)
#define gTextDBData HEXP_GLOBAL(0x574A18, char*)
#define gHMutex HEXP_GLOBAL(0x58B440, HANDLE)

#endif //OPENHEXPLORE_GLOBALS_H
