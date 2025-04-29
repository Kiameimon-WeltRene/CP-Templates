# Lazy Propagation Segment Tree Template

A C++ template implementation of a Lazy Propagation Segment Tree that supports efficient range queries and range updates with customizable operations.

## Features

- Range Queries: Supports customizable operations (e.g., `sum`, `min`, `max`) over any range `[left, right)`
- Range Updates: Supports applying updates to a range of elements using a custom update function
- Efficient Operations: $O(\log N)$ time complexity for both queries and updates
- Generic: Works with any type `T` for elements and `U` for updates, with customizable operation, value update, and lazy update functions. For more info, see [this section](#notes)

## Usage

### Initialization

The Lazy Propagation Segment Tree can be initialized in two ways:

1. **From a range of elements**:
    ```cpp
    std::vector<int> arr = {1, 2, 3, 4, 5};
    LazyPropSegtree<int, int, op, updVal, updLazy> st(arr.begin(), arr.end(), identityOp, identityUpdate);
    ```
    - **Time Complexity**: $O(N)$, where $N$ is the size of the range
    - **Space Complexity**: $O(N)$ for the tree and lazy arrays
    - **Requirements**: Input iterators (`start`, `end`), identity element for the operation (e.g., `0` for sum), identity element for the lazy update (e.g., `0` for addition), and compatible `op`, `updVal`, and `updLazy` functions

2. **With a specific size**:
    This fills the entire range with the operation identity (second argument)
    ```cpp
    LazyPropSegtree<int, int, op, updVal, updLazy> st(size, identityOp, identityUpdate);
    ```
    - **Time Complexity**: $O(N)$, where $N$ is the size
    - **Space Complexity**: $O(N)$ for storing the data and lazy tags
    - **Requirements**: A positive integer size, identity elements for the operation and lazy update, and compatible `op`, `updVal`, and `updLazy` functions

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
    auto updLazy = [](W curval, Y v) -> U {
        // define the lazy update function: return the combined update
    };
    ```
    `W` and `Y` must be `U` or `U&`, and `updLazy` must return the combined lazy update (type `U`). For example, if `updVal` is addition, updating by `curval` then `v` is equivalent to updating by `curval + v`, so return `curval + v`.

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

2. **Updating a range**:
    ```cpp
    Update(left, right, value)
    ```
    - **Description**: Applies the `updVal` function to all elements in the range `[left, right)` (0-based indexing, `right` exclusive) with the given `value` of type `U`, using `updLazy` for lazy propagation.
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `left` and `right` must satisfy `0 <= left <= right <= N`, and `value` must be of type `U`
    - **Example**:
        ```cpp
        st.Update(1, 4, 10); // Add 10 to elements from index 1 to 3
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "DataStructures/LazyPropSegtree/LazyPropSegtree.hpp"


int main() {
    using T = int;
    using U = int;

    // Initialize with a vector for range min queries and addition updates
    std::vector<T> arr = {2, 5, 3, 4, 1};

    auto op = [](T a, T b) -> T {
        return std::min(a, b);
    };
    auto updVal = [](T curval, U v) -> T {
        return curval + v;
    };
    auto updLazy = [](U curval, U v) -> U {
        return curval + v;
    };

    LazyPropSegtree<T, U, op, updVal, updLazy> st(arr.begin(), arr.end(), INT_MAX, 0);

    // Perform a range query
    int min_val = st.Query(1, 4); // Minimum of elements at indices 1, 2, 3
    std::cout << "minimum over the range [1, 4): " << min_val << '\n';
    // min_val = min(5, 3, 4) = 3

    // Update a range
    st.Update(1, 4, 10); // Add 10 to elements at indices 1, 2, 3
    // the array is now: [2, 15, 13, 14, 1]

    // Query again
    min_val = st.Query(1, 4); // Now min_val = min(15, 13, 14) = 13
    std::cout << "minimum over the range [1, 4) after update: " << min_val << '\n';

    // Query a single element
    min_val = st.Query(2, 3); // Value at index 2
    std::cout << "value at index 2: " << min_val << '\n';
    // value = 13

    return 0;
}
```

## Notes

- The Lazy Propagation Segment Tree is highly customizable through the `op`, `updVal`, and `updLazy` functions:
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
        assert(updLazy(updLazy(a, b), c) == updLazy(a, updLazy(b, c))); // this must be true for all a, b, c
        ```
    - You have to provide an **identity element** `e` such that:
        ```cpp
        U u, e;
        U u_updLazy_e = updLazy(u, e);
        assert(u == u_updLazy_e); // this must be true for all u
        ```
        For example, `0` is the identity for addition updates.
- **Lazy Propagation Requirement**: The `updVal` function must allow the new value of any range or node to be determined based solely on the current value and the update value. For example, adding a value to a range or assigning a new value to a range are valid, as the result depends only on the current state and the update.
- **Time Complexity**: All operations (queries and updates) are $O(\log N)$ multiplied by the time to perform the `op`, `updVal`, or `updLazy` functions for types `T` and `U`.
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
    auto updLazy = [](int curval, int v) -> int {
        return curval + v;
    };

    LazyPropSegtree<LinearFunction, int, op, updVal, updLazy> st(5, LinearFunction{1, 0}, 0);
    ```


## More Info

You can read more about how a Lazy Propagation Segment Tree works from [cp-algorithms](https://cp-algorithms.com/data_structures/segment_tree.html#lazy-propagation).
- This data structure extends the standard Segment Tree by supporting efficient range updates, making it suitable for problems requiring both range queries and updates, such as updating intervals in an array or computing range statistics.
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/112890) discusses an alternate way to do lazy propagation, and also explains about what exactly is required for this data structure to support range updates.
  - [This blog](https://codeforces.com/blog/entry/18051) provides a description of how to implement this data structure without recursion (and is what I used to implement the Segment Tree here).