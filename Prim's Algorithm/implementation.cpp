#include<bits/stdc++.h>
using namespace std;

// Prim's Algorithm implementation using a min-heap.
// Idea:
// 1. Always take the smallest edge currently available.
// 2. If that edge leads to an already visited vertex, ignore it.
// 3. Otherwise, add that vertex to the MST and push its outgoing edges.
//
// This is the lazy version of Prim's algorithm.
// The heap may contain duplicate or leftover entries, so visited[] is checked
// again after popping.
class prims{
    public:
    // Function to perform Prim's algorithm and print the edges of the Minimum Spanning Tree (MST).
    void primsAlgo(int n, vector<pair<int,int>> adj[]){
        // Min-heap stores candidate edges as (weight, vertex).
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        // visited[v] tells whether vertex v has already been included in MST.
        vector<int> visited(n, false);
        vector<int> key(n, INT_MAX); // Best known edge weight for each vertex.
        vector<int> parent(n, -1);    // Parent of each vertex in the MST.
        int sum = 0;                  // Total weight of the MST.

        // Start Prim's from vertex 0.
        pq.push({0, 0});
        key[0] = 0;

        while(!pq.empty()){
            // Get the smallest candidate edge available right now.
            auto u = pq.top();
            pq.pop();
            
            // If this vertex was already added through a better edge,
            // skip this leftover heap entry.
            if(visited[u.second]) continue;

            // Now we are really adding this vertex to the MST.
            visited[u.second] = true;
            sum += u.first;

            // Explore all neighbors of the current vertex.
            // For every unvisited neighbor, keep the best edge found so far.
            for(auto it : adj[u.second]){
                int v = it.first;
                int weight = it.second;

                if(!visited[v] && weight < key[v]){
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u.second;
                }
            }
        }

        // Print the edges of the MST.
        for(int i = 1; i < n; i++){
            cout << parent[i] << " - " << i << endl;
        }
    }
};

int main(){
    int n = 5; // Number of vertices
    vector<pair<int,int>> adj[n];

    // Adding edges to the adjacency list
    adj[0].push_back({1, 2});
    adj[0].push_back({3, 6});
    adj[1].push_back({0, 2});
    adj[1].push_back({2, 3});
    adj[1].push_back({3, 8});
    adj[1].push_back({4, 5});
    adj[2].push_back({1, 3});
    adj[2].push_back({4, 7});
    adj[3].push_back({0, 6});
    adj[3].push_back({1, 8});
    adj[4].push_back({1, 5});
    adj[4].push_back({2, 7});

    prims p;
    p.primsAlgo(n, adj);

    cout << "Minimum Spanning Tree edges printed above." << endl;

    return 0;
}