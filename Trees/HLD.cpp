#include <bits/stdc++.h>
using namespace std;

// Heavy-Light Decomposition (HLD) - The Swiss Army Knife for Trees
// Build: O(N)
// Path Queries/LCA: O(log N) jumps
// 1-based indexing for nodes and the flattened array (perfect for SegTrees)
struct HLD {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, head, pos, end_pos, node_at;

    // n: number of nodes (nodes are 1-indexed)
    HLD(int _n) : n(_n), timer(0), adj(_n + 1), parent(_n + 1),
                  depth(_n + 1), head(_n + 1), pos(_n + 1),
                  end_pos(_n + 1), node_at(_n + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Call this after adding all edges. Root is 1 by default.
    void build(int root = 1) {
        dfs1(root, 0, 0);
        dfs2(root, 0, root);
    }

private:
    int dfs1(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        int sz = 1, max_sub = 0;

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v == p) continue;
            int sub_sz = dfs1(v, u, d + 1);
            sz += sub_sz;
            // Heavy-child swap trick: The heaviest child is placed at adj[u][0]
            if (sub_sz > max_sub) {
                max_sub = sub_sz;
                swap(adj[u][0], adj[u][i]);
            }
        }
        return sz;
    }

    void dfs2(int u, int p, int h) {
        head[u] = h;
        pos[u] = ++timer;        // 'pos[u]' is the index of node 'u' in the Segment Tree
        node_at[timer] = u;      // Reverse mapping: SegTree index -> original node

        for (int v : adj[u]) {
            if (v == p) continue;
            // If v is the heavy child (at index 0), it continues the current chain 'h'
            // Otherwise, it starts a new heavy chain with 'v' as the head
            dfs2(v, u, (v == adj[u][0] ? h : v));
        }
        end_pos[u] = timer;      // 'end_pos[u]' marks the end of u's subtree in the SegTree
    }

public:
    // --- UTILITY METHODS ---

    // O(log N) - Lowest Common Ancestor
    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            u = parent[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    // O(log N) - Distance between two nodes (number of edges)
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // --- QUERY RANGES (FOR SEGMENT TREE / FENWICK TREE) ---

    // O(1) - Returns the contiguous [L, R] range for the entire subtree of 'u'.
    pair<int, int> get_subtree_range(int u) {
        return {pos[u], end_pos[u]};
    }

    // O(log N) - Returns a list of disjoint [L, R] ranges covering the path between u and v.
    // Set is_edge = true if values are stored on edges (the deeper node represents the edge).
    vector<pair<int, int>> get_path_ranges(int u, int v, bool is_edge = false) {
        vector<pair<int, int>> ranges;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            ranges.push_back({pos[head[u]], pos[u]});
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);

        if (is_edge && u == v) return ranges; // Do not include the LCA for edge queries
        ranges.push_back({pos[u] + is_edge, pos[v]});
        return ranges;
    }

    // Required struct for non-commutative operations (e.g., Matrix multiplication, string hashing)
    struct DirectedRanges {
        vector<pair<int, int>> up;   // Segments flowing UP to LCA. Range [L, R] means going from R up to L.
        vector<pair<int, int>> down; // Segments flowing DOWN from LCA. Range [L, R] means going from L down to R.
    };

    // O(log N) - Use this when path direction matters!
    DirectedRanges get_directed_path_ranges(int u, int v, bool is_edge = false) {
        DirectedRanges res;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                res.up.push_back({pos[head[u]], pos[u]});
                u = parent[head[u]];
            } else {
                res.down.push_back({pos[head[v]], pos[v]});
                v = parent[head[v]];
            }
        }

        if (depth[u] < depth[v]) {
            if (!is_edge || u != v) res.down.push_back({pos[u] + is_edge, pos[v]});
        } else {
            if (!is_edge || u != v) res.up.push_back({pos[v] + is_edge, pos[u]});
        }
        // Ensure 'down' flows correctly from LCA downwards
        reverse(res.down.begin(), res.down.end());
        return res;
    }
};