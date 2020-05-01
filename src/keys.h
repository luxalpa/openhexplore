//
// Created by Smaug on 2020-05-01.
//

#ifndef OPENHEXPLORE_KEYS_H
#define OPENHEXPLORE_KEYS_H

LRESULT keycodeHandler(UINT msg, WPARAM wparam, LPARAM lparam);
int processKey();
bool trackKey(int keyCode, unsigned int bit);

#endif //OPENHEXPLORE_KEYS_H
