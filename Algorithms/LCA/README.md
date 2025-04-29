# Lowest Common Ancestor (LCA) Template

A C++ implementation of Lowest Common Ancestor (LCA) using binary lifting, designed for efficient ancestor and LCA queries on trees.

## Features

- LCA Queries: Finds the lowest common ancestor of two nodes in $O(1)$ time after preprocessing
- K-th Ancestor Queries: Finds the k-th ancestor of a node in $O(\log N)$ time
- Efficient Preprocessing: $O(N \log N)$ preprocessing for building the binary lifting table
- Tree Structure: Operates on trees represented as adjacency lists with 0-based indexing

## Usage

### Initialization

The LCA structure can be initialized with an adjacency list representing the tree:

```cpp
std::vector<std::vector<int>> adj = {{1, 2}, {0, 3}, {0, 4}, {1}, {2}}; // 0-based indexing
LCA lca(adj);
lca.preprocess(); // Preprocess with default root (node 0)
```

- **Time Complexity**: $O(N \log N)$ for preprocessing, where $N$ is the number of nodes
- **Space Complexity**: $O(N \log N)$ for the binary lifting table and adjacency list
- **Requirements**: An adjacency list `adj` (0-based indexing, where `adj[i]` lists neighbors of node `i`)

### Public Methods

1. **Finding the k-th ancestor**:
    ```cpp
    kthAncestor(node, k)
    ```
    - **Description**: Returns the k-th ancestor of `node` (0-based indexing) or `-1` if it doesn't exist.
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `node` must be a valid node index (0 to $N-1$), and `k` must be non-negative
    - **Example**:
        ```cpp
        int ancestor = lca.kthAncestor(3, 1); // Find the 1st ancestor of node 3
        ```

2. **Finding the lowest common ancestor**:
    ```cpp
    findLCA(u, v)
    ```
    - **Description**: Returns the lowest common ancestor of nodes `u` and `v` (0-based indexing).
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `u` and `v` must be valid node indices (0 to $N-1$)
    - **Example**:
        ```cpp
        int lca_node = lca.findLCA(3, 4); // Find the LCA of nodes 3 and 4
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include "Algorithms/LCA/LCA.hpp"

int main() {
    // Initialize a tree with 5 nodes (0-based indexing)
    // Tree structure:
    //       0
    //      / \
    //     1   2
    //    /     \
    //   3       4
    std::vector<std::vector<int>> adj = {{1, 2}, {0, 3}, {0, 4}, {1}, {2}};

    // Initialize and preprocess LCA
    LCA lca(adj);
    lca.preprocess(); // Root at node 0

    // Perform an LCA query
    int lca_node = lca.findLCA(3, 4); // LCA of nodes 3 and 4
    std::cout << "LCA of nodes 3 and 4: " << lca_node << '\n';
    // lca_node = 0 (node 0 is the LCA)

    // Perform a k-th ancestor query
    int ancestor = lca.kthAncestor(3, 1); // 1st ancestor of node 3
    std::cout << "1st ancestor of node 3: " << ancestor << '\n';
    // ancestor = 1 (parent of node 3)

    // Query k-th ancestor that doesn't exist
    ancestor = lca.kthAncestor(3, 5); // 5th ancestor of node 3
    std::cout << "5th ancestor of node 3: " << ancestor << '\n';
    // ancestor = -1 (does not exist)

    return 0;
}
```

## Notes

- The LCA implementation uses **binary lifting** to achieve efficient queries:
  - The binary lifting table stores ancestors at power-of-2 distances, enabling $O(1)$ LCA queries and $O(\log N)$ k-th ancestor queries.
  - Preprocessing involves a DFS to compute node depths and populate the binary lifting table.
- **Preprocessing Requirement**: The `preprocess` method must be called after initialization to build the binary lifting table. By default, it uses node 0 as the root, but a custom root can be specified.
- **Tree Structure**: The implementation assumes an undirected tree (bidirectional edges in the adjacency list). The adjacency list must be correctly formatted with 0-based indexing.
- **Time Complexity**:
  - Initialization and preprocessing: $O(N \log N)$, where $N$ is the number of nodes.
  - LCA queries: $O(1)$.
  - K-th ancestor queries: $O(\log N)$.
- **Space Complexity**: $O(N \log N)$ for the binary lifting table, depth array, and adjacency list.
- **Usage Considerations**:
  - The implementation is not generic in terms of operations (unlike Segment Trees or HLD). It is specifically designed for LCA and k-th ancestor queries.
  - For weighted trees or path queries requiring operations (e.g., sum, max), consider combining with a Heavy-Light Decomposition (HLD) structure.
- **Custom Root**: The `preprocess` method allows specifying a custom root node:
    ```cpp
    lca.preprocess(2); // Use node 2 as the root
    ```
- **Edge Cases**: The `kthAncestor` method returns `-1` if the k-th ancestor does not exist (e.g., if `k` exceeds the node's depth).

## More Info

You can read more about how Lowest Common Ancestor with binary lifting works from [cp-algorithms](https://cp-algorithms.com/graph/lca_binary_lifting.html).
- This algorithm is particularly useful for problems involving tree queries, such as finding the common ancestor of two nodes, computing distances in a tree, and can be used to handle .
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/100826) provides a detailed explanation of binary lifting for LCA and its applications.
  - [This blog](https://codeforces.com/blog/entry/74847) describes an alternative implementation of LCA that only requires $O(N)$ memory.