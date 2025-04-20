# CP-Templates

A collection of commonly-used data structures and algorithms for competitive programming, implemented in modern C++ (C++20 and above). Each component is modular, header-based, and easy to integrate by simply including the `.hpp` file.

## 📁 Structure

### 🔹 Data Structures
- `DisjointSetUnion/` — Union-Find with path compression and union by rank.
- `DisjointSparseTable/` — Efficient static range queries.
- `DynamicSegmentTree/` — Segment tree that supports queries over wider ranges (say, more than `5e6`).
- `FenwickTree/` — Binary Indexed Tree for prefix sums.
- `LazyPropSegtree/` — Segment tree with lazy propagation.
- `SegmentTree/` — Classic segment tree.
- `SparseTable/` — Fast, immutable range queries (e.g., RMQ).

### 🔸 Algorithms
- `HLD/` — Heavy-Light Decomposition for tree path queries.
- `LCA/` — Lowest Common Ancestor queries with binary lifting.

## 🛠 Usage

Each module is split into a header (`.hpp`) and implementation (`.cpp`) file. To use them, simply:

```cpp
#include "SegmentTree/SegmentTree.hpp"
// or
#include "HLD/HLD.hpp"
```

README files describing how each algorithm works, as well as credits and sources for further reading will be added for every algorithm implemented here in the future.