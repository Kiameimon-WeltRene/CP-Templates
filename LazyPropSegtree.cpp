#ifndef LAZYPROPSEGTREE_CPP
#define LAZYPROPSEGTREE_CPP

#include "LazyPropSegtree.hpp"

// Constructor from a range of elements
template <typename T, typename U, auto op, auto updVal, auto updLazy>
LazyPropSegtree<T, U, op, updVal, updLazy>::LazyPropSegtree(auto start, auto end, T identityOp, U identityUpdate)
    : size_(std::distance(start, end)), LOG_(32 - __builtin_clz(size_)), identityOp_(identityOp),
      identityUpdate_(identityUpdate), tree_(2 * size_), lazy_(size_, identityUpdate_) {
    std::copy(start, end, tree_.begin() + size_);

    // Build the tree bottom-up
    for (int i = size_ - 1; i > 0; --i) {
        tree_[i] = op(tree_[2 * i], tree_[2 * i + 1]);
    }
}

// Constructor with a given size and identity elements
template <typename T, typename U, auto op, auto updVal, auto updLazy>
LazyPropSegtree<T, U, op, updVal, updLazy>::LazyPropSegtree(int size, T identityOp, U identityUpdate)
    : size_(size), LOG_(31 - __builtin_clz(size_)), identityOp_(identityOp),
      identityUpdate_(identityUpdate), tree_(2 * size_, identityOp_), lazy_(size_, identityUpdate_) {}

// Query function
template <typename T, typename U, auto op, auto updVal, auto updLazy>
T LazyPropSegtree<T, U, op, updVal, updLazy>::Query(int left, int right) {
    T left_result = identityOp_, right_result = identityOp_;
    left += size_, right += size_;

    // Propagate lazy updates
    Propagate(left);
    Propagate(right - 1);

    // Perform the query
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
template <typename T, typename U, auto op, auto updVal, auto updLazy>
void LazyPropSegtree<T, U, op, updVal, updLazy>::Update(int left, int right, U value) {
    left += size_, right += size_;
    int _left = left, _right = right;

    // Apply updates to the leaves
    if (left % 2 == 1) {
        tree_[left] = updVal(tree_[left], value);
        ++left;
    }
    if (right % 2 == 1) {
        --right;
        tree_[right] = updVal(tree_[right], value);
    }

    left /= 2, right /= 2;

    // Propagate updates up the tree
    while (left < right) {
        if (left % 2 == 1) {
            tree_[left] = updVal(tree_[left], value);
            lazy_[left] = updLazy(lazy_[left], value);
            ++left;
        }
        if (right % 2 == 1) {
            --right;
            tree_[right] = updVal(tree_[right], value);
            lazy_[right] = updLazy(lazy_[right], value);
        }
        left /= 2, right /= 2;
    }

    // Recalculate values after updates
    recalculate_after_update(_left);
    recalculate_after_update(_right - 1);
}

// Propagate lazy updates
template <typename T, typename U, auto op, auto updVal, auto updLazy>
void LazyPropSegtree<T, U, op, updVal, updLazy>::Propagate(int pos) {
    for (int shift = LOG_; shift > 1; --shift) {
        int i = pos >> shift;
        if (lazy_[i] != identityUpdate_) {
            tree_[2 * i] = updVal(tree_[2 * i], lazy_[i]);
            lazy_[2 * i] = updLazy(lazy_[2 * i], lazy_[i]);

            tree_[2 * i + 1] = updVal(tree_[2 * i + 1], lazy_[i]);
            lazy_[2 * i + 1] = updLazy(lazy_[2 * i + 1], lazy_[i]);

            lazy_[i] = identityUpdate_;
        }
    }

    pos /= 2;
    if (lazy_[pos] != identityUpdate_) {
        tree_[2 * pos] = updVal(tree_[2 * pos], lazy_[pos]);
        tree_[2 * pos + 1] = updVal(tree_[2 * pos + 1], lazy_[pos]);
        lazy_[pos] = identityUpdate_;
    }
}

// Recalculate values after updates
template <typename T, typename U, auto op, auto updVal, auto updLazy>
void LazyPropSegtree<T, U, op, updVal, updLazy>::recalculate_after_update(int pos) {
    pos /= 2;
    while (pos > 0) {
        tree_[pos] = op(tree_[2 * pos], tree_[2 * pos + 1]);
        tree_[pos] = updVal(tree_[pos], lazy_[pos]);
        pos /= 2;
    }
}

#endif // LAZYPROPSEGTREE_CPP
