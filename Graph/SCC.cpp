#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T = int>
struct SCCGraph {
    T n;
    T vid, idx, comp;

    vector<vector<T>> adj, SCC;
    vector<T> compId, dfn, low, vis, self_loop, compself, compsz;
    vector<T> in, out, good;
    stack<T> ord;

    // Initialize the struct with the number of nodes
    SCCGraph(T n_nodes) {
        n = n_nodes;
        vid = 0;

        adj.assign(n + 1, vector<T>());
        compId.assign(n + 1, -1);
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        vis.assign(n + 1, 0);

        // Sized to n + 1 (max possible components)
        self_loop.assign(n + 1, 0);
        compself.assign(n + 1, 0);
        compsz.assign(n + 1, 0);
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        good.assign(n + 1, 0);
    }

    // Adds a directed edge from u to v
    void add_edge(T u, T v) {
        adj[u].push_back(v);
        if (u == v) {
            self_loop[u] = 1;
        }
    }

    void tarjan(T u) {
        vis[u] = vid;
        dfn[u] = low[u] = idx++;
        ord.push(u);

        for (auto v : adj[u]) {
            if (vis[v] != vid) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (compId[v] == -1) { // Equivalent to !~compId[v]
                low[u] = min(low[u], low[v]);
            }
        }

        if (low[u] == dfn[u]) {
            T v;
            do {
                v = ord.top();
                ord.pop();
                compId[v] = comp;
                compsz[comp]++;
            } while (v != u);
            comp++;
        }
    }

    void build_SCC() {
        vid++;
        idx = comp = 1; // Removed 'timer' as it wasn't used in your snippet
        compId.assign(n + 1, -1);

        // 1. Find SCCs
        for (T i = 1; i <= n; ++i) {
            if (vis[i] != vid) {
                tarjan(i);
            }
        }

        // 2. Build Condensed DAG
        SCC.assign(comp + 5, vector<T>());

        for (T u = 1; u <= n; ++u) {
            compself[compId[u]] |= self_loop[u];
            compself[compId[u]] |= (compsz[compId[u]] >= 2);

            for (auto v : adj[u]) {
                if (compId[v] != compId[u]) {
                    SCC[compId[u]].push_back(compId[v]);
                }
            }
        }

        // 3. Remove duplicate edges and calculate degrees
        for (T u = 1; u < comp; ++u) {
            sort(SCC[u].begin(), SCC[u].end());
            SCC[u].erase(unique(SCC[u].begin(), SCC[u].end()), SCC[u].end());

            for (auto v : SCC[u]) {
                in[v]++;
                out[u]++;
            }
        }
    }

    void dfs_good(T u) {
        good[u] = 1;
        for (auto v : SCC[u]) {
            if (!good[v]) {
                dfs_good(v);
            }
        }
    }

    // Returns the topological sort of "good" components
    // start_node defaults to 1 just like in your original code
    vector<T> topo_sort(T start_node = 1) {
        // Mark reachable components
        if (compId[start_node] != -1) {
            dfs_good(compId[start_node]);
        }

        queue<T> q;
        vector<T> order;

        for (T u = 1; u < comp; ++u) {
            if (in[u] == 0) {
                q.push(u);
            }
        }

        while (!q.empty()) {
            T u = q.front();
            q.pop();

            if (good[u]) {
                order.push_back(u);
            }

            for (auto v : SCC[u]) {
                if (--in[v] == 0) {
                    q.push(v);
                }
            }
        }
        return order;
    }
};