# Disjoint Set Union (DSU) Template

A C++ implementation of the Disjoint Set Union (DSU) data structure, also known as Union-Find, with path compression and union by size for efficient operations.

## Features

- Union Operations: Merges two sets containing given elements
- Find Operations: Finds the representative (root) of a set containing a given element
- Connectivity Queries: Checks if two elements are in the same set
- Efficient Operations: Nearly $O(\alpha(N))$ amortized time complexity for union and find operations, where $\alpha$ is the inverse Ackermann function
- Size Queries: Retrieves the size of a set or the total number of sets

## Usage

### Initialization

The Disjoint Set Union can be initialized with a specified number of elements:

```cpp
DisjointSetUnion dsu(5); // Initialize DSU with 5 elements (0 to 4)
```

- **Time Complexity**: $O(N)$, where $N$ is the number of elements
- **Space Complexity**: $O(N)$ for storing the parent/size array
- **Requirements**: A non-negative integer `n` representing the number of elements

### Public Methods

1. **Finding the root of a set**:
    ```cpp
    root(x)
    ```
    - **Description**: Returns the representative (root) of the set containing element `x` (0-based indexing).
    - **Time Complexity**: $O(\alpha(N))$ amortized
    - **Requirements**: `x` must be in range `[0, N)`
    - **Example**:
        ```cpp
        int r = dsu.root(2); // Get the root of the set containing element 2
        ```

2. **Joining two sets**:
    ```cpp
    join(x, y)
    ```
    - **Description**: Merges the sets containing elements `x` and `y` (0-based indexing) using union by size.
    - **Time Complexity**: $O(\alpha(N))$ amortized
    - **Requirements**: `x` and `y` must be in range `[0, N)`
    - **Example**:
        ```cpp
        dsu.join(1, 2); // Merge the sets containing elements 1 and 2
        ```

3. **Checking connectivity**:
    ```cpp
    query(x, y)
    ```
    - **Description**: Checks if elements `x` and `y` (0-based indexing) are in the same set.
    - **Time Complexity**: $O(\alpha(N))$ amortized
    - **Requirements**: `x` and `y` must be in range `[0, N)`
    - **Example**:
        ```cpp
        bool connected = dsu.query(1, 2); // Check if 1 and 2 are in the same set
        ```

4. **Getting the size of a set**:
    ```cpp
    size(x)
    ```
    - **Description**: Returns the size of the set containing element `x` (0-based indexing).
    - **Time Complexity**: $O(\alpha(N))$ amortized
    - **Requirements**: `x` must be in range `[0, N)`
    - **Example**:
        ```cpp
        int set_size = dsu.size(2); // Get the size of the set containing element 2
        ```

5. **Counting the number of sets**:
    ```cpp
    count()
    ```
    - **Description**: Returns the total number of disjoint sets.
    - **Time Complexity**: $O(1)$
    - **Requirements**: None
    - **Example**:
        ```cpp
        int num_sets = dsu.count(); // Get the number of disjoint sets
        ```

## Basic Usage

```cpp
#include <iostream>
#include "DataStructures/DisjointSetUnion/DisjointSetUnion.hpp"

int main() {
    // Initialize DSU with 5 elements
    DisjointSetUnion dsu(5);

    // Perform some union operations
    dsu.join(0, 1); // Merge sets containing 0 and 1
    dsu.join(1, 2); // Merge sets containing 1 and 2
    // Now 0, 1, 2 are in the same set

    // Check connectivity
    bool connected = dsu.query(0, 2);
    std::cout << "Are 0 and 2 in the same set? " << (connected ? "Yes" : "No") << '\n';
    // Output: Yes

    // Get the size of the set containing element 2
    int set_size = dsu.size(2);
    std::cout << "Size of the set containing 2: " << set_size << '\n';
    // Output: 3 (since 0, 1, 2 are in the set)

    // Get the total number of sets
    int num_sets = dsu.count();
    std::cout << "Total number of disjoint sets: " << num_sets << '\n';
    // Output: 3 (sets: {0,1,2}, {3}, {4})

    // Perform another union
    dsu.join(3, 4); // Merge sets containing 3 and 4
    num_sets = dsu.count();
    std::cout << "Total number of disjoint sets after joining 3 and 4: " << num_sets << '\n';
    // Output: 2 (sets: {0,1,2}, {3,4})

    return 0;
}
```

## Notes

- The Disjoint Set Union uses **path compression** and **union by size** to achieve near-constant time complexity ($O(\alpha(N))$ amortized) for `root`, `join`, and `query` operations, where $\alpha$ is the inverse Ackermann function, which grows extremely slowly.
- The implementation is **not generic** in terms of element types; it works with integer indices (0-based) representing elements. For custom types, you would need to map them to unique integers.
- **No Custom Types for Elements**: The DSU operates on integer indices. To use with custom types, create a mapping:
    ```cpp
    std::map<CustomType, int> type_to_index;
    DisjointSetUnion dsu(n);
    // Use type_to_index[custom_value] as the index in dsu operations
    ```

## More Info

You can read more about how a Disjoint Set Union works from [cp-algorithms](https://cp-algorithms.com/data_structures/disjoint_set_union.html).
- This data structure is particularly useful in graph algorithms, such as Kruskal's algorithm for minimum spanning trees or detecting cycles in undirected graphs.
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/98275) discusses the proof of the amortized inverse Ackermann time complexity (Be warned: it is rather technical)
  - [This blog](https://usaco.guide/adv/offline-del?lang=cpp) explores one of the advanced DSU modifications: supporting rollbacks