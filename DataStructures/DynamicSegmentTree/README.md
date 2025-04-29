# Dynamic Segment Tree Template

A C++ template implementation of a Dynamic Segment Tree with lazy propagation that supports efficient range queries and range updates with customizable operations. Unlike traditional segment trees, it dynamically allocates nodes only as needed, making it suitable for large index ranges (e.g. up to `1e18`).

## Features

- Range Queries: Supports customizable operations (e.g., `sum`, `min`, `max`) over any range `[left, right]`
- Range Updates: Supports applying updates to a range of elements using a custom update function
- Efficient Operations: $O(\log N)$ time complexity for both queries and updates, where $N$ is the range size
- Generic: Works with any type `T` for elements and `U` for updates, with customizable operation, value update, and lazy update functions. For more info, see [this section](#notes)
- Dynamic Allocation: Only creates nodes as needed, ideal for sparse or large ranges
- Memory Management: Includes a self-cleaning destructor to prevent memory leaks

## Usage

### Initialization

The Dynamic Segment Tree can be initialized with a specified range:

```cpp
DynamicSegmentTree<int, int, op, updVal, updLazy> st(start, end, identityOp, identityUpdate);
```

- **Time Complexity**: $O(1)$ initially (nodes are created dynamically during operations)
- **Space Complexity**: $O(\log N)$ per operation, where $N$ is the range size, as nodes are allocated only when needed
- **Requirements**: A range `[start, end]` (inclusive, using `long long`), identity element for the operation (e.g., `0` for sum), identity element for the lazy update (e.g., `0` for addition), and compatible `op`, `updVal`, and `updLazy` functions

Specifically:
- `op`
    ```cpp
    auto op = [](A a, B b) -> T {
        // define your operation: eg gcd(a, b), max(a, b), +, -, *...
    };
    ```
    `A` and `B` must be `T` or `T&`, and `op` must return the result of the operation (type `T`). For example, if the operation is addition, you should return `a + b`.
- `updVal`
    ```cpp
    auto updVal = [](C curval, V v) -> T {
        // define the update function: for example, if you want to add v to curval, return curval + v
    };
    ```
    `C` must be `T` or `T&`, `V` must be `U` or `U&`, and `updVal` must return the updated value (type `T`).
- `updLazy`
    ```cpp
    auto updLazy = [](W& curval, X& val, Y v, long long& left, long long& right) {
        // define the lazy update function: update curval to combine with v
    };
    ```
    `W` must be `U&`, `X` must be `T&`, `Y` must be `U`, and `updLazy` must update `curval` to represent the combined lazy update. For example, if `updVal` is addition, updating by `curval` then `v` is equivalent to updating by `curval + v`, so set `curval += v`.

### Public Methods

1. **Querying over a range**:
    ```cpp
    Query(left, right)
    ```
    - **Description**: Computes the result of the operation `op` over the range `[left, right]` (inclusive).
    - **Time Complexity**: $O(\log N)$, where $N$ is the range size
    - **Requirements**: `left` and `right` must satisfy `start <= left <= right <= end`
    - **Example**:
        ```cpp
        int sum = st.Query(1, 3); // Sum of elements from index 1 to 3
        ```

2. **Updating a range**:
    ```cpp
    Update(left, right, value)
    ```
    - **Description**: Applies the `updVal` function to all elements in the range `[left, right]` (inclusive) with the given `value` of type `U`, using `updLazy` for lazy propagation.
    - **Time Complexity**: $O(\log N)$, where $N$ is the range size
    - **Requirements**: `left` and `right` must satisfy `start <= left <= right <= end`, and `value` must be of type `U`
    - **Example**:
        ```cpp
        st.Update(1, 3, 10); // Add 10 to elements from index 1 to 3
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "DataStructures/DynamicSegmentTree/DynamicSegmentTree.hpp"

int main() {
    // Initialize for sum queries and addition updates over range [0, 4]
    auto op = [](int a, int b) { return a + b; };
    auto updVal = [](int curval, int v) { return curval + v; };
    auto updLazy = [](int& curval, int& val, int v, long long& left, long long& right) { curval += v; };
    DynamicSegmentTree<int, int, op, updVal, updLazy> st(0, 4, 0, 0);

    // Update individual elements to match initial array [1, 2, 3, 4, 5]
    st.Update(0, 0, 1);
    st.Update(1, 1, 2);
    st.Update(2, 2, 3);
    st.Update(3, 3, 4);
    st.Update(4, 4, 5);

    // Perform a range query
    int sum = st.Query(1, 3); // Sum of elements at indices 1, 2, 3
    std::cout << "sum over the range [1, 3]: " << sum << '\n';
    // sum = 2 + 3 + 4 = 9

    // Update a range
    st.Update(1, 3, 10); // Add 10 to elements at indices 1, 2, 3
    // the array is now: [1, 12, 13, 14, 5]

    // Query again
    sum = st.Query(1, 3); // Now sum = 12 + 13 + 14 = 39
    std::cout << "sum over the range [1, 3] after update: " << sum << '\n';

    // Query a single element
    sum = st.Query(2, 2); // Value at index 2
    std::cout << "value at index 2: " << sum << '\n';
    // value = 13

    return 0;
}
```

## Notes

- The Dynamic Segment Tree is highly customizable through the `op`, `updVal`, and `updLazy` functions:
  - `op` defines the operation for range queries (e.g., `+`, `-`, `*`, `gcd`, `lcm`, `min`, `max`, and many more).
  - `updVal` defines how updates are applied to tree values (e.g., incrementing, assigning, multiplying by the update value, and many more).
  - `updLazy` defines how lazy updates are combined (e.g., accumulating additions, composing assignments, and many more).
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
- The lazy update operation `updLazy` must also satisfy the following properties:
    - It is **associative**:
        ```cpp
        assert(updLazy(updLazy(a, b, val1, left1, right1), c, val2, left2, right2) == 
               updLazy(a, updLazy(b, c, val2, left2, right2), val1, left1, right1)); // this must be true for all a, b, c
        ```
    - You have to provide an **identity element** `e` such that:
        ```cpp
        U u, e;
        U u_updLazy_e = updLazy(u, e, val, left, right);
        assert(u == u_updLazy_e); // this must be true for all u
        ```
        For example, `0` is the identity for addition updates.
- **Lazy Propagation Requirement**: The `updVal` function must allow the new value of any range or node to be determined based solely on the current value and the update value. For example, adding a value to a range or assigning a new value to a range are valid, as the result depends only on the current state and the update.
- **Time Complexity**: All operations (queries and updates) are $O(\log N)$ multiplied by the time to perform the `op`, `updVal`, or `updLazy` functions for types `T` and `U`, where $N$ is the range size.
- **Identity Elements**: You must provide identity elements for both the operation (e.g., `0` for sum) and the lazy update (e.g., `0` for addition) during initialization.
- **Custom Types**: Ensure `op`, `updVal`, and `updLazy` are compatible with types `T` and `U`. For example:
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
    auto updVal = [](LinearFunction curval, int v) -> LinearFunction {
        curval.m += v;
        return curval;
    };

    // Define the lazy update function: accumulates additions to the slope
    auto updLazy = [](int& curval, LinearFunction& val, int v, long long& left, long long& right) {
        curval += v;
    };

    DynamicSegmentTree<LinearFunction, int, op, updVal, updLazy> st(0, 1000000, LinearFunction{1, 0}, 0);
    ```

## More Info

You can read more about how a Dynamic Segment Tree works from [cp-algorithms](https://cp-algorithms.com/data_structures/segment_tree.html#dynamic-segment-tree).
- This data structure is particularly useful for problems with large index ranges (e.g., up to $10^9$) where a static Segment Tree would be memory-inefficient. It dynamically creates nodes only when needed, making it memory-efficient for sparse updates and queries.
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/112890) discusses dynamic segment trees and their applications, including lazy propagation techniques.
  - [This blog](https://codeforces.com/blog/entry/83170) Discusses a technique on dynamic Segment Trees.