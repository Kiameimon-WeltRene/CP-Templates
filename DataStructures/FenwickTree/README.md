# Fenwick Tree (Binary Indexed Tree) Template

A C++ template implementation of a Fenwick Tree (Binary Indexed Tree) that supports efficient range queries and point updates.

## Features

- Range Queries: Supports sum queries over any range `[left, right)`
- Point Updates: Supports adding values to individual elements
- Efficient Operations: $O(\log N)$ time complexity for both updates and queries
- Generic: Works with any type that supports `+=` and `-=` operations. For more info, see [this section](#notes)

## Usage

### Initialization
The Fenwick Tree can be initialized in two ways:
1. **From a range of elements**:
    ```cpp
    std::vector<int> arr = {1, 2, 3, 4, 5};
    FenwickTree<int> fwt(arr.begin(), arr.end(), 0);
    ```
    - **Time Complexity**: $O(N \log N)$, where $N$ is the size of the range
    - **Space Complexity**: $O(N)$
    - **Requirements**: Input iterators (start, end) and an identity element (e.g., 0 for summation)
2. **With a specific size**:
    This fills the entire range with the identity (second argument)
    ```cpp
    FenwickTree<int> fwt(5, 0);
    ```
    - **Time Complexity**: $O(N)$, where $N$ is the size
    - **Space Complexity**: $O(N)$ for storing the data
    - **Requirements**: A positive integer size and an identity element

### Public Methods
1. **Updating an entry**:
    ```cpp
    Update(pos, value)
    ```
    - **Description**: Adds `value` to the element at position `pos` (0-based indexing).
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `pos` must be in range `[0, N)`, and value must be of type `T`
    - **Example**:
        ```cpp
        fwt.Update(2, 10); // Adds 10 to the element at index 2
        ```

2. **Querying over a range**:
    ```cpp
    Query(left, right)
    ```
    - **Description**: Computes the sum (or operation) over the range `[left, right)` (0-based indexing, `right` exclusive).
    - **Time Complexity**: $O(\log N)$
    - **Requirements**: `left` and `right` must satisfy `0 <= left <= right <= size`
    - **Example**:
        ```cpp
        int sum = fwt.Query(1, 4); // Sum of elements from index 1 to 3
        ```


## Basic Usage
```cpp
#include <iostream>
#include <vector>
#include "DataStructures/FenwickTree/FenwickTree.hpp"

int main() {
    // Initialize with a vector
    std::vector<int> arr = {1, 2, 3, 4, 5};
    FenwickTree<int> fwt(arr.begin(), arr.end(), 0);

    // Perform a range query
    int sum = fwt.Query(1, 4); // Sum of elements at indices 1, 2, 3
    std::cout << "sum over the range [1, 4): " << sum << '\n';
    // sum = 2 + 3 + 4 = 9

    // Update an element
    fwt.Update(2, 10); // Add 10 to element at index 2
    // the array is now: [1, 2, 13, 4, 5]

    // Query again
    sum = fwt.Query(2, 4); // Now sum = 13 + 4 = 17
    std::cout << "sum over the range [2, 4): " << sum << '\n';

    return 0;
}
```

## Notes
- The Fenwick Tree is generic and works with any type `T` that forms an [abelian group](https://en.wikipedia.org/wiki/Abelian_group) under the operation defined by `+=` and `-=`. This means:
    - The `+` operation is **commutative**:
        ```cpp
        T a_plus_b = a, b_plus_a = b;
        a_plus_b += b;
        b_plus_a += a;
        assert(a_plus_b == b_plus_a);  // this must be true for all a, b
        ```
    - You have to provide an **identity element** `e` such that:
        ```cpp
        T a_plus_e = a;
        a_plus_e += e;
        assert(a == a_plus_e);  // this must be true for all a
        ```
        For example, `0` is the identity element for addition, and `1` is the identity element for multiplication.
    -  There is a `-` operation that does the opposite of `+` (called the **inverse operation**):
        ```cpp
        T value = a;
        value += b;
        value -= b;  // -= b "undoes" the += b
        assert(value == a);  // this must be true for all a, b
        ```
        For example, if you overloaded `+` to be multiplication, then `-` (the "inverse operation") would be `/`.
- **Time Complexity**: All operations are $O(\log N)$ multiplied by the time to perform the operation and assignment for type `T`.
- **Identity Element**: You must provide the identity element during initialization (e.g., `0` for sum, `1` for product)
- **Custom Types**: Ensure += and -= are properly defined for custom types. For example:
    ```cpp
    struct XorInt {
        int value;
        XorInt& operator+=(const XorInt& other) {
            value ^= other.value; return *this;
        }
        XorInt& operator-=(const XorInt& other) {
            value ^= other.value; return *this;
        }
    };
    ```
    Notice how `a ^ b ^ b == a` for any integers `a` and `b`, therefore `^` is its own inverse operation. The identity element for `^` is also `0`.

## More Info
You can read more about how a Fenwick Tree works from [cp-algorithms](https://cp-algorithms.com/data_structures/fenwick.html).
- This data structure is closely linked to the *Segment Tree*, and in fact, the Segment Tree can perform every operation that the Fenwick Tree can, and more. However, the Fenwick Tree typically outperforms it both in terms of memory and speed.
- For further reading on the topic:
    - [This blog](https://codeforces.com/blog/entry/78564) describes an approach to handle path sum queries on a tree with a Fenwick Tree
    - [This blog](https://codeforces.com/blog/entry/99895) discusses some generalizations of the Fenwick Tree