#include <vector>
#include <algorithm>

using namespace std;

template <typename T = int>
struct CutpointGraph {
    T n;
    T timer;
    vector<vector<T>> adj;
    vector<T> tin, low;
    vector<bool> vis, is_cutpoint;

    // Initialize the struct with the number of nodes
    CutpointGraph(T n_nodes) {
        n = n_nodes;
        timer = 1;
        adj.assign(n + 1, vector<T>());
        vis.assign(n + 1, false);
        tin.assign(n + 1, -1);
        low.assign(n + 1, -1);
        is_cutpoint.assign(n + 1, false);
    }

    // Adds an undirected edge between u and v
    void add_edge(T u, T v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(T u, T p = -1) {
        vis[u] = true;
        T children = 0;
        tin[u] = low[u] = timer++;

        for (auto &v : adj[u]) {
            if (v == p) continue;

            if (vis[v]) {
                // back-edge
                low[u] = min(low[u], tin[v]);
            } else {
                // tree-edge
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                if (low[v] >= tin[u] && p != -1) {
                    is_cutpoint[u] = true;
                }
                ++children;
            }
        }

        // Root with multiple children is a cutpoint
        if (p == -1 && children > 1) {
            is_cutpoint[u] = true;
        }
    }

    // Runs the algorithm to find all cutpoints in O(N + M)
    void find_cutpoints() {
        for (T u = 1; u <= n; ++u) {
            if (!vis[u]) {
                dfs(u, -1);
            }
        }
    }

    // Returns a vector containing all the cutpoints
    vector<T> get_cutpoints() {
        vector<T> result;
        for (T u = 1; u <= n; ++u) {
            if (is_cutpoint[u]) {
                result.push_back(u);
            }
        }
        return result;
    }
};