#ifndef LAZYPROPSEGTREE_HPP
#define LAZYPROPSEGTREE_HPP

#include <algorithm>  // For std::copy
#include <cassert>    // For assert
#include <functional> // For std::invoke
#include <vector>     // For std::vector

/**
 * Lazy Propagation Segment Tree implementation.
 * Supports range updates and range queries with customizable operations.
 *
 * @tparam T The type of elements stored in the segment tree.
 * @tparam U The type of the update value.
 * @tparam op The operation function (e.g., sum, min, max).
 * @tparam updVal The function to update a value with a lazy update.
 * @tparam updLazy The function to combine two lazy updates.
 */
template <typename T, typename U, auto op, auto updVal, auto updLazy>
class LazyPropSegtree {
    // Helper to check if a function is callable with A or A&
    template <typename F, typename A>
    static constexpr bool IsCallable1 =
        std::is_invocable_r_v<A, F, A, A> || std::is_invocable_r_v<A, F, A&, A> ||
        std::is_invocable_r_v<A, F, A, A&> || std::is_invocable_r_v<A, F, A&, A&>;

    // Helper to check if a function is callable with T and U or T& and U&
    template <typename F, typename A, typename B>
    static constexpr bool IsCallable2 =
        std::is_invocable_r_v<T, F, A, B> || std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || std::is_invocable_r_v<T, F, A&, B&>;

    // Ensure `op`, `updVal`, and `updLazy` are valid
    static_assert(IsCallable1<decltype(op), T>,
                  "`op` must be callable with T or T& as arguments");
    static_assert(IsCallable2<decltype(updVal), T, U>,
                  "`updVal` must be callable with T and U or T& and U& as arguments");
    static_assert(IsCallable1<decltype(updLazy), U>,
                  "`updLazy` must be callable with U or U& as arguments");

public:
    /**
     * Constructs a LazyPropSegtree from a range of elements.
     *
     * @param start Iterator to the start of the range.
     * @param end Iterator to the end of the range.
     * @param identityOp The identity element for the operation (e.g., 0 for sum, INF for min).
     * @param identityUpdate The identity element for the lazy update.
     */
    explicit LazyPropSegtree(auto start, auto end, T identityOp, U identityUpdate);

    /**
     * Constructs a LazyPropSegtree with a given size and identity elements.
     *
     * @param size The number of elements in the tree.
     * @param identityOp The identity element for the operation.
     * @param identityUpdate The identity element for the lazy update.
     */
    explicit LazyPropSegtree(int size, T identityOp, U identityUpdate);

    /**
     * Queries the range [left, right).
     *
     * @param left The left index (inclusive).
     * @param right The right index (exclusive).
     * @return The result of the operation over the range.
     */
    T Query(int left, int right);

    /**
     * Updates the range [left, right) with a value.
     *
     * @param left The left index (inclusive).
     * @param right The right index (exclusive).
     * @param value The value to apply to the range.
     */
    void Update(int left, int right, U value);

private:
    int size_;              // Number of elements in the tree
    int LOG_;               // Log2 of the size (for propagation)
    T identityOp_;          // Identity element for the operation
    U identityUpdate_;      // Identity element for the lazy update
    std::vector<T> tree_;   // The underlying tree structure
    std::vector<U> lazy_;   // Lazy propagation values

    /**
     * Propagates lazy updates down the tree.
     *
     * @param pos The position to propagate from.
     */
    void Propagate(int pos);

    /**
     * Recalculates the tree values after an update.
     *
     * @param pos The position to start recalculating from.
     */
    void recalculate_after_update(int pos);
};

// Include the implementation file for templates
#include "LazyPropSegtree.cpp"

#endif // LAZYPROPSEGTREE_HPP
