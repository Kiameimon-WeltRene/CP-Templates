# CP-Templates

A collection of commonly-used data structures and algorithms for competitive programming, implemented in modern C++ (C++20 and above). Each component is modular, header-based, and easy to integrate by simply including the `.hpp` file.

## Structure

### Data Structures
- `DisjointSetUnion/` — Union-Find with path compression and union by rank.
- `DisjointSparseTable/` — Efficient static range queries.
- `DynamicSegmentTree/` — Segment tree that supports queries over wider ranges (say, more than `5e6`).
- `FenwickTree/` — Binary Indexed Tree for range queries and point updates.
- `LazyPropSegtree/` — Segment tree with lazy propagation.
- `SegmentTree/` — Classic segment tree.
- `SparseTable/` — Fast, immutable range queries (e.g., RMQ).

### Algorithms
- `HLD/` — Heavy-Light Decomposition for tree path queries.
- `LCA/` — Lowest Common Ancestor queries with binary lifting.

## Usage

Each module is split into a header (`.hpp`) and implementation (`.cpp`) file. To use them, simply:

```cpp
#include "DataStructures/SegmentTree/SegmentTree.hpp"
// or
#include "Algorithms/HLD/HLD.hpp"
```

For each template, you will find a README file describing how to use it, some benchmarks, as well as credits and sources at the bottom for further reading. If you're interested to find out more about a certain data structure, I recommend searching it up on [CodeForces](https://codeforces.com/catalog), [USACO](https://usaco.guide/adv/offline-del?lang=cpp) or [cp-algorithms](https://cp-algorithms.com/).

## Future Improvements
Some potential future updates:
- A greater variety of templates—especially data structures
- Variant implementations of existing templates catered towards specific data types for further optimization.
- More detailed explanation of each template: How it works, the implementation, and example problems.