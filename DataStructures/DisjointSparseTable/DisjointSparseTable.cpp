#ifndef DISJOINTSPARSETABLE_CPP
#define DISJOINTSPARSETABLE_CPP

#include "DisjointSparseTable.hpp"

// Constructor from a range of elements
template <typename T, auto op>
template <Iterator Iter>
DisjointSparseTable<T, op>::DisjointSparseTable(Iter start, Iter end)
    : size_(std::distance(start, end)),
      data_(33 - __builtin_clz(size_), std::vector<T>(size_)) {
    // Copy the input elements into the first layer of the disjoint sparse table
    std::copy(start, end, data_[0].begin());

    int layer = 0, h = 1; // h is the current block size
    while (h < size_) {
        int left = 0, right = std::min(h, size_) - 1;

        // Process each block in the current layer
        while (left < size_) {
            // Propagate values to the left within the block
            for (int x = right - 1; x >= left; --x) {
                data_[layer][x] = op(data_[layer][x], data_[layer][x + 1]);
            }

            left += h;
            right = std::min(right + h, size_ - 1);

            if (left >= size_) break;

            // Propagate values to the right within the block
            for (int x = left + 1; x <= right; ++x) {
                data_[layer][x] = op(data_[layer][x - 1], data_[layer][x]);
            }

            left += h;
            right = std::min(right + h, size_ - 1);
        }

        h *= 2; // Double the block size
        ++layer; // Move to the next layer
    }
}

// Query function
template <typename T, auto op>
T DisjointSparseTable<T, op>::Query(int left, int right) {

    if (left == right) {
        // Single-element query
        return data_[0][left];
    }

    // Find the highest differing bit between left and right
    int layer = 31 - __builtin_clz(left ^ right);
    return op(data_[layer][left], data_[layer][right]);
}

#endif // DISJOINTSPARSETABLE_CPP
