#ifndef SPARSETABLE_CPP
#define SPARSETABLE_CPP

#include "SparseTable.hpp"

// Constructor from a range of elements
template <typename T, auto op>
template <Iterator Iter>
SparseTable<T, op>::SparseTable(Iter start, Iter end)
    : size_(std::distance(start, end)), LOG_(32 - __builtin_clz(size_)),
      data_(LOG_, std::vector<T>(size_)) {
    // Copy the input elements into the first level of the sparse table
    std::copy(start, end, data_[0].begin());

    // Build the sparse table
    for (int i = 0; i < LOG_ - 1; ++i) {
        for (int j = 0; j + (1 << i) < size_; ++j) {
            data_[i + 1][j] = op(data_[i][j], data_[i][j + (1 << i)]);
        }
    }
}

// Query function
template <typename T, auto op>
T SparseTable<T, op>::Query(int left, int right) {
    int block = 31 - __builtin_clz(right - left);       // Calculate the largest power of 2 <= (right - left)
    return op(data_[block][left], data_[block][right - (1 << block)]);
}

#endif // SPARSETABLE_CPP
