## About

OpenHexplore is a decompilation project of the 1998 video game [Hexplore](https://en.wikipedia.org/wiki/Hexplore) with the goal to modernize and improve it.

## How it works

Decompilation itself is being done step by step using Hexrays IDA Pro and transforming / renaming the code to make it more readable as well as stripping / fixing code along the way.

The **`OpenHexplore.exe`** is a modified version of the original `Hexplore.exe` that has an import to `openhexplore.dll` injected into the IAT. It also contains an X86 jmp expression as first statement in WinMain which jumps directly to the memory address of the `StartHexplore()` function in `main.cpp` .

To jump back into the original games code, `global_fns.h` contains definitions for all currently needed original functions.

## Current State

Currently only the sequence up until (including) the loading screen has been decompiled.

## Plans for the future

- Finish the decompilation
- Port the code base to Vulkan (and make it use 3D graphics)
- Support modern resolutions as well as Window mode
- improved pathfinding
- improved controls
- Options for hotkey rebinding, language, etc
- Mod support
- Map editor
- Online multiplayer
- Bug fixes

## Notes

For running and development, [**DxWnd**](https://sourceforge.net/projects/dxwnd/) is strongly recommended