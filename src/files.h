//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_FILES_H
#define OPENHEXPLORE_FILES_H

namespace Files {
    enum class OpenMode {
        ReadOnly = 1,
        WriteOnly = 2,
        Append = 3,
        Truncate = 4,
    };

    int open(LPCSTR lpText, OpenMode mode);

    int getSize(int fd);

    bool close(int fd);

    bool exists(const char *fileName);

    bool read(int fd, void *buffer, unsigned int len);
}

#endif //OPENHEXPLORE_FILES_H
