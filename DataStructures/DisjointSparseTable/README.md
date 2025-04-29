# Disjoint Sparse Table Template

A C++ template implementation of a Disjoint Sparse Table that supports efficient range queries for associative operations.

## Features

- Range Queries: Supports customizable operations (e.g., `sum`, `product`, `xor`) over any range `[left, right]`
- Efficient Queries: $O(1)$ time complexity for queries after $O(N \log N)$ preprocessing
- Generic: Works with any type `T` and operation `op` that is associative. For more info, see [this section](#notes)
- Static Structure: Optimized for static data with no updates

## Usage

### Initialization

The Disjoint Sparse Table can be initialized from a range of elements:

```cpp
std::vector<int> arr = {1, 2, 3, 4, 5};
DisjointSparseTable<int, op> dst(arr.begin(), arr.end());
```

- **Time Complexity**: $O(N \log N)$, where $N$ is the size of the range
- **Space Complexity**: $O(N \log N)$ for storing the table
- **Requirements**: Input iterators (`start`, `end`) and a valid operation `op`
Specifically:
- `op`
    ```cpp
    auto op = [](A a, B b) -> T {
        // define your operation: eg gcd(a, b), max(a, b), +, -, *...
    };
    ```
    `A` and `B` must be `T` or `T&` and `op` must return the result of the operation (type `T`). For example, if the operation is addition, you should return `a + b`.

### Public Methods

1. **Querying over a range**:
    ```cpp
    Query(left, right)
    ```
    - **Description**: Computes the result of the operation `op` over the range `[left, right]` (0-based indexing, both `left` and `right` inclusive).
    - **Time Complexity**: $O(1)$
    - **Requirements**: `left` and `right` must satisfy `0 <= left <= right < N`
    - **Example**:
        ```cpp
        int result = dst.Query(1, 3); // query operation from index 1 to 3
        ```

## Basic Usage

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "DataStructures/DisjointSparsetable/DisjointSparseTable.hpp"

int main() {
    // Initialize with a vector for sum queries
    using T = int;
    std::vector<T> arr = {1, 2, 3, 4, 5};
    
    auto op = [](T a, T b) -> T {
        return a * b;
    };
    DisjointSparseTable<T, op> dst(arr.begin(), arr.end());

    // Perform a range query
    int product = dst.Query(1, 3); // Product of elements at indices 1, 2, 3
    std::cout << "product over the range [1, 3]: " << product << '\n';
    // product = 2 * 3 * 4 = 24

    // Another range query
    product = dst.Query(4, 4);
    std::cout << "product over the range [4, 4]: " << product << '\n';
    // product = 5

    return 0;
}
```

## Notes

- The Disjoint Sparse Table is designed for **static data** and does not support updates after initialization. For dynamic data, consider using a *Segment Tree* or *Fenwick Tree*.
- The operation `op` must be **associative**:
    ```cpp
        assert(op(op(a, b), c) == op(a, op(b, c))); // this must be true for all a, b and c
    ```
    Examples of valid operations include addition, multiplication, bitwise operations, function composition and matrix multiplication.
- **Time Complexity**: Initialization takes $O(N \log N)$, and queries are $O(1)$ multiplied by the time to perform the `op` function for type `T`.
- **Custom Types**: Ensure `op` is compatible with type `T`. For example, for a custom type:
    ```cpp
    // 2x2 Matrix struct
    struct Matrix {
        int m[2][2];
        Matrix() {
            m[0][0] = 0; m[0][1] = 0;
            m[1][0] = 0; m[1][1] = 0;
        }

        // Matrix multiplication
        Matrix& operator*(const Matrix& other) const {
            Matrix result();
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        result.m[i][j] += m[i][k] * other.m[k][j];
                    }
                }
            }
            return result;
        }
    };

    // Define the operation for matrix multiplication
    auto op = [](Matrix a, Matrix b) -> Matrix {
        return a * b;
    };

    DisjointSparseTable<Matrix, op> dst(matrices.begin(), matrices.end());
    // "matrices" is a vector of "Matrix"s
    ```
- **No Identity Element Required**: Unlike Segment Trees or Fenwick Trees, Disjoint Sparse Tables do not require an identity element since they directly apply the operation over ranges.
- **Comparison with Sparse Table**: Unlike the standard Sparse Table, which requires the operation to be idempotent (e.g., `min`, `max`), the Disjoint Sparse Table only requires associativity, making it suitable for operations like sum or product.

## More Info

You can read more about how a Disjoint Sparse Table works from [cp-algorithms](https://cp-algorithms.com/data_structures/disjoint_sparse_table.html).
- This data structure is optimized for range queries on static data and offers similar query performance to the standard Sparse Table but supports a broader range of operations (e.g., sum, product) due to not requiring idempotence.
- For further reading on the topic:
  - [This blog](https://codeforces.com/blog/entry/87940) discusses the Disjoint Sparse Table and its applications in competitive programming.
  - [This blog](https://codeforces.com/blog/entry/57046) discusses a similar data structure.