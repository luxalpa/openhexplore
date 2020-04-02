#include "main.h"
#include "interop/interop.hpp"
#include "globals.h"
#include "init.h"
#include "global_fns.h"
#include "ddraw.h"

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

    if (!createGameWindow(hInstance, nShowCmd))
        return -2;

    initGame(&gGame);
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
