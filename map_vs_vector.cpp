#include <vector>
#include <map>
#include <unordered_map>

using namespace std;




//--------------BENCHMARK-------------
#include "benchmark/benchmark.h"
//#include <cassert>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <cstdlib>

#define CHECK(x) x

#define ASSERT(x) if(!(x)) std::cerr << "ASSERT " << __PRETTY_FUNCTION__ << " line:" << __LINE__ << " assert: "<< #x << std::endl, std::abort();


static void BM_vector(benchmark::State& state) {
    state.KeepRunning();
    state.PauseTiming();
    vector<pair<int,int>> v;
    for (int i=0;i<state.range(0);i++) {
        v.push_back(make_pair(rand(), rand()));
    }
    unsigned long long out=0;
    state.ResumeTiming();
    while (state.KeepRunning()) {
        state.PauseTiming();
        int x2 = v[rand()%v.size()].first;
        state.ResumeTiming();
        for(auto &x:v) {
            if(x.first == x2) {
                out += (unsigned long long)&x;
                break;
            }
        }
    }
}

static void BM_map(benchmark::State& state) {
    state.KeepRunning();
    state.PauseTiming();
    map<int,int> v1;
    vector<pair<int,int>> v;
    for (int i=0;i<state.range(0);i++) {
        auto p = make_pair(rand(), rand());
        v.push_back(p);
        v1.insert(p);
    }
    unsigned long long out=0;
    state.ResumeTiming();
    while (state.KeepRunning()) {
        state.PauseTiming();
        int x2 = v[rand()%v.size()].first;
        state.ResumeTiming();
        auto x = v1.find(x2);
        out += (unsigned long long)&x;
    }
}

static void BM_umap(benchmark::State& state) {
    state.KeepRunning();
    state.PauseTiming();
    unordered_map<int,int> v1;
    vector<pair<int,int>> v;
    for (int i=0;i<state.range(0);i++) {
        auto p = make_pair(rand(), rand());
        v.push_back(p);
        v1.insert(p);
    }
    unsigned long long out=0;
    state.ResumeTiming();
    while (state.KeepRunning()) {
        state.PauseTiming();
        int x2 = v[rand()%v.size()].first;
        state.ResumeTiming();
        auto x = v1.find(x2);
        out += (unsigned long long)&x;
    }
}


static void CustomArguments(benchmark::internal::Benchmark* b) {
    int v[] = {1,5,10,20,30,40,50,60,70,80,90, 100};
    for(auto x:v)
      b->Args({x});
}


#define BM(x) BENCHMARK(x)->Apply(CustomArguments)



BM(BM_vector);
BM(BM_map);
BM(BM_umap);



BENCHMARK_MAIN();
