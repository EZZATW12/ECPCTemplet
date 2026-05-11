#include <bits/stdc++.h>
using namespace std;

// O(N + M)

int timer, n, m, cur_id;
vector<int> tin, low, comp_id;
vector<vector<int> > tree;
vector<bool> vis, is_bridge;
vector<vector<pair<int, int> > > al;

void dfs(int u, int p) {
    vis[u] = true;
    low[u] = tin[u] = timer++;
    for (auto &[v, edge]: al[u]) {
        if (v == p) continue;
        if (vis[v]) {
            // back-edge
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            // tree-edge
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                is_bridge[edge] = true;
            }
        }
    }
}

void find_bridges() {
    timer = 1;
    vis.assign(n + 1, false);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    is_bridge.assign(m + 1, false);
    for (int u = 1; u <= n; ++u) {
        if (!vis[u]) {
            dfs(u, -1);
        }
    }
}

void dfs_tree(int u) {
    comp_id[u] = cur_id;
    for (auto &[v, edge]: al[u]) {
        if (is_bridge[edge] || ~comp_id[v]) continue;
        dfs_tree(v);
    }
}

void build_tree() {
    cur_id = 0;
    comp_id.assign(n + 1, -1);
    for (int u = 1; u <= n; ++u) {
        if (~comp_id[u]) continue;
        cur_id++;
        dfs_tree(u);
    }

    tree.assign(cur_id + 1, vector<int>());

    vector<bool> added(m + 1, false);
    for (int u = 1; u <= n; ++u) {
        for (auto &[v, edge]: al[u]) {
            if (is_bridge[edge] && !added[edge]) {
                added[edge] = true;
                tree[comp_id[u]].push_back(comp_id[v]);
                tree[comp_id[v]].push_back(comp_id[u]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}
