# Segment Tree Template

A C++ template implementation of a Segment Tree that supports efficient range queries and point updates with customizable operations.

## Features

- Range Queries: Supports customizable operations (e.g., `sum`, `min`, `max`) over any range `[left, right)`
- Point Updates: Supports applying updates to individual elements using a custom update function
- Efficient Operations: $O(\log N)$ time complexity for both updates and queries
- Generic: Works with any type `T` for elements and `U` for updates, with customizable operation and update functions. For more info, see [this section](#notes)

## Usage

### Initialization

The Segment Tree can be initialized in two ways:

1. **From a range of elements**:
    ```cpp
    std::vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree<int, int, op, update> st(arr.begin(), arr.end(), identity);
    ```
    - **Time Complexity**: $O(N)$, where $N$ is the size of the range
    - **Space Complexity**: $O(N)$ for storing the data
    - **Requirements**: Input iterators (`start`, `end`), an identity element (e.g., `0` for sum), and compatible `op` and `update` functions

2. **With a specific size**:
    This fills the entire range with the identity (second argument)
    ```cpp
    SegmentTree<int, int, op, update> st(size, identity);
    ```
    - **Time Complexity**: $O(N)$, where $N$ is the size
    - **Space Complexity**: $O(N)$ for storing the data
    - **Requirements**: A positive integer size, an identity element, and compatible `op` and `update` functions

Specifically:
- `op`
    ```cpp
    auto op = [](A a, B b) -> T {
        // define your operation: eg gcd(a, b), max(a, b), +, -, *...
    };
    ```
    `A` and `B` must be `T` or `T&` and `op` must return the result of the operation (type `T`). For example, if the operation is addition, you should return `a + b`.
- `update`
    ```cpp
    auto update = [](C &curval, V &v) -> T {
        // define the update function: for example if you want to set curval to v, return v
    };
    ```
    C must be `T` or `T&`, `V` must be `U` or `U&` and `update` must return the updated value (type `T`).

### Public Methods

1. **Querying over a range**:
    ```cpp
    Query(left, right)
    ```
    - **Description**: Computes the result of the operation `op` over the range `[left, right)` (0-based indexing, `right` exclusive).
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `left` and `right` must satisfy `0 <= left <= right <= N`
    - **Example**:
        ```cpp
        int sum = st.Query(1, 4); // Sum of elements from index 1 to 3
        ```

2. **Updating an entry**:
    ```cpp
    Update(pos, value)
    ```
    - **Description**: Applies the `update` function to the element at position `pos` (0-based indexing) with the given `value` of type `U`.
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `pos` must be in range `[0, N)`, and `value` must be of type `U`
    - **Example**:
        ```cpp
        st.Update(2, 10); // Adds 10 to the element at index 2 (if update is addition)
        ```

3. **Accessing an element**:
    ```cpp
    operator[](index)
    ```
    - **Description**: Accesses the element at the given `index` (0-based indexing).
    - **Time Complexity**: $O(1)$
    - **Requirements**: `index` must be in range `[0, N)`
    - **Example**:
        ```cpp
        int value = st[2]; // Access element at index 2
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include "DataStructures/SegmentTree/SegmentTree.hpp"

int main() {
    // Initialize with a vector for max queries

    using T = int;
    using U = int;
    
    auto op = [](T a, T b) -> T {
        return std::min(a, b);
    };
    auto update = [](T curval, U v) -> T {
        return curval + v;
    };

    std::vector<T> arr = {4, 3, 5, 1, 2};
    SegmentTree<T, U, op, update> st(arr.begin(), arr.end(), INT_MAX); // INT_MAX is the identity because min(a, INT_MAX) = a for any int a

    // Perform a range query
    int minimum = st.Query(0, 3); // Minimum of elements at indices 0, 1, 2
    std::cout << "min over the range [0, 3): " << minimum << '\n';
    // minimum = min(4, 3, 5) = 3

    // Update an element
    st.Update(3, 10); // Add 10 to element at index 3
    // the array is now: [4, 3, 5, 11, 2]

    // Query again
    minimum = st.Query(2, 5); // Minimum of elements at indices 2, 3, 4
    std::cout << "min over the range [2, 5): " << minumum << '\n';
    // minimum = min(5, 11, 2) = 2

    // Access an element
    int value = st[2];
    std::cout << "value at index 2: " << value << '\n';
    // value = 5

    return 0;
}
```

## Notes

- The Segment Tree is highly customizable through the `op` and `update` functions:
  - `op` defines the operation for range queries (e.g. `+`, `-`, `*`, `gcd`, `lcm`, `min`, `max`, and many more).
  - `update` defines how updates are applied (e.g., incrementing, assigning, multiplying by a the update value and many more).
- The operation `op` must satisfy the following properties:
    - It is **associative**:
        ```cpp
        assert(op(op(a, b), c) == op(a, op(b, c))); // this must be true for all a, b and c
        ```
    - You have to provide an **identity element** `e` such that:
        ```cpp
        T a_op_e = a;
        a_op_e = op(a, e);
        assert(a == a_op_e); // this must be true for all a
        ```
        For example, `0` is the identity for addition, and `INT_MAX` is the identity for minimum.
    In Mathematics, this is known as a [monoid](https://en.wikipedia.org/wiki/Monoid).
- **Time Complexity**: All operations are $O(\log N)$ multiplied by the time to perform the `op` or `update` function for types `T` and `U`.
- **Identity Element**: You must provide the identity element during initialization (e.g., `0` for sum, `INT_MAX` for min).
- **Custom Types**: Ensure `op` and `update` are compatible with types `T` and `U`. For example:
    ```cpp
    struct LinearFunction {
        int m, c; // Represents y = mx + c
        LinearFunction(int m = 1, int c = 0) : m(m), c(c) {}
        // Compose two linear functions: f(g(x)) = m1*(m2*x + c2) + c1 = (m1*m2)*x + (m1*c2 + c1)
        LinearFunction compose(const LinearFunction& other) const {
            return LinearFunction {m * other.m, m * other.c + c};
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
    
    SegmentTree<LinearFunction, int, op, update> st(5, LinearFunction {1, 0});
    ```

## More Info

You can read more about how a Segment Tree works from [cp-algorithms](https://cp-algorithms.com/data_structures/segment_tree.html).
- This data structure is closely related to the *Fenwick Tree*. While the Fenwick Tree is more efficient for certain operations (e.g., prefix sums), the Segment Tree is more versatile, supporting a wider range of operations and update types.
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/18051) provides a description of how to implement the segment tree without recursion (and is what I used to implement the Segment Tree here).
  - There are many blogs on the Segment Tree on Codeforces. Segment Trees are extremely versatile: there are many variants of this data structure, ranging from basic modifications to complex generalizations.