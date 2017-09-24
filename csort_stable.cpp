
#define MAX 100000

int count[MAX];

template<int mask, int shift>
void csort_(int *from, int *to, int size) {
    for (int i = 0; i < size; i++)
        count[(from[i] >> shift) & mask]++;

    for (int i = 1; i <= mask; i++)
        count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--)
        to[--count[(from[i] >> shift) & mask]] = from[i];
    for (int i = 0; i <= mask; i++)
        count[i] = 0;
}

void csort_stable4(int *from, int *to, int size) {
    csort_<255, 0>(from, to, size);
    csort_<255, 8>(to, from, size);
    csort_<255, 16>(from, to, size);
    csort_<255, 24>(to, from, size);
}
void csort_stable3(int *from, int *to, int size) {
    csort_<2047, 0>(from, to, size);
    csort_<2047, 11>(to, from, size);
    csort_<2047, 22>(from, to, size);
}
void csort_stable2(int *from, int *to, int size) {
    csort_<65535, 0>(from, to, size);
    csort_<65535, 16>(to, from, size);
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


static void BM_csort_stable4(benchmark::State& state) {
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
        csort_stable4(v.data(), r.data(), v.size());
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(v.begin(),v.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}

static void BM_csort_stable2(benchmark::State& state) {
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
        csort_stable2(v.data(), r.data(), v.size());
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(v.begin(),v.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}

static void BM_csort_stable3(benchmark::State& state) {
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
        csort_stable3(v.data(), r.data(),v.size());
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

static void BM_sort(benchmark::State& state) {
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
        std::sort(v.begin(), v.end());
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(v.begin(),v.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}



#define BM(x) BENCHMARK(x)->Ranges({{8, 1<<27}})

BM(BM_csort_stable4);
BM(BM_csort_stable3);
BM(BM_csort_stable2);
BM(BM_qsort);
BM(BM_sort);



BENCHMARK_MAIN();
