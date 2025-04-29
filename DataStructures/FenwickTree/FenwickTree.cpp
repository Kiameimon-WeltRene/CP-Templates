#ifndef FENWICKTREE_CPP
#define FENWICKTREE_CPP

#include "FenwickTree.hpp"

// Constructor from a range of elements
template <HasOp T>
template <Iterator Iter>
FenwickTree<T>::FenwickTree(Iter start, Iter end, T identity)
    : size_(std::distance(start, end) + 1), identity_(identity), data_(size_, identity) {
    int index = 1;
    for (auto it = start; it != end; ++it) {
        data_[index] += *it; // Add the current element to the tree
        int next_block = index + least_significant_bit(index); // Move to the next block
        if (next_block < size_) {
            data_[next_block] += data_[index]; // Propagate the update
        }
        ++index;
    }
}

// Constructor with a given size and identity element
template <HasOp T>
FenwickTree<T>::FenwickTree(int size, T identity)
    : size_(size + 1), identity_(identity), data_(size_, identity) {}

// Query function
template <HasOp T>
T FenwickTree<T>::Query(int left, int right) {
    return sum(right) - sum(left);
}

// Update function
template <HasOp T>
void FenwickTree<T>::Update(int pos, T value) {
    pos++; // Convert to 1-based indexing
    while (pos < size_) {
        data_[pos] += value; // Add the value to the current position
        pos += least_significant_bit(pos); // Move to the next position
    }
}

// Prefix sum function
template <HasOp T>
T FenwickTree<T>::sum(int pos) {
    T result = identity_;
    while (pos > 0) {
        result += data_[pos]; // Accumulate the sum
        pos -= least_significant_bit(pos); // Move to the parent position
    }
    return result;
}

#endif // FENWICKTREE_CPP
