//
// Created by Smaug on 2020-07-09.
//

#ifndef OPENHEXPLORE_ENGINE_INIT_H
#define OPENHEXPLORE_ENGINE_INIT_H

#define _DWORD unsigned int
#define _WORD unsigned short

struct UnkRandStruct {
    unsigned int field0;
    unsigned int field1;
};

struct UnkAnimStruct {
    int field0;
    int field1;
    int field2;
    int field3;
};

struct UnkAnimStruct2 {
    unsigned char x;
    unsigned char z;
    char field2;
    char field3;
};

struct UnkAnimStruct3 {
    unsigned char field0;
    unsigned char field1;
    unsigned char field2;
    unsigned char field3;
};

void sub_415D80();
void sub_42B820(int a1);
void initAnimatedObjects();
void sub_409050();

#endif //OPENHEXPLORE_ENGINE_INIT_H
