#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// array - 1,30358s
// list  - 1,41626s

#define LL long long
LL inf = 100000000000LL;

#define MAX 1010*1024
int N, M, K, K_shift;

struct E {
    int g;
    int v;
    int next;
};

int graf[MAX];
E e[MAX * 40];
int e_count;

void addE(int a, int b, int v) {
    e[++e_count] = {b, v, graf[a]};
    graf[a] = e_count;
}

void addS(int s, int f) {
    s *= K_shift;
    int bit = 1 << (f - 1);
    for (int i = 0; i < K_shift; i++)
        if (!(i & bit))
            addE(s + i, s + i + bit, 0);
}

//  ----------------- heap
LL dist[MAX];
int pos[MAX];

int heap[MAX];
int size = 0;

inline void swap(int i, int j) {
    int p = pos[heap[i]];
    pos[heap[i]] = pos[heap[j]];
    pos[heap[j]] = p;
    int t = heap[i];
    heap[i] = heap[j];
    heap[j] = t;
}
inline bool heapLess(int i, int j) {
    return dist[heap[i]] < dist[heap[j]];
}
void up(int start) {
    while (start > 1 && heapLess(start, start / 2)) {
        swap(start / 2, start);
        start /= 2;
    }
}
void down(int i) {
    while (i * 2     <= size && heapLess(i * 2,     i)
        || i * 2 + 1 <= size && heapLess(i * 2 + 1, i)) {
        if (i * 2 == size || heapLess(i * 2, i * 2 + 1)) {
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
    pos[e] = size;
    up(size);
}
int pop() {
    int r = heap[1];
    swap(1, size--);
    down(1);
    return r;
}

// ------------ dijkstra

void dijkstra() {
    dist[1 * K_shift] = 0;
    push(1 * K_shift);
    for (int i = K_shift + 1; i < (N + 1) * K_shift; i++) {
        dist[i] = inf;
        push(i);
    }
    while (size) {
        int g1 = pop();
        int next = graf[g1];
        while (next) {
            int g2 = e[next].g;
            LL v2 = dist[g1] + e[next].v;
            if (dist[g2] > v2) {
                dist[g2] = v2;
                up(pos[g2]);
            }
            next = e[next].next;
        }
    }
}

int main() {

    scanf("%d %d %d", &N, &M, &K);
    K_shift = 1 << K;
    for (int k, j, i = 1; i <= N; i++) {
        scanf("%d", &j);
        while (j--) {
            scanf("%d", &k);
            addS(i, k);
        }
    }
    for (int a, b, v, i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &v);
        for (int j = 0; j < K_shift; j++) {
            addE(a * K_shift + j, b * K_shift + j, v);
            addE(b * K_shift + j, a * K_shift + j, v);
        }
    }
    dijkstra();

    LL r = inf;
    for (int i = 0; i < K_shift; i++) {
        LL r2 = max(dist[(N << K) + i], dist[(N << K) + (i ^ (K_shift - 1))]);
        if (r > r2) r = r2;
    }

    printf("%lld\n", r);

    return 0;
}
