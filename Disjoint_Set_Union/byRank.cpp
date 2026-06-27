#include <bits/stdc++.h>

using namespace std;

// DSU optimized with union by rank and path compression.
class DSU {
    vector<int> parent;
    vector<int> rank;
public:
    // Constructor initializes each node to be its own parent and rank to 0.
    DSU (int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) 
            parent[i] = i;
    }

    // Find the root of the set containing x with path compression.
    int find(int x) {
        // Path compression keeps the tree shallow over time.
        if (parent[x] == x) {
            return x;
        }

        return parent[x] = find(parent[x]);
    }

    // Union two sets by rank to keep the tree balanced(small trees are attached under larger trees).
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // If both nodes have the same root, they are already connected.
        if(rootX == rootY) return;
        
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                // If ranks match, pick one root and increase its rank.
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main() {
    // Example usage of union by rank.
    DSU ds(10);

    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);
    ds.unite(3, 4);
    ds.unite(5, 6);

    cout << "Are 1 and 3 connected? " << (ds.find(1) == ds.find(3) ? "Yes" : "No") << endl;
    cout << "Are 1 and 4 connected? " << (ds.find(1) == ds.find(4) ? "Yes" : "No") << endl;
    cout << "Are 5 and 6 connected? " << (ds.find(5) == ds.find(6) ? "Yes" : "No") << endl;

    return 0;
}
