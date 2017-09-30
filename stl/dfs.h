#ifndef DFS_H
#define DFS_H

static int dfs_t;

template<class G>
void dfsV(G &graph,int v) {
    auto &g = graph.g;
    g[v].t1 = dfs_t++;
    for(auto &i: graph.g[v])
    if (g[i.v].s == -1) {
        g[i.v].s = v;
        dfsV(graph, i.v);
    }
    g[v].t2 = dfs_t++;
}

template<class G>
void dfs(G &graph, int e = -1) {
    dfs_t = 0;
    int b = 0;
    e == -1 ? e = graph.g.size() : b = e + 1;
    for (auto &v : graph.g)
        v.t1 = v.t2 = v.s = -1;
    for (int i = b; i < e; i++)
        if (graph.g[i].s == -1)
            dfsV(graph, i);
}

struct Vdfs {
    int t1, t2, s;
};

#endif
