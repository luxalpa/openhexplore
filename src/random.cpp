//
// Created by Smaug on 2020-05-20.
//

#include <cstdlib>
#include "random.h"
#include "globals.h"

// TODO: Find out what this is for
// @ 40C810
void createRandArray() {
    for (int i = 0; i < 0x100; i++) {
        randArray[i] = rand();
    }
}