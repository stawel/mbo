#ifndef PRINT_H
#define PRINT_H

#include <type_traits>


class Empty;
template<class V>
typename std::enable_if<std::is_base_of<Empty, V>::value, void>::type
printV(V& v) {
}

class Vbfs;
template<class V>
typename std::enable_if<std::is_base_of<Vbfs, V>::value, void>::type
printV(V& v) {
    cout << "s:" << v.s << " t:" << v.t;
}

class Vdfs;
template<class V>
typename std::enable_if<std::is_base_of<Vdfs, V>::value, void>::type
printV(V& v) {
    cout << "s:" << v.s << " t1:" << v.t1 << " t2:" << v.t1;
}


template<template<class, class> class G, class V, class E>
void print(G<V,E> &graph) {
    for(int i=0;i<graph.g.size();i++) {
        cout << i << " (", printV(graph.g[i]), cout << "):\t";
        for(auto &v: graph.g[i]) cout << " " << v.v;
        cout << "\n";
    }
}


#endif
