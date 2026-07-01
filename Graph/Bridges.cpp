#include <bits/stdc++.h>

using namespace std;

// Condenses a graph into a Bridge Tree (Block-Forest of 2-Edge-Connected Components)
struct BridgeTree {
    int n, timer, num_comps;
    vector<vector<pair<int, int>>> adj; // {v, edge_index}
    vector<pair<int, int>> edges;

    vector<int> tin, low, comp;
    vector<bool> is_bridge;
    vector<vector<int>> tree; // The resulting bridge tree/forest

    // Initialize with number of vertices (0-indexed)
    BridgeTree(int _n) : n(_n), timer(0), num_comps(0),
                         adj(n), tin(n, -1), low(n, -1), comp(n, -1) {}

    void add_edge(int u, int v) {
        int idx = edges.size();
        adj[u].push_back({v, idx});
        adj[v].push_back({u, idx});
        edges.push_back({u, v});
        is_bridge.push_back(false);
    }

    void dfs_bridges(int u, int p_edge = -1) {
        tin[u] = low[u] = ++timer;
        for (auto [v, id]: adj[u]) {
            if (id == p_edge) continue;
            if (tin[v] != -1) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs_bridges(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    is_bridge[id] = true;
                }
            }
        }
    }

    void dfs_comps(int u) {
        comp[u] = num_comps;
        for (auto [v, id]: adj[u]) {
            // Only traverse unvisited nodes across non-bridge edges
            if (comp[v] == -1 && !is_bridge[id]) {
                dfs_comps(v);
            }
        }
    }

    void build() {
        // 1. Find all bridges
        for (int i = 0; i < n; i++) {
            if (tin[i] == -1) dfs_bridges(i);
        }

        // 2. Identify 2-edge-connected components
        for (int i = 0; i < n; i++) {
            if (comp[i] == -1) {
                dfs_comps(i);
                num_comps++;
            }
        }
        // 3. Build the bridge tree
        tree.resize(num_comps);
        for (int i = 0; i < edges.size(); i++) {
            if (is_bridge[i]) {
                int u = comp[edges[i].first];
                int v = comp[edges[i].second];
                tree[u].push_back(v);
                tree[v].push_back(u);
            }
        }
    }
};