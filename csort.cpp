
#define MAX 1000000


static int count[MAX];

void csort(int *from, int *to, int size, int mask) {
    for(int i=0;i<size;i++) count[from[i]&mask]++;
    for(int j=0, i=0;i<=mask;i++)
        while(count[i]--) to[j++]=i;
}


//---------------------------

#include "benckmark/benchmark.h"

static void BM_csort(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto n = state.range(0);
        auto mask = state.range(1);
        std::vector<int> v(n), r(n);
        for(auto &x:v) x = rand()&mask;
        auto v2 = v;
        std::sort(v2.begin(), v2.end());
        state.ResumeTiming();
        csort(v.data(), r.data(), v.size(), mask);
        state.PauseTiming();
        assert(std::equal(r.begin(),r.end(),v2.begin());
    }
}


// Register the function as a benchmark
BENCHMARK(BM_csort)->Args({1<<10, 7})
    ->Args({1<<10, 63})
    ->Args({1<<10, 511});

// Define another benchmark

BENCHMARK_MAIN();