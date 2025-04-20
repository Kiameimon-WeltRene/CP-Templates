#ifndef LCA_CPP
#define LCA_CPP

#include "LCA.hpp"

LCA::LCA(const std::vector<std::vector<int>>& adjacency_list) 
    : adj(adjacency_list), 
      n(adjacency_list.size()),
      logN(static_cast<int>(std::log2(n)) + 1) {
    
    // Initialize binary lifting table and depth array
    up.assign(n, std::vector<int>(logN, -1));
    depth.assign(n, 0);
}

void LCA::preprocess(int root) {
    // Start DFS from root to build binary lifting tables
    dfs(root, -1);
}

void LCA::dfs(int node, int parent) {
    // Set first ancestor (immediate parent)
    up[node][0] = parent;
    
    // Fill binary lifting table using dynamic programming
    for (int j = 1; j < logN; ++j) {
        if (up[node][j - 1] != -1) {
            up[node][j] = up[up[node][j - 1]][j - 1];
        }
    }
    
    // Process children recursively
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        
        depth[neighbor] = depth[node] + 1;
        dfs(neighbor, node);
    }
}

int LCA::kthAncestor(int node, int k) const {
    // Climb the tree using binary representation of k
    for (int j = 0; j < logN && node != -1; ++j) {
        if (k & (1 << j)) {
            node = up[node][j];
        }
    }
    return node;
}

int LCA::findLCA(int u, int v) const {
    // Bring both nodes to the same depth
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }
    
    // Jump u up to depth of v
    u = kthAncestor(u, depth[u] - depth[v]);
    if (u == v) return u;
    
    // Binary search for LCA
    for (int j = logN - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

#endif // LCA_CPP
