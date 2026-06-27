#include <iostream>
#include <vector>

using namespace std;

// Basic DSU implementation with path compression.
class DSU {
    vector<int> parent;

    public:
        DSU(int n) {
            parent.resize(n);
            for(int i = 0; i < n; i++)
                parent[i] = i;
        }

        int find(int x) {
            // Compress the path so future lookups are faster.
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }

            return parent[x] = find(parent[x]);
        }

        void unite(int x, int y) {
            // Merge the two components by attaching one root to the other.
            int rootX = find(x);
            int rootY = find(y);

            if(rootX == rootY) return;

            if(rootX != rootY) {
                parent[rootY] = rootX;
            }
        }

        // Check if two nodes are in the same component.
        bool isConnected(int x, int y) {
            return find(x) == find(y);
        }
};

int main() {
    // Small example showing how DSU groups nodes together.
    DSU ds(10);

    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);

    cout << "Are 1 and 3 connected? " << (ds.isConnected(1, 3) ? "Yes" : "No") << endl;
    cout << "Are 1 and 4 connected? " << (ds.isConnected(1, 4) ? "Yes" : "No") << endl;

    return 0;
}