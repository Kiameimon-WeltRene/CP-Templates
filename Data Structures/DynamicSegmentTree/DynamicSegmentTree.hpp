#ifndef DYNAMICSEGMENTTREE_HPP
#define DYNAMICSEGMENTTREE_HPP

#include <algorithm>
#include <functional>

/**
 * Dynamic Segment Tree implementation with lazy propagation.
 * Supports range updates and range queries with customizable operations.
 * 
 * Features:
 * - Handles large ranges efficiently (only creates nodes as needed)
 * - Supports range updates and range queries in O(log N) time
 * - Includes self-cleaning destructor to prevent memory leaks
 *
 * @tparam T The type of values stored in the tree
 * @tparam U The type of lazy update values
 * @tparam op The associative operation function (e.g., sum, min, max)
 * @tparam updVal Function to update a value with a lazy update
 * @tparam updLazy Function to combine lazy updates (takes node range into account)
 */
template <typename T, typename U, auto op, auto updVal, auto updLazy>
class DynamicSegmentTree {
    using ll = long long;

    // Type trait to check if operation is valid
    template <typename F, typename A, typename B>
    static constexpr bool IsBinaryOperation =
        std::is_invocable_r_v<T, F, A, B> || 
        std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || 
        std::is_invocable_r_v<T, F, A&, B&>;

    // Type trait to check if lazy update is valid
    template <typename F, typename A, typename B, typename C, typename D, typename E>
    static constexpr bool IsLazyOperation =
        std::is_invocable_v<F, A&, B&, C, D&, E&>;

    // Compile-time validation of operation signatures
    static_assert(IsBinaryOperation<decltype(op), T, T>,
                "Operation must be callable with (T, T) and return T");
    static_assert(IsBinaryOperation<decltype(updVal), T, U>,
                "Value update must be callable with (T, U) and return T");
    static_assert(IsLazyOperation<decltype(updLazy), U, T, U, ll, ll>,
                "Lazy update must be callable with (U&, T&, U, ll&, ll&)");

public:
    /**
     * Constructs a segment tree covering [start, end]
     * @param start First index in range
     * @param end Last index in range
     * @param identityOp Identity element for the operation
     * @param identityUpdate Identity element for lazy updates
     */
    DynamicSegmentTree(ll start, ll end, T identityOp, U identityUpdate);

    /**
     * Destructor - automatically cleans up all allocated nodes
     */
    ~DynamicSegmentTree();

    /**
     * Range query operation
     * @param left Start of query range (inclusive)
     * @param right End of query range (inclusive)
     * @return Result of applying operation over [left, right]
     */
    T Query(ll left, ll right);

    /**
     * Range update operation
     * @param left Start of update range (inclusive)
     * @param right End of update range (inclusive)
     * @param value Update value to apply
     */
    void Update(ll left, ll right, U value);

private:
    // Node data
    ll start_;          // Start of range covered by this node
    ll end_;            // End of range covered by this node
    ll middle_;         // Midpoint (start + end)/2
    T identityOp_;      // Identity element for the operation
    U identityUpdate_;  // Identity element for lazy updates
    T value_;           // Current node value
    U lazy_;            // Pending lazy update
    DynamicSegmentTree* left_;   // Left child
    DynamicSegmentTree* right_;  // Right child

    /**
     * Propagates pending lazy updates to children
     */
    void Propagate();

    /**
     * Recursively deletes all child nodes
     */
    void Clear();
};

#include "DynamicSegmentTree.cpp"

#endif // DYNAMICSEGMENTTREE_HPP
