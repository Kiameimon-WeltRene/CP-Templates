# Heavy-Light Decomposition (HLD) Template

A C++ template implementation of Heavy-Light Decomposition (HLD) that supports efficient path queries and path updates on trees with customizable operations. It uses an underlying Segment Tree to handle the operations on heavy paths.

## Features

- Path Queries: Supports customizable operations (e.g., `sum`, `min`, `max`) over the path between any two nodes
- Path Updates: Supports applying updates to all nodes on the path between two nodes using a custom update function
- Efficient Operations: $O(\log^2 N)$ time complexity for both queries and updates, where $N$ is the number of nodes
- Generic: Works with any type `T` for node values and `U` for updates, with customizable operation and update functions. For more info, see [this section](#notes)
- Tree Structure: Operates on trees represented as adjacency lists with 1-based indexing

## Usage

### Initialization

The Heavy-Light Decomposition can be initialized with an adjacency list representing the tree:

```cpp
std::vector<std::vector<int>> adj = {{}, {2, 3}, {1, 4}, {1, 5}, {2}, {3}}; // 1-based indexing
auto op = [](int a, int b) -> int {
    return a + b;
};
auto update = [](int curval, int v) { return curval + v; };
HLD<int, int, op, update> hld(adj);
```

- **Time Complexity**: $O(N)$ for preprocessing the tree and building the underlying Segment Tree, where $N$ is the number of nodes
- **Space Complexity**: $O(N)$ for the adjacency list, HLD metadata, and Segment Tree
- **Requirements**: An adjacency list `adj` (1-based indexing, where `adj[i]` lists neighbors of node `i`), and compatible `op` and `update` functions

Specifically:
- `op` must take two arguments `a` and `b` (of type `T` or `T&`) and return the result of the operation (type `T`).
- `update` must take two arguments `curval` (type `T` or `T&`) and `updval` (type `U` or `U&`) and return the updated value (type `T`).

### Public Methods

1. **Querying a path**:
    ```cpp
    QueryPath(u, v)
    ```
    - **Description**: Computes the result of the operation `op` over the values of nodes on the path from node `u` to node `v` (1-based indexing).
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `u` and `v` must be valid node indices (1 to $N$)
    - **Example**:
        ```cpp
        int sum = hld.QueryPath(2, 5); // Sum of node values on the path from node 2 to 5
        ```

2. **Updating a path**:
    ```cpp
    UpdatePath(u, v, value)
    ```
    - **Description**: Applies the `update` function to all nodes on the path from node `u` to node `v` (1-based indexing) with the given `value` of type `U`.
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `u` and `v` must be valid node indices (1 to $N$), and `value` must be of type `U`
    - **Example**:
        ```cpp
        hld.UpdatePath(2, 5, 10); // Add 10 to all nodes on the path from node 2 to 5
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Algorithms/HLD/HLD.hpp"

int main() {
    // Initialize a tree with 5 nodes (1-based indexing)
    // Tree structure:
    //       1
    //      / \
    //     2   3
    //    /     \
    //   4       5
    std::vector<std::vector<int>> adj = {{}, {2, 3}, {1, 4}, {1, 5}, {2}, {3}};

    // Define operations for sum queries and addition updates
    auto op = [](int a, int b) { return a + b; };
    auto update = [](int curval, int v) { return curval + v; };
    HLD<int, int, op, update> hld(adj);

    // Assign initial values to nodes (via updates)
    hld.UpdatePath(1, 1, 1); // Node 1 = 1
    hld.UpdatePath(2, 2, 2); // Node 2 = 2
    hld.UpdatePath(3, 3, 3); // Node 3 = 3
    hld.UpdatePath(4, 4, 4); // Node 4 = 4
    hld.UpdatePath(5, 5, 5); // Node 5 = 5

    // Perform a path query
    int sum = hld.QueryPath(2, 5); // Sum of nodes on path 2->1->3->5
    std::cout << "sum over the path [2, 5]: " << sum << '\n';
    // sum = 2 + 1 + 3 + 5 = 11

    // Update a path
    hld.UpdatePath(2, 5, 10); // Add 10 to nodes on path 2->1->3->5
    // Node values now: [11, 12, 13, 4, 15]

    // Query again
    sum = hld.QueryPath(2, 5); // Now sum = 12 + 11 + 13 + 15 = 51
    std::cout << "sum over the path [2, 5] after update: " << sum << '\n';

    // Query a single node
    sum = hld.QueryPath(2, 2); // Value at node 2
    std::cout << "value at node 2: " << sum << '\n';
    // value = 12

    return 0;
}
```

## Notes

- The Heavy-Light Decomposition is highly customizable through the `op` and `update` functions:
  - `op` defines the operation for path queries (e.g., `+`, `-`, `*`, `gcd`, `lcm`, `min`, `max`, and many more).
  - `update` defines how updates are applied to node values (e.g., incrementing, assigning, multiplying by the update value, and many more).
- The operation `op` must satisfy the following properties:
    - It is **associative**:
        ```cpp
        assert(op(op(a, b), c) == op(a, op(b, c))); // this must be true for all a, b, c
        ```
    - You have to provide an **identity element** `e` such that:
        ```cpp
        T a, e;
        T a_op_e = op(a, e);
        assert(a == a_op_e); // this must be true for all a
        ```
        For example, `0` is the identity for addition, and `INT_MAX` is the identity for minimum.
    In Mathematics, this is known as a [monoid](https://en.wikipedia.org/wiki/Monoid).
- **Update Requirement**: The `update` function must allow the new value of any node to be determined based solely on the current value and the update value. For example, adding a value to a node or assigning a new value to a node are valid, as the result depends only on the current state and the update.
- **Time Complexity**: Initialization takes $O(N)$, and both queries and updates are $O(\log^2 N)$ multiplied by the time to perform the `op` or `update` functions for types `T` and `U`, where $N$ is the number of nodes.
- **Identity Element**: The underlying Segment Tree requires an identity element for the operation (e.g., `0` for sum), which is managed internally by the HLD.
- **Custom Types**: Ensure `op` and `update` are compatible with types `T` and `U`. For example:
    ```cpp
    struct LinearFunction {
        int m, c; // Represents y = mx + c
        LinearFunction(int m = 1, int c = 0) : m(m), c(c) {}
        // Compose two linear functions: f(g(x)) = m1*(m2*x + c2) + c1 = (m1*m2)*x + (m1*c2 + c1)
        LinearFunction compose(const LinearFunction& other) const {
            return LinearFunction{m * other.m, m * other.c + c};
        }
        bool operator==(const LinearFunction& other) const {
            return m == other.m && c == other.c;
        }
    };

    // Define the operation for combining two LinearFunctions (function composition)
    auto op = [](LinearFunction a, LinearFunction b) -> LinearFunction {
        return a.compose(b);
    };

    // Define the update function: adds v to the slope m
    auto update = [](LinearFunction curval, int v) -> LinearFunction {
        curval.m += v;
        return curval;
    };

    HLD<LinearFunction, int, op, update> hld(adj);
    ```

## More Info

You can read more about how Heavy-Light Decomposition works from [cp-algorithms](https://cp-algorithms.com/graph/hld.html).
- This algorithm is particularly useful for problems involving queries and updates on paths in a tree, such as computing sums, minimums, or maximums along a path or updating node values along a path in a tree. However, if you do not need updates, you can handle queries in O(\log N)$ or better (with some preprocessing time). There are many algorithms for that: for example, Binary Lifting.
- For further reading on the topic:
  - [This blog](https://usaco.guide/plat/hld?lang=cpp) provides a detailed explanation of HLD and a list of some competitive programming problems using it.