#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int> parent;

    public:
        DisjointSet(int n) {
            parent.resize(n);
            for(int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if(rootX != rootY) {
                parent[rootY] = rootX;
            }
        }

        bool isConnected(int x, int y) {
            return find(x) == find(y);
        }
};

int main() {
    DisjointSet ds(10);

    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);

    cout << "Are 1 and 3 connected? " << (ds.isConnected(1, 3) ? "Yes" : "No") << endl;
    cout << "Are 1 and 4 connected? " << (ds.isConnected(1, 4) ? "Yes" : "No") << endl;

    return 0;
}