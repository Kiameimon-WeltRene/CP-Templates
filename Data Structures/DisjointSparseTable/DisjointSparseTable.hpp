#ifndef DISJOINTSPARSETABLE_HPP
#define DISJOINTSPARSETABLE_HPP

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
 * Disjoint Sparse Table implementation for efficient range queries.
 * Supports operations like sum, product, xor, etc., as long as they are associative.
 *
 * @tparam T The type of elements stored in the table.
 * @tparam op The operation function (e.g., sum, product, xor).
 */
template <typename T, auto op>
class DisjointSparseTable {
    // Helper to check if `op` is callable with T or T&
    template <typename F, typename A, typename B>
    static constexpr bool IsOpCallable =
        std::is_invocable_r_v<T, F, A, B> || std::is_invocable_r_v<T, F, A&, B> ||
        std::is_invocable_r_v<T, F, A, B&> || std::is_invocable_r_v<T, F, A&, B&>;

    // Ensure `op` is valid
    static_assert(IsOpCallable<decltype(op), T, T>,
                  "`op` must be callable with T or T& as arguments");

public:
    /**
     * Constructs a DisjointSparseTable from a range of elements.
     *
     * @param start Iterator to the start of the range.
     * @param end Iterator to the end of the range.
     */
    template <Iterator Iter>
    explicit DisjointSparseTable(Iter start, Iter end);

    /**
     * Queries the range [left, right].
     *
     * @param left The left index (inclusive).
     * @param right The right index (inclusive).
     * @return The result of the operation over the range.
     */
    T Query(int left, int right);

private:
    int size_;                  // Number of elements in the table
    std::vector<std::vector<T>> data_; // The underlying disjoint sparse table data
};

// Include the implementation file for templates
#include "DisjointSparseTable.cpp"

#endif // DISJOINTSPARSETABLE_HPP
