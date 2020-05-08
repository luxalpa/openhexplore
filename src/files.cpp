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
            int fd = hexp_open(lpText, _O_BINARY);
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

            int fd = hexp_open(lpText, openFlags);
            if (fd == -1) {
                fd = hexp_open(lpText, _O_BINARY | _O_CREAT, _S_IREAD | _S_IWRITE);
                if (fd == -1)
                    exitWithFileError(1, lpText);
                hexp_close(fd);
                fd = hexp_open(lpText, openFlags);
                if (fd == -1)
                    exitWithFileError(3, lpText);
            }
            return fd;
        }
        if (mode == OpenMode::Truncate) {
            int fd = hexp_open(lpText, _O_BINARY | _O_TRUNC | _O_CREAT | _O_WRONLY, _S_IREAD | _S_IWRITE);
            if (fd == -1)
                exitWithFileError(1, lpText);
            hexp_close(fd);
            fd = hexp_open(lpText, _O_BINARY | _O_RDWR);
            if (fd == -1)
                exitWithFileError(3, lpText);
            return fd;
        }

        return 0;
    }

    // @ 406F60
    int getSize(int fd) {
        int len = hexp_filelength(fd);
        if (len == -1)
            return 0;
        return len;
    }

    // @ 406FC0
    bool read(int fd, void *buffer, unsigned int len) {
        if (hexp_read(fd, buffer, len) == -1)
            exitWithFileError(4, "---");
        return true;
    }

    // @ 407000
    bool close(int fd) {
        return hexp_close(fd);
    }

    // @ 407020
    bool exists(const char *fileName) {
        int fh = hexp_open(fileName, _O_BINARY);
        if (fh == -1)
            return false;
        hexp_close(fh);
        return true;
    }

    // @ 4070D0
    int seek(int fd, int offset, int origin) {
        return hexp_lseek(fd, offset, origin);
    }

    // returns a pointer to the file data and sets pSize to the size of the data
    // @ 4070F0
    void *getContents(const char *filename, unsigned int *pSize, int flags) {
        int fd = Files::open(filename, OpenMode::ReadOnly);

        int size = Files::getSize(fd);
        void *data = allocFile(size, flags);

        Files::read(fd, data, size);
        Files::close(fd);

        *pSize = size;
        return data;
    }
}

