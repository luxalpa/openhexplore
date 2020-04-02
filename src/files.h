//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_FILES_H
#define OPENHEXPLORE_FILES_H

namespace Files {
    int getSize(int fd);

    bool close(int fd);

    bool exists(char *fileName);

    bool read(int fd, void *buffer, unsigned int len);
}

#endif //OPENHEXPLORE_FILES_H
