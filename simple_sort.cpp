

void isort(int *T, int size) {
    for (int j, x, i = 1; i < size; i++) {
        x = T[i];
        j = i - 1;
        while (j >= 0 && T[j] > x) {
            T[j + 1] = T[j];
            j--;
        }
        T[j + 1] = x;
    }
}


#define VAR(v, n) __typeof(n) v = (n)
#define SWAP(a, b) { VAR(t,a); a=b,b=t;}

void bsort(int *T, int size) {
    do {
        int i, nsize = 0;
        for (i = 1; i < size; i++)
            if (T[i - 1] > T[i]) {
                SWAP(T[i - 1], T[i]);
                nsize = i;
            }
        size = nsize;
    } while (size > 0);
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


static void BM_isort(benchmark::State& state) {
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
        isort(v.data(), v.size());
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(v.begin(),v.end(),v2.begin()));
            state.ResumeTiming();
        )
    }
}

static void BM_bsort(benchmark::State& state) {
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
        bsort(v.data(), v.size());
        CHECK(
            state.PauseTiming();
            ASSERT(std::equal(v.begin(),v.end(),v2.begin()));
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

static void CustomArguments(benchmark::internal::Benchmark* b) {
    int v[] = {1,5,10,20,50,100,150,200,300,400,500,600,700,800,900,1000};
    for(auto x:v)
      b->Args({x});
}


#define BM(x) BENCHMARK(x)->Apply(CustomArguments)

BM(BM_isort);
BM(BM_bsort);
BM(BM_qsort);
BM(BM_sort);



BENCHMARK_MAIN();
