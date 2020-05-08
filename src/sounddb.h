//
// Created by Smaug on 2020-05-01.
//

#ifndef OPENHEXPLORE_SOUNDDB_H
#define OPENHEXPLORE_SOUNDDB_H

void loadSoundbankHeaders();

int loadSysSmpBin();
int loadMusicSmpBin();
int sub_40A650(int sndBank, int snd);

#endif //OPENHEXPLORE_SOUNDDB_H
