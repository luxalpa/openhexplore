//
// Created by Smaug on 2020-04-02.
//

#include <Windows.h>
#include <cstdio>
#include "meta.h"
#include "../globals.h"
#include "../global_fns.h"
#include "../main.h"
#include "../textdb.h"
#include "../registry.h"

template<char c>
struct encrypt {
    enum {
        value = c ^0x55
    };
};

template<char... Chars>
struct EncryptCharsA {
    static char value[sizeof...(Chars) + 1];
};

template<char... Chars>
char EncryptCharsA<Chars...>::value[sizeof...(Chars) + 1] = {
        encrypt<Chars>::value..., 0
};

char *gExecutableName = EncryptCharsA<'H', 'E', 'X', 'P', 'L', 'O', 'R', 'E', '.', 'E', 'X', 'E'>::value;

// @ 416E30
bool setRegistryValue(
        bool onlyForCurrentUser,
        LPCSTR optSubKey,
        LPCSTR lpValueName,
        RegistryValueType valueType,
        LPCSTR lpString
) {
    bool result;

    HKEY key = Registry::createKey(onlyForCurrentUser, "Heliovisions", "Hexplore", "1.0", optSubKey);
    if (valueType == RegistryValueType::Number) {
        result = Registry::setStringValue(key, lpValueName, lpString);
    } else if (valueType == RegistryValueType::String) {
        result = Registry::setDWordValue(key, lpValueName, *(int *) lpString);
    } else {
        result = false;
    }
    Registry::closeKey(key);
    return result;
}

// @ 416EE0
void initGame(Game *game) {
    char buffer[0x100];

    GetCurrentDirectoryA(sizeof(buffer), buffer);

    // Make sure we don't have trailing slash
    if (buffer[strlen(buffer) - 1] == '\\') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    strcpy(game->directory, buffer);
    strcpy(game->directory2, game->directory);

    char txtFilePath[0x100]; // TODO: Make this +17 bigger so that everything fits without crashing
    sprintf(txtFilePath, "%s\\%s\\??%s", game->directory, "COMMON", "txt.st1");

    _WIN32_FIND_DATAA findFileData;
    HANDLE handle = FindFirstFileA(txtFilePath, &findFileData);
    if (handle != INVALID_HANDLE_VALUE) {
        gLangPrefix[0] = findFileData.cFileName[0];
        gLangPrefix[1] = findFileData.cFileName[1];
        gLangPrefix[2] = '\0';
        FindClose(handle);
    }

    initTextDB();

    for (int i = 0; i < strlen(gExecutableName); i++) {
        gExecutableName[i] ^= 0x55;
    }

//  Removed cdCheck: sub_4139C0(gExecutableName);

    game->directory2[0] = '.';
    game->directory2[1] = '\\';
    game->directory2[2] = '\0';
    sprintf(game->saveDir, "%s\\%s", game->directory, "SAVE");
    CreateDirectoryA(game->saveDir, nullptr);
    if (game->episode == -1) {
        game->episode = 0;
        game->level = 0;
        game->field_8 = 0;
    }
}
