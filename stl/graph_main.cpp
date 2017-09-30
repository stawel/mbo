#include <bits/stdc++.h>

using namespace std;
#include "graph.h"
#include "print.h"

int main() {
    int n, m, b, e;
    cin >> n >> m;
    Graph<> g(n);
    while (m--) {
        cin >> b >> e;
        g.addE(b, e);
    }
    print(g);
    return 0;
}
