#include <cmath>
#include <cstdio>
#include <iostream>

//TODO: implementation not verified

#define LL long long
LL inf = 100000000000LL;

#define MAX_G 1000000

int N, M;
//-------------  array
template<class T>
struct array {
    T * v;
    int size, alloc;
    array(int a = 2) : size(0), alloc(a) { v = (T*) calloc(a, sizeof(T)); }
    void re(int a) {
        alloc = a;
        v = (T*) realloc(v, sizeof(T) * a);
    }
    void push_back(T x) {
        if (size + 1 > alloc)
            re(alloc * 2);
        v[size++] = x;
    }
    T& operator[](int idx) { return v[idx]; }
};
//----------------- graph

struct Edge {
    int g; //node
    int c; //cost
};

array<Edge> graph[MAX_G];

void addE(int a, int b, int c) {
    graph[a].push_back({b, c});
}

//  ----------------- heap

LL dist[MAX_G];
int pos[MAX_G];

int heap[MAX_G]; //heap starts at heap[1]
int heap_size = 0;

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
    while (i * 2     <= heap_size && heapLess(i * 2,     i)
        || i * 2 + 1 <= heap_size && heapLess(i * 2 + 1, i)) {
        if (i * 2 == heap_size || heapLess(i * 2, i * 2 + 1)) {
            swap(i, i * 2);
            i = i * 2;
        } else {
            swap(i, i * 2 + 1);
            i = i * 2 + 1;
        }
    }
}
void push(int e) {
    heap[++heap_size] = e;
    pos[e] = heap_size;
    up(heap_size);
}
int pop() {
    int r = heap[1];
    swap(1, heap_size--);
    down(1);
    return r;
}

// ------------ dijkstra

void dijkstra(int from, int to, int start) {
    for (int i = from; i < to; i++) {
        dist[i] = inf;
        push(i); //TODO: might be optimized
    }
    dist[start] = 0;
    up(pos[start]);

    while (heap_size) {
        int g1 = pop();
        for(int i = 0; i < graph[g1].size; i++) {
            int g2 = graph[g1][i].g;
            LL v2 = dist[g1] + graph[g1][i].c;
            if (dist[g2] > v2) {
                dist[g2] = v2;
                up(pos[g2]);
            }
        }
    }
}

// --------------- main
int main() {

    scanf("%d %d", &N, &M);
    for (int a, b, c, i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &c);
        addE(a, b, c);
        addE(b, a, c);
    }
    dijkstra(1, N, 1);

    printf("%lld\n", dist[N]);
    return 0;
}
