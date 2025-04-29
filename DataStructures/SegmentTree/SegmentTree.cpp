#ifndef SEGMENTTREE_CPP
#define SEGMENTTREE_CPP

#include "SegmentTree.hpp"

// Constructor from a range of elements
template <typename T, typename U, auto op, auto update>
template <Iterator Iter>
SegmentTree<T, U, op, update>::SegmentTree(Iter start, Iter end, T identity)
    : size_(std::distance(start, end)), identity_(identity), tree_(2 * size_) {
    // Copy elements into the leaf nodes
    std::copy(start, end, tree_.begin() + size_);

    // Build the tree bottom-up
    for (int i = size_ - 1; i > 0; --i) {
        tree_[i] = op(tree_[2 * i], tree_[2 * i + 1]);
    }
}

// Constructor with a given size and identity element
template <typename T, typename U, auto op, auto update>
SegmentTree<T, U, op, update>::SegmentTree(int size, T identity)
    : size_(size), identity_(identity), tree_(2 * size_, identity) {}

// Query function
template <typename T, typename U, auto op, auto update>
T SegmentTree<T, U, op, update>::Query(int left, int right) {
    T left_result = identity_, right_result = identity_;
    left += size_, right += size_;

    while (left < right) {
        if (left % 2 == 1) {
            left_result = op(left_result, tree_[left]);
            ++left;
        }
        if (right % 2 == 1) {
            --right;
            right_result = op(tree_[right], right_result);
        }
        left /= 2, right /= 2;
    }

    return op(left_result, right_result);
}

// Update function
template <typename T, typename U, auto op, auto update>
void SegmentTree<T, U, op, update>::Update(int pos, U value) {
    pos += size_;
    tree_[pos] = update(tree_[pos], value);
    pos /= 2;
    
    // Propagate the update up the tree
    while(pos > 0) {
        tree_[pos] = op(tree_[2 * pos], tree_[2 * pos + 1]);
        pos /= 2;
    }
}

// Access operator
template <typename T, typename U, auto op, auto update>
const T& SegmentTree<T, U, op, update>::operator[](int index) const {
    return tree_[index + size_];
}

#endif // SEGMENTTREE_CPP
