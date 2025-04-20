#ifndef DISJOINTSETUNION_HPP
#define DISJOINTSETUNION_HPP

#include <vector>
#include <algorithm>

/**
 * Disjoint Set Union (DSU) data structure with path compression and union by size.
 * Supports efficient union and find operations.
 */
class DisjointSetUnion {
public:
    /**
     * Constructs a DSU with n elements
     * @param n Number of elements
     */
    explicit DisjointSetUnion(int n);

    /**
     * Finds the root of element x with path compression
     * @param x Element to find
     * @return Root of x
     */
    int root(int x);

    /**
     * Joins two sets containing x and y
     * @param x First element
     * @param y Second element
     */
    void join(int x, int y);

    /**
     * Checks if x and y are in the same set
     * @param x First element
     * @param y Second element
     * @return True if x and y are in the same set
     */
    bool query(int x, int y);

    /**
     * Gets the size of the set containing x
     * @param x Element to check
     * @return Size of the set containing x
     */
    int size(int x);

    /**
     * Gets the total number of sets
     * @return Number of disjoint sets
     */
    int count() const;

private:
    int n;                  // Total number of elements
    int set_count;          // Current number of disjoint sets
    std::vector<int> dsu;   // Parent/size storage (-size for roots)
};

// Include the implementation file for templates
#include "DisjointSetUnion.cpp"

#endif // DISJOINTSETUNION_HPP
