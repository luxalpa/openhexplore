//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_INIT_H
#define OPENHEXPLORE_INIT_H

void resetEpisode();
int parseCmdLine(char *pLine, int (*parseArg)(char *));
int parseCmdLineArg(char *a1);

#endif //OPENHEXPLORE_INIT_H
