//
// Created by Smaug on 2020-04-02.
//

#include <sys/stat.h>
#include <fcntl.h>
#include "global_fns.h"
#include "globals.h"
#include "textdb.h"
#include <windows.h>
#include <cstdio>
#include <io.h>
#include "files.h"
#include "ddraw.h"

namespace Files {

    // @ 406F60
    int getSize(int fd) {
        int len = _filelength(fd);
        if (len == -1)
            return 0;
        return len;
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
        hexp_close(fh);
        return true;
    }

    // @ 406FC0
    bool read(int fd, void *buffer, unsigned int len) {
        if (_read(fd, buffer, len) == -1)
            exitWithFileError(4, "---");
        return true;
    }
}

