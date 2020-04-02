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
}

#endif //OPENHEXPLORE_REGISTRY_H
