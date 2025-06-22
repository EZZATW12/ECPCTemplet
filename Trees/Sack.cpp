vector<int> adj[N];
int n, sz[N], big[N];

void dfsSz(int u, int par) {
    sz[u] = 1;
    for (auto &v: adj[u]) {
        if (v == par)continue;
        dfsSz(v, u);
        sz[u] += sz[v];
        if (big[u] == -1 || sz[v] > sz[big[u]])
            big[u] = v;
    }
}


void collect(int u, int par) {
    // add(u)
    for (auto v: adj[u]) {
        if (v == par)continue;
        collect(v, u);
    }
}


void dfs(int u, int par, bool keep) {
    for (auto v: adj[u]) {
        if (v == par || v == big[u])continue;
        dfs(v, u, false);
    }
    if (~big[u]) {
        dfs(big[u], u, true);
    }
    
    // add(u)
    for (auto v: adj[u]) {
        if (v == par || v == big[u])continue;
        collect(v, u);
    }

    if (!keep) {
        // reset(all)
    }
}