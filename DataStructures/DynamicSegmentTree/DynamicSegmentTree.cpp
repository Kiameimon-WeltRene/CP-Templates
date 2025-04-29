#ifndef DYNAMICSEGMENTTREE_CPP
#define DYNAMICSEGMENTTREE_CPP

#include "DynamicSegmentTree.hpp"

template <typename T, typename U, auto op, auto updVal, auto updLazy>
DynamicSegmentTree<T, U, op, updVal, updLazy>::DynamicSegmentTree(
    ll start, ll end, T identityOp, U identityUpdate)
    : start_(start),
      end_(end),
      middle_((start + end) / 2),
      identityOp_(identityOp),
      identityUpdate_(identityUpdate),
      value_(identityOp),
      lazy_(identityUpdate),
      left_(nullptr),
      right_(nullptr) {}

template <typename T, typename U, auto op, auto updVal, auto updLazy>
DynamicSegmentTree<T, U, op, updVal, updLazy>::~DynamicSegmentTree() {
    Clear();
}

template <typename T, typename U, auto op, auto updVal, auto updLazy>
T DynamicSegmentTree<T, U, op, updVal, updLazy>::Query(ll left, ll right) {
    // Query range doesn't overlap with node range
    if (right < start_ || end_ < left) {
        return identityOp_;
    }
    
    // Current node completely contained in query range
    if (left <= start_ && end_ <= right) {
        return value_;
    }
    
    // Propagate updates and query children
    Propagate();
    return op(left_->Query(left, right), right_->Query(left, right));
}

template <typename T, typename U, auto op, auto updVal, auto updLazy>
void DynamicSegmentTree<T, U, op, updVal, updLazy>::Update(ll left, ll right, U value) {
    // Update range doesn't overlap with node range
    if (right < start_ || end_ < left) {
        return;
    }
    
    // Current node completely contained in update range
    if (left <= start_ && end_ <= right) {
        updLazy(lazy_, value_, value, start_, end_);
        return;
    }
    
    // Propagate updates and update children
    Propagate();
    left_->Update(left, right, value);
    right_->Update(left, right, value);
    value_ = op(left_->value_, right_->value_);
}

template <typename T, typename U, auto op, auto updVal, auto updLazy>
void DynamicSegmentTree<T, U, op, updVal, updLazy>::Propagate() {
    // Create children if they don't exist
    if (left_ == nullptr) {
        left_ = new DynamicSegmentTree(start_, middle_, identityOp_, identityUpdate_);
        right_ = new DynamicSegmentTree(middle_ + 1, end_, identityOp_, identityUpdate_);
    }
    
    // Skip if no pending updates
    if (lazy_ == identityUpdate_) {
        return;
    }
    
    // Apply lazy updates to children
    updLazy(left_->lazy_, left_->value_, lazy_, left_->start_, left_->end_);
    updLazy(right_->lazy_, right_->value_, lazy_, right_->start_, right_->end_);
    
    // Clear pending update
    lazy_ = identityUpdate_;
}

template <typename T, typename U, auto op, auto updVal, auto updLazy>
void DynamicSegmentTree<T, U, op, updVal, updLazy>::Clear() {
    if (left_) {
        left_->Clear();
        delete left_;
        left_ = nullptr;
    }
    
    if (right_) {
        right_->Clear();
        delete right_;
        right_ = nullptr;
    }
}

#endif // DYNAMICSEGMENTTREE_CPP
