struct EulerianDirected {
    vector<int> path, edg, in, out;
    int n, m;
    bool euPath, euCycle;
    EulerianDirected(const vector<vector<pair<int, int>>> &adj):n(adj.size()), m(0) {
        check(adj);
        if (euPath) {
            dfs(start(adj), -1, adj);
            reverse(path.begin(), path.end());
            reverse(edg.begin(), edg.end());
            euPath &= (edg.size() == m);
            euCycle &= euPath;
        }
    }
    void check(const vector<vector<pair<int, int>>> &adj) {
        in.assign(n, 0);
        out.assign(n, 0);
        euPath = euCycle = true;
        for (int u = 0; u < n; ++u)
            for (auto &[v, id]: adj[u])
                in[v]++, out[u]++, ++m;
        int st = 0, ed = 0;
        for (int i = 0; i < n; ++i) {
            if (out[i] - in[i] > 1 || in[i] - out[i] > 1) euPath = euCycle = false;
            st += out[i] > in[i], ed += out[i] < in[i];
        }
        //        at most one vertex has (out-degree) − (in-degree) = 1,
        //        at most one vertex has (in-degree) − (out-degree) = 1,
        //        every other vertex has equal in-degree and out-degree
        euPath &= st <= 1 && ed <= 1;
        //        every vertex has equal in degree and out degree
        euCycle &= st == ed && st == 0;
    }
    int start(const vector<vector<pair<int, int>>> &adj) {
        //        node that have degree out degree greater than in degree (if not find return any node that have edge)
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            if (out[i] > in[i]) ret = i;
            if (out[ret] == 0 && out[i] > 0) ret = i;
        }
        return ret;
    }
    void dfs(int u, int e, const vector<vector<pair<int, int>>> &adj) {
        // do dfs that visit every edge exactly once
        while (out[u] > 0) {
            out[u] -= 1;
            auto [v, eid] = adj[u][out[u]];
            dfs(v, eid, adj);
        }
        path.push_back(u);
        if (~e) edg.push_back(e);
    }
};