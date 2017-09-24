
#define MAP_SIZE   100000000
#define DATA_SIZE  100000000

struct Data {
    int data;

    int key;
    int next;
};

//data starts at data[1]
Data data[DATA_SIZE];
int data_size = 0;

int hashMap[MAP_SIZE];
int map_size; //needed only for benchmarking

inline int hash(int key) {
    return key % map_size;
}

void put(int idx) {
    int h = hash(data[idx].key);
    data[idx].next = hashMap[h];
    hashMap[h] = idx;
}

int get(int key) {
    int idx = hashMap[hash(key)];
    while (idx != 0 && data[idx].key != key)
        idx = data[idx].next;
    return idx;
}

void remove(int key) {
    data[get(key)].key = -1;
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


void create_set(int n) {
    data_size = 0;
    for(int i=0;i<map_size;i++) hashMap[i]=0;
    for(int i=0;i<n;i++) {
        Data d{i,rand(), 0};
        data[++data_size] = d;
    }
}
void put_set() {
    for(int i=1;i<=data_size;i++) {
        put(i);
    }
}

static void BM_put(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto n = state.range(0);
        map_size = state.range(1);
        create_set(n);
        state.ResumeTiming();
        put_set();
    }
}

static void BM_get(benchmark::State& state) {
    state.KeepRunning();
    state.PauseTiming();
    auto n = state.range(0);
    map_size = state.range(1);
    create_set(n);
    put_set();
    bool ok = true;
    state.ResumeTiming();
    while (state.KeepRunning()) {
        for(int i=0;i<n;i++) {
            int idx = 1 + (rand()%data_size);
            int r = get(data[idx].key);
            ok = ok && (data[r].key == data[idx].key);
        }
        ASSERT(ok);
    }
}



static void CustomArguments(benchmark::internal::Benchmark* b) {
    auto v1 = {1, 1<<4, 1<<8, 1<<12};
    auto v2 = {1, 2, 4, 8, 16};

    for(auto x:v1)
        for(auto y:v2)
            b->Args({y*x*(1<<8), x*(1<<10)});
}


#define BM(x) BENCHMARK(x)->Apply(CustomArguments)

//#define BM(x) BENCHMARK(x)->RangeMultiplier(8)->Ranges({{1<<16, 1<<24},{1<<16, 1<<24} })

BM(BM_get);
BM(BM_put);


BENCHMARK_MAIN();
