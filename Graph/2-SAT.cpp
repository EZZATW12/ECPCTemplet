struct twoSat {
    int n;
    vector<vector<int>> adj, adj_rev;
    vector<int> ord, root, ans;
    vector<bool> vis;
    int numSCC;
    towSat(int sz) {
        n = sz * 2, numSCC = 0;
        adj.assign(n, {});
        adj_rev.assign(n, {});
        ans.assign(sz, 0);
        root.assign(n, 0);
        vis.assign(n, false);
        ord.clear();
    }
    void add(int tu, int u, int tv, int v) {
        u = (2 * u) + tu, v = (2 * v) + tv;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    void dfs1(int u) {
        vis[u] = true;
        for (auto v: adj[u])
            if (!vis[v])
                dfs1(v);
        ord.push_back(u);
    }
    void dfs2(int u) {
        vis[u] = true;
        root[u] = numSCC;
        for (auto v: adj_rev[u])
            if (!vis[v])
                dfs2(v);
    }
    bool check() {
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);
        reverse(ord.begin(), ord.end());
        vis.assign(n, false);
        for (auto u: ord)
            if (!vis[u])
                dfs2(u), numSCC++;
        for (int i = 0; i < n; i += 2) {
            if (root[i] == root[i + 1])
                return false;
            ans[i / 2] = (root[i] > root[i + 1]);
        }
        return true;
    }
};