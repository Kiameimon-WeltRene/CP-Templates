#ifndef DISJOINTSETUNION_CPP
#define DISJOINTSETUNION_CPP

#include "DisjointSetUnion.hpp"

DisjointSetUnion::DisjointSetUnion(int n) 
    : n(n), 
      set_count(n), 
      dsu(n, -1) {}

int DisjointSetUnion::root(int x) {
    // Path compression: make parent of x point directly to root
    return dsu[x] < 0 ? x : (dsu[x] = root(dsu[x]));
}

void DisjointSetUnion::join(int x, int y) {
    x = root(x);
    y = root(y);
    
    // Already in same set
    if (x == y) return;
    
    // Union by size: smaller tree joins larger tree
    if (dsu[x] < dsu[y]) {
        std::swap(x, y);
    }
    
    dsu[y] += dsu[x];  // Update size
    dsu[x] = y;        // Make x point to y
    set_count--;       // Decrease set count
}

bool DisjointSetUnion::query(int x, int y) {
    return root(x) == root(y);
}

int DisjointSetUnion::size(int x) {
    return -dsu[root(x)];  // Size stored as negative number
}

int DisjointSetUnion::count() const {
    return set_count;
}

#endif // DISJOINTSETUNION_CPP

