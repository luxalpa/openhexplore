//
// Created by Smaug on 2020-04-02.
//

#include <cstdio>
#include "init.h"
#include "globals.h"
#include <windows.h>
#include "game/meta.h"
#include "filedb.h"
#include "global_fns.h"

// @ 406760
void resetEpisode() {
    gGame.episode = -1;
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
        gGame.episode = episode;
        gGame.level = level;
        gGame.field_8 = 0;
    }
    return 1;
}

