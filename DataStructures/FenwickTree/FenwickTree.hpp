#ifndef FENWICKTREE_HPP
#define FENWICKTREE_HPP

#include <vector>     // For std::vector
#include <functional> // For std::invoke

// Concept to ensure the type is an iterator
template <typename Iter>
concept Iterator = requires(Iter it) {
    typename std::iterator_traits<Iter>::iterator_category;
};

// Concept to ensure += and -= are defined
template <typename T>
concept HasOp = requires(T a, T b) {
    { a += b } -> std::same_as<T&>; 
    { a -= b } -> std::same_as<T&>;
};

/**
 * Fenwick Tree (also known as a Binary Indexed Tree) implementation.
 * Supports efficient range queries and point updates.
 *
 * @tparam T The type of elements stored in the tree. Must support addition (+) and subtraction (-).
 */
template <HasOp T>
class FenwickTree {
public:
    /**
     * Constructs a FenwickTree from a range of elements.
     *
     * @param start Iterator to the start of the range.
     * @param end Iterator to the end of the range.
     * @param identity The identity element for the operation (e.g., 0 for sum).
     */
    template <Iterator Iter>
    explicit FenwickTree(Iter start, Iter end, T identity);

    /**
     * Constructs a FenwickTree with a given size and identity element.
     *
     * @param size The number of elements in the tree.
     * @param identity The identity element for the operation.
     */
    explicit FenwickTree(int size, T identity);

    /**
     * Updates the element at the given position.
     *
     * @param pos The position to update.
     * @param value The value to add to the element at `pos`.
     */
    void Update(int pos, T value);

    /**
     * Queries the range [left, right).
     *
     * @param left The left index (inclusive).
     * @param right The right index (exclusive).
     * @return The result of the operation over the range.
     */
    T Query(int left, int right);

private:
    int size_;            // Number of elements in the tree + 1 (for 1-based indexing)
    T identity_;          // Identity element for the operation
    std::vector<T> data_; // The underlying data structure

    /**
     * Computes the least significant bit of `x`.
     *
     * @param x The input value.
     * @return The least significant bit of `x`.
     */
    inline int least_significant_bit(int x) const {
        return x & -x;
    }

    /**
     * Computes the prefix sum up to `pos`.
     *
     * @param pos The position to compute the prefix sum up to.
     * @return The prefix sum.
     */
    T sum(int pos);
};

// Include the implementation file for templates
#include "FenwickTree.cpp"

#endif // FENWICKTREE_HPP
