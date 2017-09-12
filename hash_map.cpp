
#define SIZE_MAP 100000000
#define SIZE_DATA 100000000


struct Data {
    int data;

    int key;
    int next;
}

//data starts at data[1]

Data data[SIZE_DATA];
int data_size = 0;

int hashMap[SIZE_MAP];
int size_map = SIZE_MAP; //needed only for benchmarks

inline int hash(int key) {
    return key%size_map;
}

void put(int idx) {
    int hash = hash(data[idx].key);
    data[idx].next = hashMap[hash];
    hashMap[hash] = idx;
}

int get(int key) {
    int idx = hashMap[hash];
    while(l != null){
        if (l->k == k) return l->e;
        l = l->next;
    }
    return null;
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


static void BM_hsort(benchmark::State& state) {
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
        hsort(v.data(), v.size());
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

BM(BM_hsort);
BM(BM_qsort);



BENCHMARK_MAIN();
