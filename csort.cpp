
#define MAX 1000000


static int count[MAX];

void csort(int *from, int *to, int size, int maks) 
{
    for(int i=0;i<size;i++)
        count[from[i]]++;

    for(int j=0, i=0;i<=maks;i++)
        while(count[i]) count[i]--, to[j++]=i;
}


//--------------BENCHMARK-------------

#include "benchmark/benchmark.h"
#include <cassert>
#include <algorithm>
#include <iostream>

#define CHECK(x) x

static void BM_csort(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto n = state.range(0);
        auto mask = state.range(1);
        std::vector<int> v(n), r(n);
        for(auto &x:v) x = rand()&mask;
        CHECK(
            auto v2 = v;
            std::sort(v2.begin(), v2.end());
        )
        state.ResumeTiming();
        csort(v.data(), r.data(), v.size(), mask);
        CHECK(
            state.PauseTiming();
            assert(std::equal(r.begin(),r.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}


static void BM_qsort(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto n = state.range(0);
        auto mask = state.range(1);
        std::vector<int> v(n), r(n);
        for(auto &x:v) x = rand()&mask;
        CHECK(
            auto v2 = v;
            std::sort(v2.begin(), v2.end());
        )
        state.ResumeTiming();
        std::sort(v.begin(), v.end());
        CHECK(
            state.PauseTiming();
            assert(std::equal(v.begin(),v.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}


int size = (1<<10)*10;

#define BM(x) BENCHMARK(x)->Args({size, 7}) \
    ->Args({size, 63}) \
    ->Args({size, 127})        \
    ->Args({size, 255})        \
    ->Args({size, 511})        \
    ->Args({size, 1023})       \
    ->Args({size, 2047})       \
    ->Args({size, 4095})       \
    ->Args({size, 8191})       \
    ->Args({size, 16383})      \
    ->Args({size, 32767})       \
    ->Args({size, 65535})       \
    ->Args({size, 131071});

BM(BM_csort);
BM(BM_qsort);
/*
BENCHMARK(BM_qsort)->Args({1<<10, 7})
    ->Args({1<<10, 63})
    ->Args({1<<10, 511});
*/
// Define another benchmark


BENCHMARK_MAIN();