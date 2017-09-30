#include <bits/stdc++.h>

using namespace std;
#include "graph.h"
#include "bfs.h"
#include "print.h"

int main() {
    int n, m, b, e;
    cin >> n >> m;
    Graph<Vbfs> g(n);
    while (m--) {
        cin >> b >> e;
        g.addE(b, e);
    }

    cin >> b;
    bfs(g, b);
    print(g);
    return 0;
}
