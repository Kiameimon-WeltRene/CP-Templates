#ifndef SPARSETABLE_HPP
#define SPARSETABLE_HPP

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
 * Sparse Table implementation for efficient range queries.
 * Supports operations like minimum, maximum, gcd, etc., as long as they are associative and idempotent.
 *
 * @tparam T The type of elements stored in the table.
 * @tparam op The operation function (e.g., min, max, gcd).
 */
template <typename T, auto op>
class SparseTable {
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
     * Constructs a SparseTable from a range of elements.
     *
     * @param start Iterator to the start of the range.
     * @param end Iterator to the end of the range.
     */
    template <Iterator Iter>
    explicit SparseTable(Iter start, Iter end);

    /**
     * Queries the range [left, right).
     *
     * @param left The left index (inclusive).
     * @param right The right index (exclusive).
     * @return The result of the operation over the range.
     */
    T Query(int left, int right);

private:
    int size_;                  // Number of elements in the table
    int LOG_;                   // Log2 of the size (for block size calculation)
    std::vector<std::vector<T>> data_; // The underlying sparse table data
};

// Include the implementation file for templates
#include "SparseTable.cpp"

#endif // SPARSETABLE_HPP
