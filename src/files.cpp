//
// Created by Smaug on 2020-04-02.
//

#include <sys/stat.h>
#include <fcntl.h>
#include "global_fns.h"
#include "globals.h"
#include "filedb.h"
#include <windows.h>
#include <cstdio>
#include <io.h>
#include "files.h"
#include "game_window.h"

namespace Files {

    // @ 406E40
    int open(LPCSTR lpText, OpenMode mode) {
        if (mode == OpenMode::ReadOnly) {
            int fd = _open(lpText, _O_BINARY);
            if (fd == -1)
                exitWithFileError(5, lpText);
            return fd;
        }
        if (mode == OpenMode::WriteOnly || mode == OpenMode::Append) {
            int openFlags;
            if (mode == OpenMode::WriteOnly) {
                openFlags = _O_BINARY | _O_WRONLY;
            } else {
                openFlags = _O_BINARY | _O_APPEND | _O_RDWR;
            }

            int fd = _open(lpText, openFlags);
            if (fd == -1) {
                fd = _open(lpText, _O_BINARY | _O_CREAT, _S_IREAD | _S_IWRITE);
                if (fd == -1)
                    exitWithFileError(1, lpText);
                _close(fd);
                fd = _open(lpText, openFlags);
                if (fd == -1)
                    exitWithFileError(3, lpText);
            }
            return fd;
        }
        if (mode == OpenMode::Truncate) {
            int fd = _open(lpText, _O_BINARY | _O_TRUNC | _O_CREAT | _O_WRONLY, _S_IREAD | _S_IWRITE);
            if (fd == -1)
                exitWithFileError(1, lpText);
            _close(fd);
            fd = _open(lpText, _O_BINARY | _O_RDWR);
            if (fd == -1)
                exitWithFileError(3, lpText);
            return fd;
        }

        return 0;
    }

    // @ 406F60
    int getSize(int fd) {
        int len = _filelength(fd);
        if (len == -1)
            return 0;
        return len;
    }

    // @ 406FC0
    bool read(int fd, void *buffer, unsigned int len) {
        if (_read(fd, buffer, len) == -1)
            exitWithFileError(4, "---");
        return true;
    }

    // @ 407000
    bool close(int fd) {
        return _close(fd);
    }

    // @ 407020
    bool exists(char *fileName) {
        int fh = _open(fileName, _O_BINARY);
        if (fh == -1)
            return false;
        _close(fh);
        return true;
    }
}

