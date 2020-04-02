//
// Created by Smaug on 2020-04-02.
//

#include <cstdio>
#include <windows.h>
#include "textdb.h"
#include "globals.h"
#include "global_fns.h"

// @ 411F80
void initTextDB() {
    struc_2 a3;
    char filepath[0x100];

    sprintf(filepath, "%s\\%s%s", "COMMON", gLangPrefix, "txt.st1");
    sub_417090(filepath);
    sub_416000(filepath, &gTextDBData, true);
    sub_4160A0(gTextDBData, 100u, &a3);
    strcpy(gText_Strength, a3.field_0);
    sub_4160A0(gTextDBData, 101u, &a3);
    strcpy(gText_Mechanism, a3.field_0);
    sub_4160A0(gTextDBData, 102u, &a3);
    strcpy(gText_Incantation, a3.field_0);
    sub_4160A0(gTextDBData, 103u, &a3);
    strcpy(gText_Agility, a3.field_0);
    sub_4160A0(gTextDBData, 104u, &a3);
    strcpy(gText_ToNextLevel, a3.field_0);
    MessageBoxA(gHWnd, gText_Incantation, "", MB_OK);
}
