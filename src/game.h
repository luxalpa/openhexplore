//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_GAME_H
#define OPENHEXPLORE_GAME_H

struct Game {
    int episode;
    int level;
    int field_8; // map?
    char directory[0x100];
    char directory2[0x100];
    char saveDir[0x100];
};

void initGame(Game *game);

#endif //OPENHEXPLORE_GAME_H
