//
// Created by Smaug on 2020-05-01.
//

#ifndef OPENHEXPLORE_KEYS_H
#define OPENHEXPLORE_KEYS_H

LRESULT keycodeHandler(UINT msg, WPARAM wparam, LPARAM lparam);
int processKey();
bool trackKey(int keyCode, char bit);
void initVoiceRNG();
void sub_415D30();

#endif //OPENHEXPLORE_KEYS_H
