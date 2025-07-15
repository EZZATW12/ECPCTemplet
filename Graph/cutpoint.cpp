#include <bits/stdc++.h>
using namespace std;

// O(N + M)

int timer, n, m;
vector<int> tin, low;
vector<vector<int> > adj;
vector<bool> vis, is_cutpoint;

void dfs(int u, int p) {
    vis[u] = true;
    int children = 0;
    tin[u] = low[u] = timer++;
    for (auto &v: adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            // back-edge
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // tree-edge
            if (low[v] >= tin[u] && p != -1) {
                is_cutpoint[u] = true;
            }
            ++children;
        }
    }
    if (p == -1 && children > 1) {
        is_cutpoint[u] = true; // Root with multiple children
    }
}

void find_cutpoint() {
    timer = 1;
    vis.assign(n + 1, false);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    is_cutpoint.assign(n + 1, false);
    for (int u = 1; u <= n; ++u) {
        if (!vis[u]) {
            dfs(u, -1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}