struct EulerianUnDirected {
    vector<int> path, edg, deg;
    vector<int> vis;
    int n, m;
    bool euPath, euCycle;
    EulerianUnDirected(const vector<vector<pair<int, int>>> &adj):n(adj.size()), m(0) {
        check(adj);
        if (euPath) {
            // visited for edges not nodes
            vis.assign(m, false);
            dfs(start(adj), -1, adj);
            reverse(path.begin(), path.end());
            reverse(edg.begin(), edg.end());
            euCycle &= (euPath = (edg.size() == m));
        }
        if (euCycle) assert(euPath);
    }
    void check(const vector<vector<pair<int, int>>> &adj) {
        // all degree even or exactly 2 nodes has degree odd
        deg.assign(n, 0);
        for (int u = 0; u < n; ++u)
            for (auto &[v, id]: adj[u])
                deg[u]++, ++m;
        m /= 2;
        int odd = 0;
        for (int i = 0; i < n; ++i)
            odd += deg[i] & 1;
        euCycle = (odd == 0);
        euPath = (odd == 0 || odd == 2);
    }
    int start(const vector<vector<pair<int, int>>> &adj) {
        // node that have degree odd (if not find return any node that have edge)
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            if (deg[i] & 1) return i;
            if (deg[ret] == 0 && deg[i] > 0) ret = i;
        }
        return ret;
    }
    void dfs(int u, int e, const vector<vector<pair<int, int>>> &adj) {
        // do dfs that visit every edge exactly once
        if(~e) vis[e] = true;
        while (deg[u] > 0) {
            deg[u] -= 1;
            auto [v, eid] = adj[u][deg[u]];
            if (!vis[eid]) dfs(v, eid, adj);
        }
        path.push_back(u);
        if (~e) edg.push_back(e);
    }
};