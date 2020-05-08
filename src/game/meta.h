//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_META_H
#define OPENHEXPLORE_META_H

#include <windows.h>

struct Game {
    int episode;
    int level;
    int field_8; // map?
    char directory[0x100];
    char directory2[0x100];
    char saveDir[0x100];
};

enum class RegistryValueType {
    String = 1,
    Number = 2,
};

bool setRegistryValue(
        bool onlyForCurrentUser,
        LPCSTR optSubKey,
        LPCSTR lpValueName,
        RegistryValueType valueType,
        LPCSTR lpString
);

void initGame(Game *game);
bool convertToGamePath(char *relPath);

#endif //OPENHEXPLORE_META_H
