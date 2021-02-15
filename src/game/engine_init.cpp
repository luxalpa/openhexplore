//
// Created by Smaug on 2020-07-09.
//

#include "engine_init.h"
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
    const int entrySize = 50 * 50 * sizeof(UnkAnimStruct3);

    UnkAnimStruct2 *tempMemory1 = (UnkAnimStruct2 *) allocFile(0x10000, 0x8001);
    bool *tempMemory2 = (bool *) allocFile(128 * 128, 0x8001); // list of booleans
    char *tempMemory3 = (char *) allocFile(50 * 50, 0x8001); // 50 * 50, which is also the model x * z size

    memset(unk_577BC0, 0x7Fu, numEntries * entrySize);

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

        UnkAnimStruct2 *v7 = tempMemory1;
        bool *v8 = tempMemory2;

        for (int j = 0; j < 128; j++) {
            int v25 = v23;
            int v40 = v6;
            v6 = v31 + v6;
            v23 += v27;

            for (int k = 0; k < 128; k++) {
                int v10 = (v25 & 0x7F0000u) >> 16;
                int v11 = (v40 & 0x7F0000u) >> 16;
                if (v10 > 39 && v10 < 89 && v11 > 39 && v11 < 89) {
                    v7->x = v10 - 39;
                    v7->z = v11 - 39;
                    v7->field2 = k - 63;
                    v7->field3 = j - 63;
                    *v8 = true;
                }
                v7++;
                ++v8;
                v25 += v35;
                v40 += v27;
            }
        }

        UnkAnimStruct3 *offset = &unk_577BC0[50 * 50 * i];

        memset(tempMemory3, 0, 50 * 50);

        int v26 = 0;
        int v30 = 0;
        int v24 = 0;
        int v28 = 0;

        for (int j = 0; j < 128; j++) {
            for (int k = 0; k < 128; k++) {
                int pos = j * 128 + k;

                if (tempMemory2[pos] != 0) {
                    UnkAnimStruct2 &v13 = tempMemory1[pos];
                    int v15 = v13.x + 50 * v13.z;
                    char v16 = tempMemory3[v15];
                    if (v16) {
                        if (v16 == 1) {
                            UnkAnimStruct3 &v19 = offset[v15];
                            int v20 = v13.field2;
                            int v18 = v13.field3;
                            v19.field2 = v20;
                            v19.field3 = v18;
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
                        int v17 = v13.field2;
                        int v18 = v13.field3;
                        offset[v15].field0 = v17;
                        offset[v15].field1 = v18;
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
            }
        }

        dword_577B40[i] = {
                .field0 = v28,
                .field1 = v30,
                .field2 = v24,
                .field3 = v26,
        };
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

    for (UnkRandStruct &v8 : stru_575CC0) {
        int v10 = rand();
        v8.field0 = (((v10 >> 31) ^ abs((_WORD) v10) & 0x1FF) - (v10 >> 31)) << 10;
        v8.field0 += 2 * (rand() % -512);
        int v11 = rand();
        __int64 v13 = v11;
        v8.field1 = (unsigned __int64) (v13 % 99) + 2;
    }
}