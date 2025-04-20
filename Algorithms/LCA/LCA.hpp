#ifndef LCA_HPP
#define LCA_HPP

#include <vector>
#include <cmath>

/**
 * Lowest Common Ancestor (LCA) implementation using binary lifting.
 * Supports:
 * - O(1) LCA queries after O(N log N) preprocessing
 * - O(log N) k-th ancestor queries
 */
class LCA {
public:
    /**
     * Constructs LCA structure from adjacency list
     * @param adjacency_list Tree represented as adjacency list (0-based index)
     */
    explicit LCA(const std::vector<std::vector<int>>& adjacency_list);

    /**
     * Preprocesses the tree for LCA queries
     * @param root Root node of the tree (default 0)
     */
    void preprocess(int root = 0);

    /**
     * Finds the k-th ancestor of a node
     * @param node Starting node
     * @param k Number of levels to go up
     * @return k-th ancestor or -1 if it doesn't exist
     */
    int kthAncestor(int node, int k) const;

    /**
     * Finds the lowest common ancestor of two nodes
     * @param u First node
     * @param v Second node
     * @return LCA of u and v
     */
    int findLCA(int u, int v) const;

private:
    /**
     * Performs DFS to compute binary lifting tables and depths
     * @param node Current node being processed
     * @param parent Parent of current node
     */
    void dfs(int node, int parent);

    int n;                          // Number of nodes
    int logN;                       // Maximum depth in binary representation
    std::vector<std::vector<int>> adj;  // Adjacency list
    std::vector<std::vector<int>> up;   // Binary lifting table
    std::vector<int> depth;             // Depth of each node
};

#endif // LCA_HPP
