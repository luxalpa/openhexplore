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

#define gCurrentVideoPath HEXP_ADDRESS(0x44CAC8, char) // 0x100 elements ; We don't know if this is only for videos yet
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
#define unk_44E110 HEXP_GLOBAL(0x44E110, int)
#define unk_44E114 HEXP_GLOBAL(0x44E114, int)
#define dword_44E118 HEXP_GLOBAL(0x44E118, int)
#define unk_44E11C HEXP_GLOBAL(0x44E11C, int)
#define unk_44E120 HEXP_GLOBAL(0x44E120, int)
#define gpDDSurfaceMemory HEXP_GLOBAL(0x44E15C, LPVOID)
#define gLangPrefix HEXP_ADDRESS(0x44E1F0, char) // 3 elements, // = "XX"
#define dword_44E400 HEXP_ADDRESS(0x44E400, int)
#define dword_44F340 HEXP_ADDRESS(0x44F340, int)

#define dword_4DBCBC HEXP_GLOBAL(0x4DBCBC, int)
#define dword_4DBCC0 HEXP_GLOBAL(0x4DBCC0, int)
#define dword_4DBCC4 HEXP_GLOBAL(0x4DBCC4, int)
#define dword_4DBCC8 HEXP_GLOBAL(0x4DBCC8, int)
#define dword_4DBCF4 HEXP_GLOBAL(0x4DBCF4, int)
#define dword_4DBCF8 HEXP_GLOBAL(0x4DBCF8, int) // = -1
#define unk_4DBD00 HEXP_GLOBAL(0x4DBD00, int)
#define dword_4E5DA8 HEXP_GLOBAL(0x4E5DA8, int)
#define dword_4E5DB0 HEXP_GLOBAL(0x4E5DB0, int)
#define dword_4E5FA8 HEXP_GLOBAL(0x4E5FA8, int)
#define dword_4E5FAC HEXP_GLOBAL(0x4E5FAC, int) // is set to 2 when playing a video
#define dword_4E5FB0 HEXP_GLOBAL(0x4E5FB0, int)
#define dword_4E5FB4 HEXP_GLOBAL(0x4E5FB4, int)
#define dword_4E5FB8 HEXP_GLOBAL(0x4E5FB8, int)
#define dword_4E5FBC HEXP_GLOBAL(0x4E5FBC, int)
#define dword_4E5FC0 HEXP_GLOBAL(0x4E5FC0, int)
#define dword_4E5FC4 HEXP_GLOBAL(0x4E5FC4, int)
#define dword_4E5FC8 HEXP_GLOBAL(0x4E5FC8, int)
#define dword_4E5FCC HEXP_GLOBAL(0x4E5FCC, int)
#define dword_4E5FD0 HEXP_GLOBAL(0x4E5FD0, int)
#define dword_4E5FD4 HEXP_GLOBAL(0x4E5FD4, int)
#define dword_4E5FD8 HEXP_GLOBAL(0x4E5FD8, int)
#define dword_4E5FDC HEXP_GLOBAL(0x4E5FDC, int)
#define dword_4E5FE0 HEXP_GLOBAL(0x4E5FE0, int) // = 1
#define dword_4E5FF4 HEXP_GLOBAL(0x4E5FF4, int)
#define dword_4E607C HEXP_GLOBAL(0x4E607C, int)
#define dword_4E6098 HEXP_GLOBAL(0x4E6098, int)
#define dword_4E60B4 HEXP_GLOBAL(0x4E60B4, int)
#define dword_4E60B8 HEXP_GLOBAL(0x4E60B8, int)
#define dword_4E60C8 HEXP_GLOBAL(0x4E60C8, int)
#define dword_4E60DC HEXP_GLOBAL(0x4E60DC, int) // = -1
#define dword_4E60E0 HEXP_GLOBAL(0x4E60E0, int) // = -1

// All data after 004E7000 is not part of the .exe

#define dword_4EB750 HEXP_ADDRESS(0x4EB750, int)
#define gGame HEXP_GLOBAL(0x4EB780, Game)

#define dword_5730DC HEXP_GLOBAL(0x5730DC, int)
#define gHWnd HEXP_GLOBAL(0x5730E0, HWND)
#define gpPalEntries2 HEXP_ADDRESS(0x5730F0, PALETTEENTRY) // 0x100 elements
#define gClipper HEXP_GLOBAL(0x5734F0, IDirectDrawClipper*)
#define gWndClass HEXP_GLOBAL(0x573500, WNDCLASSA)
#define gHInstance HEXP_GLOBAL(0x573528, HINSTANCE)
#define gpPalEntries HEXP_ADDRESS(0x573530, PALETTEENTRY)
#define dword_574240 HEXP_GLOBAL(0x574240, char*)
#define gTextDBData HEXP_GLOBAL(0x574A18, char*)
#define gHMutex HEXP_GLOBAL(0x58B440, HANDLE)

#endif //OPENHEXPLORE_GLOBALS_H
