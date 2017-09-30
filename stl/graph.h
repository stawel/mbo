#ifndef GRAPH_H
#define GRAPH_H

struct Empty {};

template<class V = Empty, class E = Empty>
struct Graph {

    struct Ed: E {
        int v;
        Ed(E p, int w) : E(p), v(w) {}
    };
    struct Ve: V, vector<Ed> {};

    vector<Ve> g;

    Graph(int n = 0) : g(n) {}

    void addE(int b, int e, E d = E()) {
        g[b].push_back(Ed(d, e));
    }
    void add2E(int b, int e, E d = E()) {
        Ed eg(d, e);
        eg.rev = g[e].size() + (b == e);
        g[b].push_back(eg);
        eg.v = b;
        eg.rev = g[b].size() - 1;
        g[e].push_back(eg);
    }
};

#endif
