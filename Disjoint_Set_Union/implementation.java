import java.util.*;

class DisjointSet {
    private final int[] parent;

    DisjointSet(int n) {
        parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }

    boolean isConnected(int x, int y) {
        return find(x) == find(y);
    }
}

public class implementation {
    public static void main(String[] args) {
        DisjointSet ds = new DisjointSet(10);

        ds.unite(1, 2);
        ds.unite(2, 3);
        ds.unite(4, 5);

        System.out.println("Are 1 and 3 connected? " + (ds.isConnected(1, 3) ? "Yes" : "No"));
        System.out.println("Are 1 and 4 connected? " + (ds.isConnected(1, 4) ? "Yes" : "No"));
    }
}
