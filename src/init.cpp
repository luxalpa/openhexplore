//
// Created by Smaug on 2020-04-02.
//

#include "init.h"
#include "globals.h"
#include "interop/memory.h"

// @4156E0
int sub_4156E0(int a1) {
    void *v2; // eax

    if ( dword_44CDAC )
        return 0;
    dword_44CDAC = hexp_malloc(24000u);
    if ( !dword_44CDAC )
        return 0;
    memset(dword_44CDAC, 0, 24000u);
    dword_44CDB0 = a1;
    dword_44CDB4 = 0;
    dword_44CDB8 = 0;
    dword_44CDC0 = 0;
    dword_44CDC4 = 0;
    dword_44CDBC = 0;
    dword_44CDC8 = 0;
    return 1;
}