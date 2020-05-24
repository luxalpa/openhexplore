//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GLOBALS_H
#define OPENHEXPLORE_GLOBALS_H

#include "interop/interop.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define NUM_SOUNDBANKS 2
#define NUM_SOUNDINSTANCES 8
#define NUM_SOUNDTEMPLATES 80

#define dword_440040        GLOB(0x440040, int)
#define dword_440044        GLOB(0x440044, int)
#define dword_440048        GLOB(0x440048, int)
#define dword_44004C        GLOB(0x44004C, int)
#define gSysSmpBinData      GLOB(0x4400D8, SmpBinEntry *)
#define gMusicSmpBinData    GLOB(0x4400DC, SmpBinEntry *)
#define gPosSmpbank         GLOB(0x4400E0, int) // = -1
#define gPosMusbank         GLOB(0x4400E4, int) // = -1
#define gTxtSmpInfoPos      GLOB(0x44C4E4, int)
#define gTxtSmpData         GLOB(0x44C4EC, SmpBinEntry *)
#define gText_Strength      ADDR(0x44C500, char) // 0x32 elements
#define gText_Mechanism     ADDR(0x44C532, char) // 0x32 elements
#define gText_Incantation   ADDR(0x44C564, char) // 0x32 elements
#define gText_Agility       ADDR(0x44C596, char) // 0x32 elements
#define gText_ToNextLevel   ADDR(0x44C5C8, char) // 0x32 elements

#define gCurrentVideoPath   ADDR(0x44CAC8, char) // 0x100 elements ; We don't know if this is only for videos yet
#define gLoadedFiles        GLOB(0x44CDAC, FileEntryStruct *) // Lots of memory (24k)
#define gMaxTotalSize       GLOB(0x44CDB0, int)
#define gCurrentTotalSize   GLOB(0x44CDB4, int)
#define dword_44CDB8        GLOB(0x44CDB8, int) // possibly some other kind of currentTotalSize
#define gNumFiles           GLOB(0x44CDBC, int)
#define dword_44CDC0        GLOB(0x44CDC0, int) // Possibly max size ever used?
#define dword_44CDC4        GLOB(0x44CDC4, int)
#define dword_44CDC8        GLOB(0x44CDC8, int) // Possibly max number of files we had?
#define gKeyCacheIdx        GLOB(0x44CDCC, int)
#define gKeyCacheIdxLastKey        GLOB(0x44CDD0, int)
#define dword_44CDD4        GLOB(0x44CDD4, int)
#define dword_44CDD8        GLOB(0x44CDD8, int)
#define dword_44CDDC        GLOB(0x44CDDC, int)
#define dword_44CDE0        ADDR(0x44CDE0, int) // 128 elements
#define dword_44CFE8        ADDR(0x44CFE8, int)

#define gDD                 GLOB(0x44E0F4, LPDIRECTDRAW)
#define gPrimaryDDS         GLOB(0x44E0F8, IDirectDrawSurface*)
#define gDDS2               GLOB(0x44E0FC, IDirectDrawSurface*)
#define gDDPalette          GLOB(0x44E100, IDirectDrawPalette*)
#define gIsPaletteInitialized   GLOB(0x44E104, bool)
#define dword_44E110        GLOB(0x44E110, int)
#define dword_44E114        GLOB(0x44E114, int)
#define dword_44E118        GLOB(0x44E118, int)
#define dword_44E11C        GLOB(0x44E11C, int)
#define gModifierKeyState   GLOB(0x44E120, int) // Modifier keys pressed?
#define gWindowWidth        GLOB(0x44E128, int) // = 640
#define gWindowHeight       GLOB(0x44E12C, int) // = 480
#define dword_44E148        GLOB(0x44E148, int)
#define dword_44E14C        GLOB(0x44E14C, int)
#define dword_44E150        GLOB(0x44E150, int)
#define dword_44E154        GLOB(0x44E154, int)
#define dword_44E158        GLOB(0x44E158, int)
#define gpDDSurfaceMemory   GLOB(0x44E15C, LPVOID)
#define gLangPrefix         ADDR(0x44E1F0, char) // 3 elements, // = "XX"
#define dword_44E400        ADDR(0x44E400, int)
#define dword_44F340        ADDR(0x44F340, int)

#define stru_4D5DE0        ADDR(0x4D5DE0, UnkSoundStruct) // 4 elements
#define gDirectSound        GLOB(0x4D5E10, LPDIRECTSOUND)
#define gDirectSoundBuffer  GLOB(0x4D5E14, IDirectSoundBuffer*)
#define gMaxAudioBufferSize GLOB(0x4D5E18, int) // = 0x100000
#define dword_4D5E28        ADDR(0x4D5E28, int) // 101 elements from 0 ~ 6643 and then 10000
//#define gNextSoundID        GLOB(0x4D5FBC, int)
#define dword_4DBCBC        GLOB(0x4DBCBC, int)
#define dword_4DBCC0        GLOB(0x4DBCC0, int)
#define dword_4DBCC4        GLOB(0x4DBCC4, int)
#define dword_4DBCC8        GLOB(0x4DBCC8, int)
#define dword_4DBCE8        GLOB(0x4DBCE8, int)
#define dword_4DBCF4        GLOB(0x4DBCF4, int)
#define dword_4DBCF8        GLOB(0x4DBCF8, int) // = -1
#define dword_4DBD00        GLOB(0x4DBD00, int)
#define dword_4E5DA8        GLOB(0x4E5DA8, int)
#define dword_4E5DB0        GLOB(0x4E5DB0, int)
#define gSysSmpBinPos       GLOB(0x4E5F58, int) // = -1
#define gMusicSmpBinPos     GLOB(0x4E5F5C, int) // = -1
#define dword_4E5F60        GLOB(0x4E5F60, int) // = 70
#define dword_4E5F68        GLOB(0x4E5F68, int) // = 400
#define dword_4E5F7C        GLOB(0x4E5F7C, int)
#define dword_4E5F80        GLOB(0x4E5F80, int)
#define dword_4E5F84        GLOB(0x4E5F84, int)
#define dword_4E5F94        GLOB(0x4E5F94, int)
#define dword_4E5F98        GLOB(0x4E5F98, int)
#define dword_4E5F9C        GLOB(0x4E5F9C, int)
#define dword_4E5F78        GLOB(0x4E5F78, int)
#define dword_4E5F90        GLOB(0x4E5F90, int)

#define dword_4E5FA8        GLOB(0x4E5FA8, int)
#define dword_4E5FAC        GLOB(0x4E5FAC, int) // is set to 2 when playing a video
#define dword_4E5FB0        GLOB(0x4E5FB0, int)
#define dword_4E5FB4        GLOB(0x4E5FB4, int)
#define dword_4E5FB8        GLOB(0x4E5FB8, int)
#define dword_4E5FBC        GLOB(0x4E5FBC, int)
#define dword_4E5FC0        GLOB(0x4E5FC0, int)
#define dword_4E5FC4        GLOB(0x4E5FC4, int)
#define dword_4E5FC8        GLOB(0x4E5FC8, int)
#define dword_4E5FCC        GLOB(0x4E5FCC, int)
#define dword_4E5FD0        GLOB(0x4E5FD0, int)
#define dword_4E5FD4        GLOB(0x4E5FD4, int)
#define dword_4E5FD8        GLOB(0x4E5FD8, int)
#define dword_4E5FDC        GLOB(0x4E5FDC, int)
#define dword_4E5FE0        GLOB(0x4E5FE0, int) // = 1
#define dword_4E5FF4        GLOB(0x4E5FF4, int)
#define dword_4E607C        GLOB(0x4E607C, int)
#define dword_4E6098        GLOB(0x4E6098, int) // Mutes the sound if certain flag is set
#define dword_4E60B4        GLOB(0x4E60B4, int)
#define dword_4E60B8        GLOB(0x4E60B8, int)
#define dword_4E60C8        GLOB(0x4E60C8, int)
#define dword_4E60CC        GLOB(0x4E60CC, int)
#define dword_4E60D0        GLOB(0x4E60D0, int)
#define dword_4E60D4        GLOB(0x4E60D4, int)
#define dword_4E60D8        GLOB(0x4E60D8, int)
#define dword_4E60DC        GLOB(0x4E60DC, int) // = -1
//#define dword_4E60E0        GLOB(0x4E60E0, int) // = -1
#define dword_4E60EC        GLOB(0x4E60EC, int) // = -1

// All data after 004E7000 is not part of the .exe

#define dword_4EA2D8        GLOB(0x4EA2D8, int) // Flags of keys pressed (in dword_4EA330)
#define gKeyCache           ADDR(0x4EA2E0, int) // 10 elements
#define dword_4EA308        ADDR(0x4EA308, int) // 10 elements
#define gTrackedKeyStates   ADDR(0x4EA330, int) // 0x20 elements; begin keycodes
#define dword_4EA3B0        GLOB(0x4EA3B0, int)
#define gAudioBufferPos     GLOB(0x4EA410, int)
#define gSoundBufferSize    GLOB(0x4EA41C, int)
#define gVolumes            ADDR(0x4EA420, int)
#define gDirectSoundBuffer2 GLOB(0x4EA444, IDirectSoundBuffer*)
#define gSBKInfos            ADDR(0x4EA450, SBKInfo) // 2 elements
#define gSoundTemplateCache  ADDR(0x4EA600, SoundTemplate) // 80 elements
#define gSoundInstanceCache  ADDR(0x4EAEC8, SoundInstance) // 8 elements
#define gSmpInfos           ADDR(0x4EAFC8, SmpInfo) // 25 elements
#define gSampleDir          ADDR(0x4EB160, char) // 256 characters
#define dword_4EB750        ADDR(0x4EB750, int)
#define gGame               GLOB(0x4EB780, Game)
#define dword_4EB77C        GLOB(0x4EB77C, char *)

#define gIsWindowActive     GLOB(0x5730DC, int)
#define gHWnd               GLOB(0x5730E0, HWND)
#define gpPalEntries2       ADDR(0x5730F0, PALETTEENTRY) // 0x100 elements
#define gClipper            GLOB(0x5734F0, IDirectDrawClipper*)
#define gWndClass           GLOB(0x573500, WNDCLASSA)
#define gHInstance          GLOB(0x573528, HINSTANCE)
#define gpPalEntries        ADDR(0x573530, PALETTEENTRY)
#define Fnt10               GLOB(0x573A00, SB0Info)
#define Fnt16               GLOB(0x574210, SB0Info)
#define dword_574240        GLOB(0x574240, char*)
#define gTextDBData         GLOB(0x574A18, char*)
#define SmFntW              GLOB(0x5759E0, SB0Info)
#define SmFntR              GLOB(0x575A10, SB0Info)
#define SmFntB              GLOB(0x575A40, SB0Info)
#define randArray           ADDR(0x575A70, unsigned char) // 0x100 elements
#define gHMutex             GLOB(0x58B440, HANDLE)

#endif //OPENHEXPLORE_GLOBALS_H
