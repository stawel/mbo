
#define MAX_SIZE 100000000
int heap[MAX_SIZE];  //heap starts at heap[1]
int size = 0;

inline void swap(int i, int j) {
    int t = heap[i];
    heap[i] = heap[j];
    heap[j] = t;
}
inline bool Less(int i, int j) {
    return heap[i] < heap[j];
}
void up(int start) {
    while (start > 1 && Less(start, start / 2)) {
        swap(start / 2, start);
        start /= 2;
    }
}
void down(int i) {
    while (  i * 2     <= size && Less(i * 2, i)
          || i * 2 + 1 <= size && Less(i * 2 + 1, i)) {
        if ( i * 2     == size || Less(i * 2, i * 2 + 1)) {
            swap(i, i * 2);
            i = i * 2;
        } else {
            swap(i, i * 2 + 1);
            i = i * 2 + 1;
        }
    }
}

void push(int e) {
    heap[++size] = e;
    up(size);
}
int pop() {
    int r = heap[1];
    swap(1, size--);
    down(1);
    return r;
}

void make_heap() {
    //not implemented!
}

//----------heap sort

void hsort(int *T, int size) {
    for(int i=0;i<size;i++) push(T[i]);
    for(int i=0;i<size;i++) T[i]=pop();
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
