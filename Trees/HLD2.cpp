vector<pair<int, int> > adj[N];
int val[N], sz[N], par[N], depth[N], heavy[N], head[N], id[N], n, timer{1};

void dfs1(int u, int p, int d) {
    sz[u] = 1, depth[u] = d, par[u] = p;
    for (auto &[v,c]: adj[u]) {
        if (v == p)continue;
        dfs1(v, u, d + 1);
        sz[u] += sz[v];
        if (sz[v] > sz[heavy[u]])
            heavy[u] = v;
    }
}

void dfs2(int u, int par_path) {
    head[u] = par_path;
    id[u] = timer++;
    if (heavy[u])
        for (auto &[v,c]: adj[u]) {
            if (v != par[u] && v == heavy[u])
                dfs2(v, par_path);
        }
    for (auto &[v,c]: adj[u]) {
        if (v == par[u] || v == heavy[u]) continue;
        dfs2(v, v);
    }
}

vector<pair<int, int> > get_path(int u, int v) {
    vector<pair<int, int> > ret;
    while (true) {
        if (depth[head[u]] > depth[head[v]]) swap(u, v);
        if (head[u] != head[v])
            ret.emplace_back(id[head[v]], id[v]);
        else {
            if (depth[u] > depth[v]) swap(u, v);
            ret.emplace_back(id[u] + 1, id[v]);
            return ret;
        }
        v = par[head[v]];
    }
}

void clean() {
    timer = 1;
    for (int i = 1; i <= n; ++i)
        adj[i].clear(), sz[i] = 1, heavy[i] = 0, head[i] = 0;
}
