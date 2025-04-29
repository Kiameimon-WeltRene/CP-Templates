#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

#include <algorithm>  // For std::copy
#include <cassert>    // For assert
#include <functional> // For std::invoke
#include <vector>     // For std::vector

// Concept to ensure the type is an iterator
template <typename Iter>
concept Iterator = requires(Iter it) {
    typename std::iterator_traits<Iter>::iterator_category;
};

/**
 * Segment Tree implementation with customizable operation and update functions.
 *
 * @tparam T The type of elements stored in the segment tree.
 * @tparam U The type of the update value.
 * @tparam op The operation function (e.g., sum, min, max).
 * @tparam update The update function to apply to elements.
 */
template <typename T, typename U, auto op, auto update>
class SegmentTree {
    // Helper to check if `op` is callable with T or T&
    template <typename F, typename A, typename B>
    static constexpr bool IsOpCallable =
        std::is_invocable_r_v<T, F, A, B> || std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || std::is_invocable_r_v<T, F, A&, B&>;

    // Helper to check if `update` is callable with T and U or T& and U&
    template <typename F, typename A, typename B>
    static constexpr bool IsUpdateCallable =
        std::is_invocable_r_v<T, F, A, B> || std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || std::is_invocable_r_v<T, F, A&, B&>;

    // Ensure `op` and `update` are valid
    static_assert(IsOpCallable<decltype(op), T, T>,
                  "`op` must be callable with T or T& as arguments");
    static_assert(IsUpdateCallable<decltype(update), T, U>,
                  "`update` must be callable with T and U or T& and U& as arguments");

public:
    /**
     * Constructs a SegmentTree from a range of elements.
     *
     * @param start Iterator to the start of the range.
     * @param end Iterator to the end of the range.
     * @param identity The identity element for the operation (e.g., 0 for sum, INF for min).
     */
    template <Iterator Iter>
    explicit SegmentTree(Iter start, Iter end, T identity);
    /**
     * Constructs a SegmentTree with a given size and identity element.
     * All entries are initially set to the identity.
     * 
     * @param size The number of elements in the tree.
     * @param identity The identity element for the operation.
     */
    explicit SegmentTree(int size, T identity);

    /**
     * Queries the range [left, right).
     *
     * @param left The left index (inclusive).
     * @param right The right index (exclusive).
     * @return The result of the operation over the range.
     */
    T Query(int left, int right);

    /**
     * Updates the element at the given position.
     *
     * @param pos The position to update.
     * @param value The value to apply.
     */
    void Update(int pos, U value);

    /**
     * Accesses the element at the given index.
     *
     * @param index The index to access.
     * @return The element at the index.
     */
    const T& operator[](int index) const;

private:
    int size_;            // Number of elements in the tree
    T identity_;          // Identity element for the operation
    std::vector<T> tree_; // The underlying tree structure
};

// Include the implementation file for templates
#include "SegmentTree.cpp"

#endif // SEGMENTTREE_HPP
