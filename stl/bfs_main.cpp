
#include <vector>
#include <iostream>

using namespace std;
#include "graph.h"
#include "bfs.h"
#include "print.h"

int main() {
    int n, m, b, e;
    cin >> n >> m;
    Graph<Vbfs> g(n);
    while(m--) {
        cin >> b >> e;
        g.addE(b, e);
    }

    bfs(g, 1);
    printV(g);
    return 0;
}
