//
// Created by Smaug on 2020-04-02.
//

#include "registry.h"

namespace Registry {
    // @ 405BF0
    HKEY createKey(
            bool onlyForCurrentUser,
            LPCSTR companyName,
            LPCSTR programName,
            LPCSTR mainKey,
            LPCSTR optSubKey
    ) {
        char regPath[256];

        if (!companyName || !*companyName)
            return 0;
        if (!programName || !*programName)
            return 0;
        if (!mainKey || !*mainKey)
            return 0;
        lstrcpyA(regPath, "SOFTWARE");
        lstrcatA(regPath, companyName);
        lstrcatA(regPath, "\\");
        lstrcatA(regPath, programName);
        lstrcatA(regPath, "\\");
        lstrcatA(regPath, mainKey);
        if (optSubKey && *optSubKey) {
            lstrcatA(regPath, "\\");
            lstrcatA(regPath, optSubKey);
        }

        DWORD dwDisposition;
        HKEY phkResult;
        if (onlyForCurrentUser)
            RegCreateKeyExA(HKEY_CURRENT_USER, regPath, 0, 0, 0, KEY_ALL_ACCESS, 0, &phkResult, &dwDisposition);
        else
            RegCreateKeyExA(HKEY_LOCAL_MACHINE, regPath, 0, 0, 0, KEY_ALL_ACCESS, 0, &phkResult, &dwDisposition);
        return phkResult;
    }

    // @ 405D40
    bool setStringValue(HKEY hKey, LPCSTR lpValueName, LPCSTR lpString) {
        return RegSetValueExA(
                hKey,
                lpValueName,
                0,
                REG_SZ,
                (const BYTE *) lpString,
                lstrlenA(lpString)
        ) == ERROR_SUCCESS;
    }

    // @ 405D70
    bool setDWordValue(HKEY hKey, LPCSTR lpValueName, int value) {
        return RegSetValueExA(hKey, lpValueName, 0, REG_DWORD, (const BYTE *) &value, 4u) == ERROR_SUCCESS;
    }

    // @ 405DA0
    bool closeKey(HKEY hKey) {
        return RegCloseKey(hKey) == ERROR_SUCCESS;
    }
}
