//
// Created by Smaug on 2020-04-02.
//

#ifndef OPENHEXPLORE_TEXTDB_H
#define OPENHEXPLORE_TEXTDB_H

struct struc_2 {
    char *field_0;
    int field_4;
    int field_8;
};

struct FileEntryStruct {
    char *pData;
    int size;
    short flags;
    short isInUse;
};

bool convertToGamePath(char *relPath);
void initTextDB();
void sub_416000(LPCSTR lpText, char **a2, int a3);

#endif //OPENHEXPLORE_TEXTDB_H
