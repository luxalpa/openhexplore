# About

OpenHexplore is a decompilation project of the 1998 video game [Hexplore](https://en.wikipedia.org/wiki/Hexplore) with the goal to modernize and improve it.

# How it works

Decompilation itself is being done step by step using Hexrays IDA Pro and transforming / renaming the code to make it more readable as well as stripping / fixing code along the way.

The **`OpenHexplore.exe`** is a modified version of the original `Hexplore.exe` that has an import to OpenHexplore.dll injected into the IAT. It also contains an X86 jmp expression as first statement in WinMain which jumps directly to the memory address of the `StartHexplore()` function in `main.cpp` .

To jump back into the original games code, `global_fns.h` contains definitions for all currently needed original functions.

# Current State

Currently only the sequence up until (including) the loading screen has been decompiled.

# Plans for the future

Use the information gathered to create a full 3D version of the project using Unity3D.

# Notes

For running and development, [**DxWnd**](https://sourceforge.net/projects/dxwnd/) is strongly recommended