//
// Created by Smaug on 2020-04-03.
//

#ifndef OPENHEXPLORE_RUN_H
#define OPENHEXPLORE_RUN_H

enum class PlayVideoMode {
    LevelVideo = 0,
    GameIntro = 1,
};

void playVideo(PlayVideoMode mode, int episode, int level);
signed int sub_426590();

#endif //OPENHEXPLORE_RUN_H
