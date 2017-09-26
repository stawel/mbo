#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

#define LEN 100
#define TESTS 20000

char SRC[TESTS][LEN];
char dummy1[100];
char QRC[TESTS][LEN][LEN];
char dummy2[100];
char IMG[TESTS][LEN * 2][LEN * 2];
char dummy3[100];
char GRY[TESTS][LEN][LEN];
char dummy4[100];

char DST[TESTS][LEN];
char dummy5[100];

void encode(char QRC[LEN][LEN], char SRC[LEN]);
void decode(char DST[LEN], char GRY[LEN][LEN]);

#ifndef BENCH
#include <time.h>
#define B(x) clock_t B_##x;
#define BB(x) clock_t Bstart_##x = clock();
#define BE(x) B_##x+=clock() - Bstart_##x;
#define BP(x) printf( #x ": %f\n", ((double)(B_##x))/CLOCKS_PER_SEC);
#else
#define B(x)
#define BB(x)
#define BE(x)
#define BP(x)
#endif

#define D(x) x
B(a);
B(b);
B(decode);
B(encode);
B(prog);

void toGray(char GRY[LEN][LEN], char IMG[LEN * 2][LEN * 2]) {
    for (int y = 0; y < LEN; y++)
        for (int x = 0; x < LEN; x++) {
            GRY[y][x] = IMG[2 * y + 0][2 * x + 0];
            GRY[y][x] += IMG[2 * y + 1][2 * x + 0];
            GRY[y][x] += IMG[2 * y + 0][2 * x + 1];
            GRY[y][x] += IMG[2 * y + 1][2 * x + 1];
        }
}

int main() {
    BB(prog);
    srand (time(NULL));
    for (int i = 0; i < TESTS; i++) {
        for(int j = 0; j < LEN; j++) {
            SRC[i][j] = 'A'+(rand() % 26);
        }
    }

    BB(encode);
    for (int i = 0; i < TESTS; i++) {
        encode(QRC[i], SRC[i]);
    }
    BE(encode);

    BB(b);
    for (int i = 0; i < TESTS; i++) {
        for (int y = 0; y < LEN * 2; y++)
            for (int x = 0; x < LEN * 2; x++)
                IMG[i][y][x] = rand() % 2;

        int posX = rand() % (LEN + 1);
        int posY = rand() % (LEN + 1);
        for (int y = 0; y < LEN; y++)
            for (int x = 0; x < LEN; x++)
                IMG[i][y + posY][x + posX] = QRC[i][y][x] ? 1 : 0;

        for (int j = 0; j < 13000; j++) {
            IMG[i][rand() % (LEN * 2)][rand() % (LEN * 2)] = 1;
        }

        toGray(GRY[i], IMG[i]);
    }
    BE(b);

    BB(decode);
    for (int i = 0; i < TESTS; i++) {
        decode(DST[i], GRY[i]);
    }
    BE(decode);

    int FAIL = 0;

    for (int i = 0; i < TESTS; i++) {
        bool f = memcmp(DST[i], SRC[i], LEN) != 0;
        D(
            if (f) {
                printf("%.100s != \n%.100s %d\n", DST[i], SRC[i], i);
                for (int j = 0; j < LEN; j++) {
                    printf("%d", DST[i][j] != SRC[i][j] ? 1 : 0);
                }
                printf("\n\n");
            }
        )
        FAIL += f ? 1 : 0;
    }
    cout << "FAIL:" << FAIL << " out of " << TESTS << "\n";
    BE(prog);
    BP(prog);
    BP(a);
    BP(b);
    BP(decode);
    BP(encode);
}

//  encode/decode code

#define STR1 "PAWI"
#define STR2 "WUPE"
#define STR1_hex (toB('P', 0)|toB('A', 5)|toB('W', 10)| toB('I', 15))
#define STR2_hex (toB('W', 0)|toB('U', 5)|toB('P', 10)| toB('E', 15))
#define STR_hex(d,i) (toB(d[i], 0)|toB(d[i+1], 5)|toB(d[i+2], 10)| toB(d[i+3], 15))

#define MASK ((1<<20)-1)
#define LL unsigned long long

LL toB(char c, int s) {
    char v = (c)-'A'+3;
    if(v==4) v = 29;
    if(v==8) v = 30;
    if(v==16) v = 31;
    return (((LL)(v))<<s);
}

char fromB(LL b) {
    char v = (b)&31;
    if(v==31) v = 16;
    if(v==30) v = 8;
    if(v==29) v = 4;
    return v+'A'-3;
}


void saveLL(char QRC[LEN][LEN], int &y, LL c) {
    for (int y_last = y + 3; y < y_last; y++)
        for (int x = 0; x < 5 * 20; x++)
            QRC[y][x] = (c >> (x / 5)) & 1;
}

void encode(char QRC[LEN][LEN], char SRC[LEN]) {
    char d[LEN + 8] = STR1 STR2;
    memcpy(d + 8, SRC, LEN);
    for (int y = 0, i = 0; i < LEN + 8; i += 4)
        saveLL(QRC, y, STR_hex(d, i));
}

//decode

void dToChar(LL d, char *c) {
    for (int i = 0; i < 4; i++) {
        c[i] = fromB(d);
        d >>= 5;
    }
}

LL decodeLine(char GRY[LEN][LEN], int y, int p) {
    LL d = 0, bit = 1;
    for (int i = (p + 1) / 2, j = 0; j < 40; j++) {
        if (GRY[y][i] + GRY[y][i + 1] >= 8) d |= bit;
        bit <<= 1;
        p ^= 1;
        i += 2 + (p & 1);
    }
    return d;
}

void decode(char DST[LEN], char GRY[LEN][LEN]) {
    LL out[6][LEN];

    for (int y = 0; y < LEN; y++)
        for (int p = 0; p < 5; p++)
            out[p][y] = decodeLine(GRY, y, p);

    for (int p = 0; p < 10; p++)
        for (int x = 0; x <= 20; x++)
            for (int y = 0; y <= LEN / 2; y++)
                if ( STR1_hex == ((out[p / 2][y] >> x) & MASK)
                  && STR2_hex == ((out[p / 2][y + 1 + !(p & 1)] >> x) & MASK)) {
                    y = y + 1 + !(p & 1);
                    for (int i = 0; i < LEN; i += 4) {
                        p ^= 1;
                        y += 1 + !(p & 1);
                        dToChar(out[p / 2][y] >> x, &DST[i]);
                    }
                    return;
                }
}

/*
 * 100'000 -> 1084,5 (c-'A')
 *         -> 1071,5 (c-'A'+1)
 *         ->  910,5 (c-'A'+5)
 *         ->  849   (toB formB)
 *
 *
 */
