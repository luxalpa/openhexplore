//
// Created by Smaug on 2020-07-09.
//

#include "todo.h"
#include "../globals.h"
#include <math.h>
#include "../filedb.h"

// @ 415D80
void sub_415D80() {
    sub_42B820(397425);
}

// @ 42B820
void sub_42B820(int a1) {
    dword_4E6198 = a1;
}

// @ 4089E0
void initAnimatedObjects() {
    const int numEntries = 8;
    const int entrySize = 10000;

    char *tempMemory1 = (char *) allocFile(0x10000, 0x8001);
    char *tempMemory2 = (char *) allocFile(0x4000, 0x8001); // list of booleans, 128 * 128
    char *tempMemory3 = (char *) allocFile(2500, 0x8001); // 50 * 50, which is also the model x * z size

    memset(unk_577BC0, 0x7Fu, numEntries * entrySize);

    int *v33 = &dword_577B40;

    for (int i = 0; i < numEntries; i++) {
        memset(tempMemory2, 0, 0x4000u);

        double v0 = ((double) i * M_PI) / 16.0;

        double v1 = cos(v0);
        double v2 = sin(v0);

        int v27 = (__int64) (65536.0 * v1);
        __int64 v3 = (__int64) (65536.0 * v2);

        int v31 = v3;
        int v35 = -v3;

        double v4 = (double) (((unsigned char) i - 8) & 0x1F) * (M_PI / 16.0);
        int v23 = (signed __int64) (((cos(v4) - v1) * 64.0 + 64.0) * 65536.0);

        __int64 v6 = (signed __int64) (((sin(v4) - v2) * 64.0 + 64.0) * 65536.0);

        char *v7 = tempMemory1;
        char *v8 = tempMemory2;

        for (int j = 0; j < 128; j++) {
            int v25 = v23;
            int v40 = v6;
            v6 = v31 + v6;
            v23 += v27;

            for (int k = 0; k < 128; k++) {
                int v10 = (v25 & 0x7F0000u) >> 16;
                int v11 = (v40 & 0x7F0000u) >> 16;
                if (v10 > 39 && v10 < 89 && v11 > 39 && v11 < 89) {
                    *v7 = v10 - 39;
                    v7[1] = v11 - 39;
                    v7[2] = k - 63;
                    v7[3] = j - 63;
                    *v8 = 1;
                }
                v7 += 4;
                ++v8;
                v25 += v35;
                v40 += v27;
            }
        }

        char *offset = unk_577BC0 + entrySize * i;

        char *v13 = tempMemory1;
        char *v32 = tempMemory2;

        memset(tempMemory3, 0, 2500);

        int v26 = 0;
        int v30 = 0;
        int v24 = 0;
        int v28 = 0;

        for (int j = 0; j < 128; j++) {
            for (int k = 0; k < 128; k++) {
                if (*v32 != 0) {
                    int v15 = (unsigned __int8) *v13 + 50 * (unsigned __int8) v13[1];
                    char v16 = tempMemory3[v15];
                    if (v16) {
                        if (v16 == 1) {
                            int v19 = (int) &offset[4 * v15];
                            int v20 = v13[2];
                            int v18 = v13[3];
                            *(unsigned char *) (v19 + 2) = v20;
                            *(unsigned char *) (v19 + 3) = v18;
                            tempMemory3[v15] = 2;
                            if (v28 > v20)
                                v28 = v20;
                            if (v24 < v20)
                                v24 = v20;
                            if (v30 > v18)
                                v30 = v18;
                            if (v26 < v18) {
                                v26 = v18;
                            }
                        }
                    } else {
                        int v17 = v13[2];
                        int v18 = v13[3];
                        offset[4 * v15] = v17;
                        offset[4 * v15 + 1] = v18;
                        tempMemory3[v15] = 1;
                        if (v28 > v17)
                            v28 = v17;
                        if (v24 < v17)
                            v24 = v17;
                        if (v30 > v18)
                            v30 = v18;
                        if (v26 < v18) {
                            v26 = v18;
                        }
                    }
                }

                v13 += 4;
                ++v32;
            }
        }

        v33 += 4;
        *(v33 - 4) = v28;
        *(v33 - 3) = v30;
        *(v33 - 2) = v24;
        *(v33 - 1) = v26;
    }
    deallocFile(tempMemory3);
    deallocFile(tempMemory1);
    deallocFile(tempMemory2);
}

// @ 409050
void sub_409050() {
    int v0 = 0;

    int v2 = 0;
    for (_DWORD &v1 : unk_5772A0) {
        int v4 = rand() % 10 + v2 - 5;
        int v5 = v4;

        if (v4 < 0)
            v5 = -v4;
        if (v5 <= 1) {
            v2 = v4;
            v1 = v4 << 10;
        }

        int v6 = rand() % 10 + v0 - 5;
        int v7 = v6;

        if (v6 < 0)
            v7 = -v6;
        if (v7 <= 1) {
            v0 = v6;
            v1 += 2 * v6;
        }
    }

    for(int i = 0; i < 700; i++) {
        UnkRandStruct &v8 = unk_575CC0[i];

        int v10 = rand();
        v8.field0 = (((v10 >> 31) ^ abs((_WORD) v10) & 0x1FF) - (v10 >> 31)) << 10;
        v8.field0 += 2 * (rand() % -512);
        int v11 = rand();
        __int64 v13 = v11;
        v8.field1 = (unsigned __int64) (v13 % 99) + 2;
    }
}