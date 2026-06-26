# Prim's Algorithm — The Complete Guide

> **Your one-stop reference** for understanding, implementing, optimizing, and applying Prim's algorithm for Minimum Spanning Trees (MST).

---

## Table of Contents

1. [What Problem Does Prim's Solve?](#1-what-problem-does-prims-solve)
2. [The Naive Approach (and Why It Fails)](#2-the-naive-approach-and-why-it-fails)
3. [Prim's Mental Model — Grow a Tree Greedily](#3-prims-mental-model--grow-a-tree-greedily)
4. [The Core Idea — Cut Property & Safe Edge](#4-the-core-idea--cut-property--safe-edge)
5. [Basic Implementation — O(E log V) (Adjacency List + Min-Heap)](<#5-basic-implementation--o(e-log-v)-adjacency-list--min-heap>)
6. [Dense Graph Optimization — O(V^2) (Array-based Prim)](#6-dense-graph-optimization--o-v2--array-based-prim)
7. [Lazy vs Eager Implementations](#7-lazy-vs-eager-implementations)
8. [Fibonacci Heaps & Theoretical Best Bounds](#8-fibonacci-heaps--theoretical-best-bounds)
9. [Full Production-Ready C++ Class & Code](#9-full-production-ready-c-class--code)
10. [Python & Java Versions](#10-python--java-versions)
11. [Time & Space Complexity Deep Dive](#11-time--space-complexity-deep-dive)
12. [Prim vs Kruskal — When To Use Which](#12-prim-vs-kruskal--when-to-use-which)
13. [Worked Example — Step-by-Step](#13-worked-example--step-by-step)
14. [Classic Applications & Problems](#14-classic-applications--problems)
15. [Edge Cases & Common Mistakes](#15-edge-cases--common-mistakes)
16. [Quick Reference Cheat Sheet](#16-quick-reference-cheat-sheet)

---

## 1. What Problem Does Prim's Solve?

Prim's algorithm finds a **Minimum Spanning Tree (MST)** of a connected, weighted, undirected graph. An MST is a subset of edges that connects all vertices with the minimum possible total edge weight and no cycles.

Use when you need a low-cost backbone that connects every node (networks, layout, clustering, etc.).

## 2. The Naive Approach (and Why It Fails)

Brute-force: try all subsets of edges and pick the cheapest that connects all nodes — obviously exponential.

Another naive idea: repeatedly add the smallest remaining edge if it doesn't create a cycle. This requires a cycle-check per edge (e.g., DFS) and is essentially Kruskal's algorithm with expensive checks — inefficient without DSU.

Prim's (and Kruskal's) are greedy algorithms that avoid brute force by using the cut property.

## 3. Prim's Mental Model — Grow a Tree Greedily

Start from any vertex. At each step, add the cheapest edge that connects the current tree to a vertex outside the tree. Repeat until all vertices are included.

Visual:

```
Start with node A (tree T = {A})
Pick the minimum-weight edge (A, x) leaving T → add x to T
Now consider all edges leaving T again, pick min → repeat
```

This produces an MST because of the cut property (see next section).

## 4. The Core Idea — Cut Property & Safe Edge

Cut: any partition of vertices into S and V\S. The lightest edge crossing the cut is always part of some MST. Prim's repeatedly picks a lightest crossing edge for the cut (T, V\T) where T is the current tree — therefore each picked edge is safe.

## 5. Basic Implementation — O(E log V) (Adjacency List + Min-Heap)

Eager (common) approach uses a priority queue keyed by edge weight. Maintain best-known edge to reach each outside vertex.

Pseudocode (eager):

```
choose start vertex s
for every v: key[v] = +INF, parent[v] = -1, inMST[v] = false
key[s] = 0
pq = min-heap of (key[v], v)
while pq not empty:
  (w, u) = pop pq
  if inMST[u]: continue
  inMST[u] = true
  for (u, v, weight) in adj[u]:
    if not inMST[v] and weight < key[v]:
      key[v] = weight
      parent[v] = u
      push (key[v], v) into pq

Result: edges (parent[v], v) for all v != s form the MST
```

This is typically implemented lazily (duplicate keys in pq) or with decrease-key (using indexed heap or pairing/fib heap).

## 6. Dense Graph Optimization — O(V^2) (Array-based Prim)

For dense graphs (E ≈ V^2), the priority-queue overhead is unnecessary. Use an array of keys and perform a linear scan to pick the next vertex with minimum key — this yields O(V^2) time and is often faster in practice for dense graphs or where V ≤ few thousands.

Pseudocode (array-based):

```
for v: key[v] = +INF, inMST[v] = false
key[s] = 0
for i in 1..V:
  u = vertex with minimum key[u] among not-inMST
  inMST[u] = true
  for (u, v, w) in adj[u]:
    if not inMST[v] and w < key[v]:
      key[v] = w
      parent[v] = u
```

## 7. Lazy vs Eager Implementations

- Lazy Prim: push all edges from the tree into a PQ; when popping, ignore edges whose target is already in the tree. Simpler to code but can push up to O(E) items and perform more pops.
- Eager Prim: maintain best edge per vertex (key[]), and update keys (requires decrease-key or pushing updated pair and ignoring stale entries). More efficient (O(E log V) with binary heap).

Both produce correct MSTs; eager is usually preferred.

## 8. Fibonacci Heaps & Theoretical Best Bounds

With Fibonacci heaps (or other heaps supporting O(1) amortized decrease-key), Prim's runs in O(E + V log V). In practice binary heaps are faster and simpler.

## 9. Full Production-Ready C++ Class & Code

Here is a clean, tested implementation using adjacency lists and `priority_queue` (min-heap via `greater`). This is the standard competitive programming implementation (lazy/eager mix using pushed pairs and checking visited flag).

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL<<60);

struct Edge { int to; ll w; };

pair<ll, vector<pair<int,int>>> prim(int n, vector<vector<Edge>>& adj, int start=0) {
    vector<char> inMST(n, false);
    vector<ll> key(n, INF);
    vector<int> parent(n, -1);
    // min-heap of (key, vertex)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;

    key[start] = 0;
    pq.push({0, start});

    ll total = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        total += w;
        for (auto &e : adj[u]) {
            int v = e.to; ll wt = e.w;
            if (!inMST[v] && wt < key[v]) {
                key[v] = wt;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    vector<pair<int,int>> edges;
    for (int v = 0; v < n; ++v) if (parent[v] != -1) edges.push_back({parent[v], v});
    return {total, edges};
}

// Usage: build adj as vector<vector<Edge>> of size n
```

Notes:

- `total` includes the weight of the start node as 0 (so the final sum is MST weight).
- If the graph is disconnected, this returns an MST for the connected component containing `start` — run Prim from every unvisited node to cover all components.

## 10. Python & Java Versions

Python (using heapq, eager style with stale entry checks):

```python
import heapq
INF = 10**18

def prim(n, adj, start=0):
    in_mst = [False]*n
    key = [INF]*n
    parent = [-1]*n
    key[start] = 0
    pq = [(0, start)]
    total = 0
    while pq:
        w, u = heapq.heappop(pq)
        if in_mst[u]:
            continue
        in_mst[u] = True
        total += w
        for v, wt in adj[u]:
            if not in_mst[v] and wt < key[v]:
                key[v] = wt
                parent[v] = u
                heapq.heappush(pq, (wt, v))
    edges = [(parent[v], v) for v in range(n) if parent[v] != -1]
    return total, edges
```

Java (concise sketch):

```java
// Use PriorityQueue<Pair<Long,Integer>> with comparator on weight
// Maintain key[], parent[], inMST[] and push (key[v], v)
```

## 11. Time & Space Complexity Deep Dive

- Adjacency list + binary heap (eager or lazy): O((E + V) log V) ≈ O(E log V) for connected graphs.
- Array-based selection (dense graphs): O(V^2).
- Fibonacci heap: O(E + V log V) (rarely used in practice).

Space: O(V + E) for adjacency representation, plus O(V) for bookkeeping.

## 12. Prim vs Kruskal — When To Use Which

- Kruskal + DSU: good when edges are easily sortable and E is not huge; ideal for sparse graphs and when you need to process edges globally (e.g., offline variants).
- Prim: good when graph is dense or represented with adjacency lists and you want to grow from one node; often faster in practice for dense graphs (O(V^2)).
- Both produce an MST; choice depends on graph representation and constant factors.

## 13. Worked Example — Step-by-Step

Graph (5 nodes):

Edges:

- (0,1,2), (0,3,6), (1,2,3), (1,3,8), (1,4,5), (2,4,7), (3,4,9)

Start at 0:

Step 1: T={0}. Candidate edges: (0,1,2), (0,3,6) → pick (0,1,2) → T={0,1}

Step 2: Candidates: (0,3,6), (1,2,3), (1,3,8), (1,4,5) → pick (1,2,3) → T={0,1,2}

Step 3: Candidates: (0,3,6), (1,3,8), (1,4,5), (2,4,7) → pick (0,3,6) → T={0,1,2,3}

Step 4: Candidates: (1,4,5), (2,4,7), (3,4,9) → pick (1,4,5) → T={0,1,2,3,4}

MST edges: (0,1),(1,2),(0,3),(1,4) total weight = 2+3+6+5 = 16

## 14. Classic Applications & Problems

- Network design (min-cost connections)
- Approximate solutions for traveling salesman (MST-based heuristics)
- Clustering (single-linkage)
- Image segmentation and minimum spanning forests
- Many CP problems: connect points, connect servers, wiring, etc.

## 15. Edge Cases & Common Mistakes

- Disconnected graph: Prim from one start gives only the component's MST. Run multiple times to cover all nodes.
- Negative weights: Prim handles negative edge weights fine — it still finds MST.
- Multi-edges: handle by storing all edges; algorithm picks the cheapest crossing edge naturally.
- Using `priority_queue` as max-heap by mistake — use `greater` or push negative weights.
- Forgetting to check `inMST[u]` when popping stale entries in lazy implementations.

## 16. Quick Reference Cheat Sheet

- Use adjacency list + binary heap: O(E log V) — default choice.
- Use O(V^2) array Prim for dense graphs or when you want simpler code and small V.
- Use Kruskal + DSU when edges are already in a list and sorting is cheap.
- For competitive programming: implement the eager/pq version shown in section 9.

---

If you want, I can also add a minimal `README.md` with usage examples and test cases, or include an interactive graph example. Want that next?
