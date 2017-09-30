#include <cmath>
#include <cstdio>
#include <iostream>

//TODO: implementation not verified

#define LL long long
LL inf = 100000000000LL;

#define MAX_G 1000000
#define MAX_E 40000000

int N, M;

//----------------- graph

struct Edge {
    int g; //node
    int c; //cost
    int next;
};

int graph[MAX_G]; //nodes start at graph[1]
Edge edge[MAX_E];  //edges start at e[1]
int edge_count;

void addE(int a, int b, int c) {
    edge[++edge_count] = {b, c, graph[a]};
    graph[a] = edge_count;
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
        for(int next = graph[g1]; next; next = edge[next].next) {
            int g2 = edge[next].g;
            LL v2 = dist[g1] + edge[next].c;
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
