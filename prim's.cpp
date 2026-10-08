#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge (neighbor vertex, edge weight)
struct Edge {
    int to;
    int weight;
};

// Function to find the Minimum Spanning Tree using Prim's Algorithm
void primMST(int V, const vector<vector<Edge>>& adjList) {
    // Min-heap to store pairs of (weight, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int src = 0; // Start the MST from vertex 0

    // Vectors to track key values, MST inclusion status, and parent nodes
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    // Insert the source vertex into the priority queue and set its key to 0
    pq.push({0, src});
    key[src] = 0;

    int mstTotalWeight = 0;

    while (!pq.empty()) {
        // Extract the vertex with the minimum key value
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        // If the vertex is already part of the MST, skip it
        if (inMST[u]) continue;

        // Include the vertex in the MST
        inMST[u] = true;
        mstTotalWeight += weight;

        // Traverse all adjacent vertices of u
        for (const auto& edge : adjList[u]) {
            int v = edge.to;
            int w = edge.weight;

            // If v is not yet in the MST and the edge weight u-v is smaller than its current key
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    // Print the constructed MST edges and their weights
    cout << "\nEdges in the Minimum Spanning Tree:\n";
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " \t" << key[i] << "\n";
        }
    }
    cout << "\nTotal Weight of MST: " << mstTotalWeight << "\n";
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<Edge>> adjList(V);

    // Hardcoded graph representation: (u, v, weight)
    // Edges connected to Vertex 0
    adjList[0].push_back({1, 2});
    adjList[0].push_back({3, 6});
    adjList[1].push_back({0, 2});
    adjList[3].push_back({0, 6});

    // Edges connected to Vertex 1
    adjList[1].push_back({2, 3});
    adjList[1].push_back({3, 8});
    adjList[1].push_back({4, 5});
    adjList[2].push_back({1, 3});
    adjList[3].push_back({1, 8});
    adjList[4].push_back({1, 5});

    // Edges connected to Vertex 2
    adjList[2].push_back({4, 7});
    adjList[4].push_back({2, 7});

    // Edges connected to Vertex 3
    adjList[3].push_back({4, 9});
    adjList[4].push_back({3, 9});

    // Run the algorithm
    primMST(V, adjList);

    return 0;
}
