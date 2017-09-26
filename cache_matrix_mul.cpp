
#define MAX 2000

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];


void mul1(int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
}

void mul2(int n)
{
	for (int i = 0; i < n; i++)
			for (int k = 0; k < n; k++)
		for (int j = 0; j < n; j++)
				C[i][j] += A[i][k] * B[k][j];
}

void mul3(int n)
{
		for (int j = 0; j < n; j++)
	for (int i = 0; i < n; i++)
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
}

void mul4(int n)
{
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
				C[i][j] += A[i][k] * B[k][j];
}

void mul5(int n)
{
			for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
				C[i][j] += A[i][k] * B[k][j];
}

void mul6(int n)
{
			for (int k = 0; k < n; k++)
		for (int j = 0; j < n; j++)
	for (int i = 0; i < n; i++)
				C[i][j] += A[i][k] * B[k][j];
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


static void BM_mul1(benchmark::State &state)
{
	auto n = state.range(0);
	while (state.KeepRunning()) {
		mul1(n);
	}
}

static void BM_mul2(benchmark::State &state)
{
	auto n = state.range(0);
	while (state.KeepRunning()) {
		mul2(n);
	}
}
static void BM_mul3(benchmark::State &state)
{
	auto n = state.range(0);
	while (state.KeepRunning()) {
		mul3(n);
	}
}
static void BM_mul4(benchmark::State &state)
{
	auto n = state.range(0);
	while (state.KeepRunning()) {
		mul4(n);
	}
}
static void BM_mul5(benchmark::State &state)
{
	auto n = state.range(0);
	while (state.KeepRunning()) {
		mul5(n);
	}
}

static void BM_mul6(benchmark::State &state)
{
	auto n = state.range(0);
	while (state.KeepRunning()) {
		mul6(n);
	}
}




static void CustomArguments(benchmark::internal::Benchmark *b)
{
	int v[] = { 100, 500, 1000, 2000};
	for (auto x : v)
		b->Args({x});
}


#define BM(x) BENCHMARK(x)->Apply(CustomArguments)

BM(BM_mul1);
BM(BM_mul2);
BM(BM_mul3);
BM(BM_mul4);
BM(BM_mul5);
BM(BM_mul6);



BENCHMARK_MAIN();
