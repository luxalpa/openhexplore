#include "main.h"
#include "interop/interop.hpp"
#include "globals.h"
#include "init.h"

inline auto sub_405E20 = (int (*const)(HINSTANCE hInstance, int nShowCmd)) 0x405E20;
inline auto sub_416EE0 = (BOOL (*const)(int *a1)) 0x416EE0;
inline auto sub_426590 = (signed int (*const)()) 0x426590;

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

    resetEpisode();
    parseCmdLine(lpCmdLine, parseCmdLineArg);

    if (!sub_405E20(hInstance, nShowCmd))
        return 0;

    sub_416EE0(&gEpisode);
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
