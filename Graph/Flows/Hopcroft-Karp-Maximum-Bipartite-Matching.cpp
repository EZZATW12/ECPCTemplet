//
// Created by ezzat on 4/26/2026.
//
#include <vector>
#include <queue>

using namespace std;

// Hopcroft-Karp Algorithm for Maximum Bipartite Matching
// Time Complexity: O(m * sqrt(n)) where n is vertices, m is edges
// Space Complexity: O(n + m)
struct HopcroftKarp {
    int n, m; // Sizes of left partition (U) and right partition (V)
    const int INF = 1e9;

    // adj[u] stores edges from u (in U) to v (in V)
    vector<vector<int>> adj;

    // match_u[i] = matched vertex in V for vertex i in U
    // match_v[j] = matched vertex in U for vertex j in V
    // dist[i] = distance of vertex i in U in the BFS tree
    vector<int> match_u, match_v, dist;

    // Initialize with sizes of left (n) and right (m) partitions.
    // NOTE: 1-based indexing is used. Vertices in U are 1..n, V are 1..m.
    HopcroftKarp(int n, int m) : n(n), m(m), adj(n + 1), match_u(n + 1, 0), match_v(m + 1, 0), dist(n + 1) {}

    // Add a directed edge from u (in U) to v (in V)
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    // BFS phase: Finds the shortest augmenting paths
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; ++u) {
            // If u is unmatched, it's a root of our BFS forest
            if (match_u[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        // dist[0] represents the distance to a dummy "unmatched" node in V
        dist[0] = INF;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // If we haven't found an augmenting path shorter than the current one
            if (dist[u] < dist[0]) {
                for (int v: adj[u]) {
                    int next_u = match_v[v];
                    // If the next vertex in U is unvisited, update its distance and push
                    if (dist[next_u] == INF) {
                        dist[next_u] = dist[u] + 1;
                        q.push(next_u);
                    }
                }
            }
        }
        // Returns true if we found at least one augmenting path
        return dist[0] != INF;
    }

    // DFS phase: Finds a maximal set of disjoint augmenting paths of the shortest length
    bool dfs(int u) {
        if (u != 0) {
            for (int v: adj[u]) {
                int next_u = match_v[v];
                // Only follow edges that are part of the BFS tree
                if (dist[next_u] == dist[u] + 1) {
                    if (dfs(next_u)) {
                        match_v[v] = u;
                        match_u[u] = v;
                        return true;
                    }
                }
            }
            // If no augmenting path can be found from u, mark it as dead
            dist[u] = INF;
            return false;
        }
        return true;
    }

    // Main solver: Returns the size of the maximum bipartite matching
    int solve() {
        int matching = 0;
        // While there is an augmenting path
        while (bfs()) {
            // Try to augment from every unmatched node in U
            for (int u = 1; u <= n; ++u) {
                if (match_u[u] == 0 && dfs(u)) {
                    matching++;
                }
            }
        }
        return matching;
    }
};