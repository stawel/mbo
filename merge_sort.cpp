

#define MAX 100000000

int t2[MAX];
int *t; //should be t[MAX]

void merge_sort(int b,int e){
    if (b+1 >= e) return;
    
    int s = (b+e)/2;
    merge_sort(b,s);
    merge_sort(s,e);
    
    int i1 = b, i2 = s;
    for(int p = b; p < e; p++){
        if (i2 == e || i1 < s && t[i1] <= t[i2]){
            t2[p] = t[i1++];
        } else {
            t2[p] = t[i2++];
        }
    }
    for(int p = b; p < e; p++) t[p]=t2[p];
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



BENCHMARK_MAIN();
