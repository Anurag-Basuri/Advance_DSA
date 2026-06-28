#include<bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, size; 

    public:
        // Constructor initializes each node to be its own parent and size to 0.
        DSU (int n) {
            parent.resize(n);
            size.resize(n, 1);

            for(int i = 0; i < n; i++)
                parent[i] = i;
        }

        // Find the root of the set containing x with path compression.
        int find(int x) {
            if(parent[x] == x)
                return x;

            return parent[x] = find(parent[x]);
        }

        // Union two sets by size to keep the tree balanced (smaller trees are attached under larger trees).
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            // If both nodes have the same root, they are already connected.
            if(rootX == rootY) return;

            if(size[rootX] > size[rootY]) {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            } else {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            }
        }
};

int main () {
    // Example usage of union by size.
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