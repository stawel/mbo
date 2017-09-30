#ifndef PRINT_H
#define PRINT_H


template<class G>
void print(G &graph) {
    for(int i=0;i<graph.g.size();i++) {
        cout << i << ":";
        for(auto &v: graph.g[i]) cout << " " << v.v;
        cout << "\n";
    }
}

template<class V>
void printV_(V& v) {
    cout << "s: " << v.s << " t:" << v.t;
}

template<class G>
void printV(G &graph) {
    for(int i=0;i<graph.g.size();i++) {
        cout << i << "(", printV_(graph.g[i]), cout << "):\t";
        for(auto &v: graph.g[i]) cout << " " << v.v;
        cout << "\n";
    }
}


#endif
