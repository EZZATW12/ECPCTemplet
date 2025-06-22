//
// Created by Ezzat on 6/22/2025.
//
int T, low[N], dis[N], art[N], ids[N], id;
vector<pair<int, int> > g[N], edges;
vector<int> acy[N];
bool is_bridge[N], vis[N];

void bridges(int u, int p) {
    low[u] = dis[u] = ++T;
    for (auto [v, i]: g[u]) {
        if (!dis[v]) {
            bridges(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dis[u]) {
                is_bridge[i] = 1;
            }
        } else if (v != p) {
            low[u] = min(low[u], dis[v]);
        }
    }
}

void dfs(int u) {
    vis[u] = true;
    ids[u] = id;
    for (auto [v, i]: g[u]) {
        if (!vis[v] and !is_bridge[i]) {
            dfs(v);
        }
    }
}
void BuildTree() {
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        edges.push_back({u, v});
    }
    for (int i = 1; i <= n; ++i) {
        if (!dis[i]) {
            bridges(i, 0);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++id;
            dfs(i);
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (is_bridge[i]) {
            acy[ids[edges[i].first]].push_back(ids[edges[i].second]);
            acy[ids[edges[i].second]].push_back(ids[edges[i].first]);
        }
    }
}