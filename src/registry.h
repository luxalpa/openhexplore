//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_REGISTRY_H
#define OPENHEXPLORE_REGISTRY_H

#include <windows.h>

namespace Registry {
    HKEY createKey(
            bool onlyForCurrentUser,
            LPCSTR companyName,
            LPCSTR programName,
            LPCSTR mainKey,
            LPCSTR optSubKey
    );

    bool setStringValue(HKEY hKey, LPCSTR lpValueName, LPCSTR lpString);

    bool setDWordValue(HKEY hKey, LPCSTR lpValueName, int value);

    bool closeKey(HKEY hKey);
}

#endif //OPENHEXPLORE_REGISTRY_H
