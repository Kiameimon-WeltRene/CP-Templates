#ifndef HLD_CPP
#define HLD_CPP

#include "HLD.hpp"

template <typename T, typename U, auto op, auto update>
HLD<T, U, op, update>::HLD(const std::vector<std::vector<int>>& adjList) 
    : adj(adjList),
      n(adjList.size()),
      counter(1),
      size(n + 1, 1),
      preorder(n + 1),
      nxt(n + 1),
      parent(n + 1),
      depth(n + 1),
      segTree(n + 1, T{}) {  // Initialize with identity element

    // Initialize with root at 1
    parent[1] = 1;
    nxt[1] = 1;

    // Perform decomposition
    DFS_Size(1, 0);
    DFS_HLD(1, 0);
}

template <typename T, typename U, auto op, auto update>
void HLD<T, U, op, update>::DFS_Size(int cur, int par) {
    for (auto& child : adj[cur]) {
        if (child == par) continue;
        
        depth[child] = depth[cur] + 1;
        parent[child] = cur;
        
        DFS_Size(child, cur);
        size[cur] += size[child];
        
        // Make the heaviest child first in adjacency list
        if (size[child] > size[adj[cur][0]]) {
            std::swap(child, adj[cur][0]);
        }
    }
}

template <typename T, typename U, auto op, auto update>
void HLD<T, U, op, update>::DFS_HLD(int cur, int par) {
    preorder[cur] = counter++;
    for (int child : adj[cur]) {
        if (child == par) continue;
        
        // Continue same chain or start new one
        nxt[child] = (child == adj[cur][0] ? nxt[cur] : child);
        DFS_HLD(child, cur);
    }
}

template <typename T, typename U, auto op, auto update>
void HLD<T, U, op, update>::UpdatePath(int u, int v, U value) {
    while (nxt[u] != nxt[v]) {
        if (depth[nxt[u]] < depth[nxt[v]]) {
            std::swap(u, v);
        }
        segTree.Update(preorder[nxt[u]], preorder[u], value);
        u = parent[nxt[u]];
    }
    
    // Update the remaining path
    if (preorder[u] > preorder[v]) {
        std::swap(u, v);
    }
    segTree.Update(preorder[u], preorder[v], value);
}

template <typename T, typename U, auto op, auto update>
T HLD<T, U, op, update>::QueryPath(int u, int v) {
    T result = T{};  // Initialize with identity
    while (nxt[u] != nxt[v]) {
        if (depth[nxt[u]] < depth[nxt[v]]) {
            std::swap(u, v);
        }
        result = op(result, segTree.Query(preorder[nxt[u]], preorder[u]));
        u = parent[nxt[u]];
    }
    
    // Query the remaining path
    if (preorder[u] > preorder[v]) {
        std::swap(u, v);
    }
    result = op(result, segTree.Query(preorder[u], preorder[v]));
    
    return result;
}

#endif // HLD_CPP
