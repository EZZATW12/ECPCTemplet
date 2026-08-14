#include <vector>
#include <algorithm>

using namespace std;

template <typename T = int>
struct TreeLCA {
    T n;
    T idx, timer;
    T max_euler;
    T max_log;

    vector<vector<T>> adj;
    vector<T> ntoi, iton, dep, tin, tout, dfsorder, LG;
    vector<vector<T>> spr;

    // Initialize the struct with the number of nodes
    TreeLCA(T n_nodes) {
        n = n_nodes;
        max_euler = 2 * n + 5; // Euler tour takes up to 2*N vertices

        max_log = 0;
        while ((1 << max_log) <= max_euler) {
            max_log++;
        }

        adj.assign(n + 1, vector<T>());
        ntoi.assign(n + 1, 0);
        tin.assign(n + 1, 0);
        tout.assign(n + 1, 0);

        iton.assign(max_euler, 0);
        dep.assign(max_euler, 0);
        dfsorder.assign(max_euler, 0);
        LG.assign(max_euler, 0);

        spr.assign(max_log, vector<T>(max_euler, 0));
    }

    // Adds an undirected edge between u and v
    void add_edge(T u, T v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(T u, T p, T d) {
        dep[idx] = d;
        ntoi[u] = idx;
        iton[idx++] = u;

        tin[u] = timer;
        dfsorder[timer++] = u;

        for (auto v : adj[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1);
            dep[idx] = d;
            iton[idx++] = u;
        }

        tout[u] = timer;
        dfsorder[timer++] = u;
    }

    // Build the Euler tour and Sparse Table (RMQ)
    // You can specify a root node (defaults to 1)
    void build(T root = 1) {
        idx = timer = 0;
        dfs(root, -1, 0);

        LG[0] = -1;
        for (T i = 0; i < idx; ++i) {
            LG[i + 1] = LG[i] + !(i & (i + 1));
            spr[0][i] = i;
        }

        for (T j = 1; (1 << j) <= idx; ++j) {
            for (T i = 0; i + (1 << j) <= idx; ++i) {
                T a = spr[j - 1][i];
                T b = spr[j - 1][i + (1 << (j - 1))];
                spr[j][i] = (dep[a] < dep[b]) ? a : b;
            }
        }
    }

    // Internal RMQ query for LCA
    T query(T l, T r) {
        T len = (r - l + 1);
        T x = LG[len];
        T a = spr[x][l];
        T b = spr[x][r - (1 << x) + 1];
        return (dep[a] < dep[b]) ? a : b;
    }

    // Returns the Lowest Common Ancestor of nodes u and v
    T lca(T u, T v) {
        u = ntoi[u];
        v = ntoi[v];
        if (u > v) swap(u, v);
        return iton[query(u, v)];
    }

    // Returns the distance (number of edges) between u and v
    T dist(T u, T v) {
        return dep[ntoi[u]] + dep[ntoi[v]] - 2 * dep[ntoi[lca(u, v)]];
    }

    // Bonus: Returns true if 'u' is an ancestor of 'v'
    bool is_ancestor(T u, T v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
};