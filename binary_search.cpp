

#define MAX 100000000

int t[MAX];


int binary_search(int b, int e, int x) {  // t - sorted, search for x in [b,e)
    while (b < e) {
        int s = (b + e) / 2; //if b+e may overflow then use b+(e-b)/2
        if (t[s] == x) return s;
        if (x < t[s])  e = s;
        else           b = s + 1;
    }
    return -1;
}


//recursive
int binary_searchR(int b, int e, int x) {  // t - sorted, search for x in [b,e)
    if (b >= e) return -1;

    int s = (b + e) / 2; //if b+e may overflow then use b+(e-b)/2
    if (t[s] == x) return s;
    if (x < t[s])  return binary_search(b,     s, x);
    else           return binary_search(s + 1, e, x);
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

/* TODO
static void BM_msort(benchmark::State& state) {
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
        t = v.data();
        merge_sort(0, v.size());
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


#define BM(x) BENCHMARK(x)->Ranges({{8, 1<<24}})

BM(BM_msort);
BM(BM_qsort);


*/
BENCHMARK_MAIN();
