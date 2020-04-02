//
// Created by Smaug on 2020-04-02.
//

#include "ddraw.h"
#include "globals.h"

/*
int sub_405E20(HINSTANCE hInstance, int nCmdShow) {
    int v2; // ST1C_4
    int v3; // eax
    int result; // eax
    int v5; // [esp+2Ch] [ebp-D8h]
    int v6; // [esp+30h] [ebp-D4h]
    int v7; // [esp+34h] [ebp-D0h]
    int v8; // [esp+38h] [ebp-CCh]
    int v9; // [esp+94h] [ebp-70h]
    int v10; // [esp+98h] [ebp-6Ch]
    int v11; // [esp+9Ch] [ebp-68h]
    int v12; // [esp+100h] [ebp-4h]

    gWndClass.style = 3;
    gWndClass.lpfnWndProc = sub_4060B0;
    gWndClass.cbClsExtra = 0;
    gWndClass.cbWndExtra = 0;
    gWndClass.hInstance = hInstance;
    gWndClass.hIcon = LoadIconA(hInstance, (LPCSTR)0x7F00);
    gWndClass.hCursor = LoadCursorA(nullptr, (LPCSTR)0x7F00);
    gWndClass.lpszMenuName = WindowName;
    gWndClass.lpszClassName = WindowName;
    gWndClass.hbrBackground = nullptr;
    RegisterClassA(&WndClass);
    v2 = GetSystemMetrics(1);
    v3 = GetSystemMetrics(0);
    hWnd = CreateWindowExA(8u, WindowName, WindowName, 0x80000000, 0, 0, v3, v2, 0, 0, hInstance, 0);
    if ( !hWnd )
        return 0;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    if ( DirectDrawCreate(0, &lpDD, 0) )
        goto LABEL_18;
    if ( lpDD->lpVtbl->SetCooperativeLevel(lpDD, hWnd, 17) )
        goto LABEL_18;
    if ( lpDD->lpVtbl->SetDisplayMode(lpDD, 640, 480, 8) )
        goto LABEL_18;
    v10 = 108;
    v11 = 1;
    v12 = 512;
    if ( lpDD->lpVtbl->CreateSurface(lpDD, (LPDDSURFACEDESC)&v10, (LPDIRECTDRAWSURFACE *)&dword_44E0F8, 0)
         || (v6 = 7,
             v5 = 108,
             v8 = 640,
             v7 = 480,
             v9 = 2112,
            lpDD->lpVtbl->CreateSurface(lpDD, (LPDDSURFACEDESC)&v5, (LPDIRECTDRAWSURFACE *)&dword_44E0FC, 0)) )
    {
        LABEL_18:
        sub_405DC0();
        DestroyWindow(hWnd);
        result = 0;
    }
    else if ( lpDD->lpVtbl->CreateClipper(lpDD, 0, (LPDIRECTDRAWCLIPPER *)&dword_5734F0, 0) )
    {
        sub_405DC0();
        DestroyWindow(hWnd);
        result = 0;
    }
    else if ( (*(int (__stdcall **)(int, _DWORD, HWND))(*(_DWORD *)dword_5734F0 + 32))(dword_5734F0, 0, hWnd) )
    {
        sub_405DC0();
        DestroyWindow(hWnd);
        result = 0;
    }
    else if ( (*(int (__stdcall **)(int, int))(*(_DWORD *)dword_44E0F8 + 112))(dword_44E0F8, dword_5734F0) )
    {
        sub_405DC0();
        DestroyWindow(hWnd);
        result = 0;
    }
    else
    {
        result = 1;
    }
    return result;
}
*/