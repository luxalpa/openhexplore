#ifndef OPENHEXPLORE_MAIN_H
#define OPENHEXPLORE_MAIN_H

#include <Windows.h>

extern "C" __declspec(dllexport)
int __stdcall StartHexplore(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void DebugInfo();

#endif //OPENHEXPLORE_MAIN_H
