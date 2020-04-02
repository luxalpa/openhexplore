//
// Created by Smaug on 2020-04-02.
//

#include <cstdio>
#include "init.h"
#include "globals.h"
#include "interop/memory.h"

// @ 4156E0
int sub_4156E0(int a1) {
    if (dword_44CDAC)
        return 0;
    dword_44CDAC = hexp_malloc(24000u);
    if (!dword_44CDAC)
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

// @ 406760
void resetEpisode() {
    gEpisode = -1;
}

// @ 413940
int parseCmdLine(char *pLine, int (*parseArg)(char *)) {
    char currentArg[200];

    int numArgs = 0;
    while (true) {
        int curPos = 0;
        while (true) {
            char firstChar;
            bool isQuoted = false;
            while (true) {
                firstChar = *pLine;
                if (*pLine != '"')
                    break;
                ++pLine;
                isQuoted ^= true;
            }
            if ((!isQuoted && (firstChar == ' ' || firstChar == '\t')) || !firstChar)
                break;
            currentArg[curPos] = firstChar;
            pLine++;
            curPos++;
        }
        currentArg[curPos] = 0;

        if (!parseArg(currentArg))
            break;

        numArgs++;
        if (*pLine == 0)
            break;

        do {
            pLine++;
        } while (*pLine == ' ' || *pLine == '\t');
    }
    return numArgs;
}

// @ 406770
int parseCmdLineArg(char *a1) {
    int episode; // [esp+4h] [ebp-8h]
    int level; // [esp+8h] [ebp-4h]

    _strupr(a1);
    if ( *a1 == 'E' && sscanf(a1, "E%dL%d", &episode, &level) == 2 )
    {
        gEpisode = episode;
        gLevel = level;
        dword_4EB788 = 0;
    }
    return 1;
}

