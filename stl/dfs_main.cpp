#include <bits/stdc++.h>

using namespace std;
#include "graph.h"
#include "dfs.h"
#include "print.h"

int main() {
    int n, m, b, e;
    cin >> n >> m;
    Graph<Vdfs> g(n);
    while (m--) {
        cin >> b >> e;
        g.addE(b, e);
    }

    dfs(g);
    print(g);
    return 0;
}
