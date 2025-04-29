# Sparse Table Template

A C++ template implementation of a Sparse Table that supports efficient range queries for associative and idempotent operations such as minimum, maximum, or GCD.

## Features

- Range Queries: Supports customizable operations (e.g., `min`, `max`, `gcd`) over any range `[left, right)`
- Efficient Queries: $O(1)$ time complexity for queries after preprocessing
- Generic: Works with any type `T` and operation `op` that is associative and idempotent. For more info, see [this section](#notes)
- Static Structure: Optimized for static data with no updates

## Usage

### Initialization

The Sparse Table can be initialized from a range of elements:

```cpp
std::vector<int> arr = {1, 3, 2, 4, 5};
SparseTable<int, op> st(arr.begin(), arr.end());
```

- **Time Complexity**: $O(N \log N)$, where $N$ is the size of the range
- **Space Complexity**: $O(N \log N)$ for storing the table
- **Requirements**: Input iterators (`start`, `end`) and a valid operation `op` 

Specifically:
- `op`
    ```cpp
    auto op = [](A a, B b) -> T {
        // define your operation: eg gcd(a, b), max(a, b), ...
    };
    ```
    `A` and `B` must be `T` or `T&` and `op` must return the result of the operation (type `T`). For example, if the operation is `min`, you should return `min(a, b)`.
### Public Methods

1. **Querying over a range**:
    ```cpp
    Query(left, right)
    ```
    - **Description**: Computes the result of the operation `op` over the range `[left, right)` (0-based indexing, `right` exclusive).
    - **Time Complexity**: $O(1)$
    - **Requirements**: `left` and `right` must satisfy `0 <= left <= right <= N`
    - **Example**:
        ```cpp
        int result = st.Query(1, 4);
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include "DataStructures/SparseTable/SparseTable.hpp"

int main() {
    // Initialize with a vector for minimum queries
    using T = int
    std::vector<T> arr = {4, 18, 24, 30, 60};

    auto op = [](T a, T b) -> T {
        return std::gcd(a, b);
    };

    SparseTable<T, op> st(arr.begin(), arr.end());

    // Perform a range query
    int gcd_qry = st.Query(1, 4); // 
    std::cout << "gcd over the range [1, 4): " << gcd_qry << '\n';
    // min_val = gcd(18, 24, 30) = 6

    // Another range query
    gcd_qry = st.Query(0, 5); // gcd of all elements
    std::cout << "minimum over the range [0, 5): " << gcd_qry << '\n';
    // min_val = min(4, 18, 24, 30, 60) = 2

    return 0;
}
```

## Notes

- The Sparse Table is designed for **static data** and does not support updates after initialization. For dynamic data, consider using a [Segment Tree](#more-info) instead.
- The operation `op` must be:
    - **associative**:
        ```cpp
        assert(op(op(a, b), c) == op(a, op(b, c))); // this must be true for all a, b and c
        ```
    - **Idempotent**:
        ```cpp
        assert(op(a, a) == a);  // this must be true for all a
        ```
    Examples: `min`, `max`, `gcd`, `lcm`
- **Time Complexity**: Initialization takes $O(N \log N)$, and queries are $O(1)$, multiplied by the time to perform the `op` function for type `T`.
- **Custom Types**: Ensure `op` is compatible with type `T`.
- **No Identity Element Required**: Unlike Segment Trees or Fenwick Trees, Sparse Tables do not require an identity element since they directly apply the operation over ranges.

## More Info

You can read more about how a Sparse Table works from [cp-algorithms](https://cp-algorithms.com/data_structures/sparse-table.html).
- This data structure is optimized for range queries on static data and is simpler and faster than a Segment Tree for idempotent operations.
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/101083) explains Sparse Tables and some optimizations.
  - Sparse Tables are rather niche. In fact, the *Disjoint Sparse Table* achieves the same time complexity and removes the assumption that the operation is imdepotent. However, the Sparse Table has a lower constant factor.