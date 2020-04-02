#include "main.h"
#include "interop/interop.hpp"
#include "globals.h"
#include "init.h"

//auto sub_4156E0 = (void (*const)(int)) 0x4156E0;
auto sub_406760 = (void (*const)()) 0x406760;
auto sub_413940 = (void (*const)(LPSTR cmdLine, int (*a2)(char *))) 0x413940;
auto sub_406770 = (int (*const)(char *a1)) 0x406770;
auto sub_405E20 = (int (*const)(HINSTANCE hInstance, int nCmdShow)) 0x405E20;
auto sub_416EE0 = (BOOL (*const)(int *a1)) 0x416EE0;
auto sub_426590 = (signed int (*const)()) 0x426590;

void DebugInfo() {
    MessageBoxA(nullptr, "Found!", "", MB_OK);
}

extern "C" __declspec(dllexport)
int __stdcall StartHexplore(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    tagMSG Msg{};

    gHInstance = hInstance;
    gHMutex = CreateMutexA(nullptr, 0, "Hexplore95");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return -1;
    }

    sub_4156E0(0x2000000);
    sub_406760();
    sub_413940(lpCmdLine, sub_406770);

    if (!sub_405E20(hInstance, nShowCmd))
        return 0;
    sub_416EE0(&gCmdEpisode);
    while (true) {
        while (!PeekMessageA(&Msg, nullptr, 0, 0, 0)) {
            if (dword_5730DC | 1) {
                if (!sub_426590()) {
                    SendMessageA(gHWnd, WM_DESTROY, 0, 0);
                }
            } else {
                WaitMessage();
            }
        }
        if (!GetMessageA(&Msg, 0, 0, 0))
            break;
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    return Msg.wParam;
}
