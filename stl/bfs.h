#ifndef BFS_H
#define BFS_H

template<class G>
void bfs(G &graph, int s) {
    auto &g = graph.g;
    for(auto &i: g)
        i.t = i.s = -1;
    g[s].t = 0;
    int qu[g.size()], b=0, e=1;
    qu[0] = s;
    while (b < e) {
        s = qu[b++];
        for(auto &d: g[s])
            if (g[d.v].t == -1) {
                qu[e++] = d.v;
                g[d.v].t = g[s].t + 1;
                g[d.v].s = s;
            }
    }
}

struct Vbfs {
    int t,s;
};

#endif
