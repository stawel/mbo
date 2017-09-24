
#define MAX 20000000

int count[MAX];

void csort(int *from, int *to, int size, int maks) {
    for (int i = 0; i < size; i++)
        count[from[i]]++;

    for (int j = 0, i = 0; i <= maks; i++)
        while (count[i]) count[i]--, to[j++] = i;
}

//counting sort stable

void csort_stable(int *from, int *to, int size, int maks) {
    for (int i = 0; i < size; i++)
        count[from[i]]++;

    for (int i = 1; i <= maks; i++)
        count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--)
        to[--count[from[i]]] = from[i];
    for (int i = 0; i <= maks; i++)
        count[i] = 0;
}


//--------------BENCHMARK-------------

#include "benchmark/benchmark.h"
//#include <cassert>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <cstdlib>

#define CHECK(x) x

#define ASSERT(x) if(!(x)) std::cerr << "ASSERT " << __PRETTY_FUNCTION__ << " line:" << __LINE__ << " assert: "<< #x << std::endl, std::abort();

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
            ASSERT(std::equal(r.begin(),r.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}

static void BM_csort_stable(benchmark::State& state) {
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
        csort_stable(v.data(), r.data(), v.size(), mask);
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(r.begin(),r.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}


static void BM_qsort(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto n = state.range(0);
        std::vector<int> v(n), r(n);
        for(auto &x:v) x = rand();
        CHECK(
            auto v2 = v;
            std::sort(v2.begin(), v2.end());
        )
        state.ResumeTiming();
        std::qsort(v.data(), v.size(), sizeof(int), [](const void* a, const void* b)
        {
            int arg1 = *static_cast<const int*>(a);
            int arg2 = *static_cast<const int*>(b);
        //  return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
            return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
        });
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(v.begin(),v.end(),v2.begin()));
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
    ->Args({size, 131071})      \
    ->Args({131071, 131071})    \
    ->Args({1048575, 1048575});

BM(BM_csort);
BM(BM_csort_stable);
BM(BM_qsort);
/*
BENCHMARK(BM_qsort)->Args({1<<10, 7})
    ->Args({1<<10, 63})
    ->Args({1<<10, 511});
*/
// Define another benchmark


BENCHMARK_MAIN();
