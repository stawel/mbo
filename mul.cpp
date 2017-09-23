#define MAX 128

#define BASE 40
#define DIGITS 5         //4
#define LEN 26           //32
#define LL unsigned long long

LL A[3 * LEN], B[3 * LEN], V[3 * LEN], MAX_NUM = 102400000ull;

void read(LL *v, char *str) {
    LL m = 1;
    for (int i = 0; i < MAX; i++) {
        v[i / DIGITS] += str[MAX - 1 - i] * m;
        m *= BASE;
        if (m >= MAX_NUM) m = 1;
    }
}

void write(char *str, LL *v) {
    LL x = 0;
    for (int i = 0; i < 2 * MAX; i++) {
        if (i % DIGITS == 0) x += v[i / DIGITS];
        str[2 * MAX - 1 - i] = x % BASE;
        x /= BASE;
    }
}

void mul(char *v, char *a, char *b) {
    for (int i = 0; i < 2 * LEN; i++) B[i] = A[i] = V[i] = 0;

    read(A, a);
    read(B, b);  //0.7s

    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++)
            V[i + j] += A[i] * B[j];  //0.6s

    write(v, V); //0.8s
}



// or...
//...
/*for(int i=0;i<2*LEN;i++) {
 V[i+1]+=V[i]/MAX_NUM;
 V[i]%=MAX_NUM;
 }*/
//...
void write2(char *str, LL *v) {
    for (int i = 0; i < 2 * MAX; i++) {
        str[2 * MAX - 1 - i] = v[i / DIGITS] % BASE;
        v[i / DIGITS] /= BASE;
    }
}

//--------------BENCHMARK-------------
#include "benchmark/benchmark.h"
//#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#define CHECK(x)

#define ASSERT(x) if(!(x)) std::cerr << "ASSERT " << __PRETTY_FUNCTION__ << " line:" << __LINE__ << " assert: "<< #x << std::endl, std::abort();

using namespace std;

char in[MAX][MAX];
char out[MAX * 2];

/*
 #define BASE 10
 #define DIGITS 1
 #define MAX 10
 #define MAX_NUM  10ULL //BASE**DIGITS
 #define LEN 10
 */
/*

 def f(v, base = 40):
 n = 0
 for i in v:
 n=n*base
 n=n+i
 return n

 */

void print(const char * name, char *a, int n) {
    cout << name << " = [ ";
    for (int i = 0; i < n; i++)
        cout << int(a[i]) << " ,";
    cout << "]\n";
}

static void BM_mul(benchmark::State& state) {
    state.KeepRunning();
    state.PauseTiming();
    MAX_NUM = 1;
    for (int i = 0; i < DIGITS; i++)
        MAX_NUM *= BASE;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            in[i][j] = rand() % BASE;

    int a = 0, b = 0;
    state.ResumeTiming();
    while (state.KeepRunning()) {
        int n = state.range(0);
        for (int i = 0; i < n; i++) {
            mul(out, in[a], in[b]);
            CHECK(
                    print("a", in[a],MAX);
                    print("b", in[b],MAX);
                    print("v", out,2*MAX);
                    cout << "----\n";
            )
            a += 13, b += 11;
            a %= MAX, b %= MAX;
        }
    }
}

static void CustomArguments(benchmark::internal::Benchmark* b) {
    auto v1 = { 1000, 10000, 100000, 1000000 };

    for (auto x : v1)
        b->Args( { x });
}

#define BM(x) BENCHMARK(x)->Apply(CustomArguments)

//#define BM(x) BENCHMARK(x)->RangeMultiplier(8)->Ranges({{1<<16, 1<<24},{1<<16, 1<<24} })

BM(BM_mul);

BENCHMARK_MAIN();
