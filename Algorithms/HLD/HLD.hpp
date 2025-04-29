#ifndef HLD_HPP
#define HLD_HPP

#include <vector>
#include <algorithm>
#include "../DataStructures/SegmentTree/SegmentTree.hpp"

/**
 * Heavy-Light Decomposition (HLD) implementation.
 * Supports path queries and updates on trees with customizable operations.
 *
 * @tparam T The type of values stored in the tree
 * @tparam U The type of update values
 * @tparam op The associative operation function (e.g., sum, min, max)
 * @tparam update Function to update a value with an update value
 */
template <typename T, typename U, auto op, auto update>
class HLD {
    // Type trait to check if operation is valid
    template <typename F, typename A, typename B>
    static constexpr bool IsOpCallable =
        std::is_invocable_r_v<T, F, A, B> || 
        std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || 
        std::is_invocable_r_v<T, F, A&, B&>;

    // Type trait to check if update is valid
    template <typename F, typename A, typename B>
    static constexpr bool IsUpdateCallable =
        std::is_invocable_r_v<T, F, A, B> || 
        std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || 
        std::is_invocable_r_v<T, F, A&, B&>;

    static_assert(IsOpCallable<decltype(op), T, T>,
                "Operation must be callable with (T, T) and return T");
    static_assert(IsUpdateCallable<decltype(update), T, U>,
                "Update must be callable with (T, U) and return T");

public:
    /**
     * Constructs HLD structure from adjacency list
     * @param adj The tree represented as adjacency list (1-based index)
     */
    explicit HLD(const std::vector<std::vector<int>>& adj);

    /**
     * Updates all nodes on the path from u to v
     * @param u First node (1-based)
     * @param v Second node (1-based)
     * @param value Update value to apply
     */
    void UpdatePath(int u, int v, U value);

    /**
     * Queries the path from u to v
     * @param u First node (1-based)
     * @param v Second node (1-based)
     * @return Result of applying operation along the path
     */
    T QueryPath(int u, int v);

private:
    /**
     * Computes subtree sizes and prepares for HLD
     * @param cur Current node being processed
     * @param par Parent of current node
     */
    void DFS_Size(int cur, int par);

    /**
     * Performs the HLD decomposition
     * @param cur Current node being processed
     * @param par Parent of current node
     */
    void DFS_HLD(int cur, int par);

    int n;                          // Number of nodes
    int counter;                    // Preorder counter
    std::vector<std::vector<int>> adj;  // Adjacency list
    std::vector<int> size;          // Subtree sizes
    std::vector<int> preorder;      // Preorder numbering
    std::vector<int> nxt;           // Head of heavy chain
    std::vector<int> parent;        // Parent nodes
    std::vector<int> depth;         // Node depths
    SegmentTree<T, U, op, update> segTree;  // Underlying segment tree
};

#endif // HLD_HPP
