#ifndef BFS_H
#define BFS_H

template<class G>
void bfs(G &graph, int s) {
    auto &g = graph.g;
    for(auto &i: g)
        i.t = i.s = -1;
    g[s].t = 0;
    int b=0, e=1, queue[g.size()];
    queue[0] = s;
    while (b < e) {
        s = queue[b++];
        for(auto &d: g[s])
            if (g[d.v].t == -1) {
                queue[e++] = d.v;
                g[d.v].t = g[s].t + 1;
                g[d.v].s = s;
            }
    }
}

struct Vbfs {
    int t,s;
};

#endif
