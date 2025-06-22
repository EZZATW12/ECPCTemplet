int n;
int up[N][LOG], depth[N], arr[N], in[N], out[N], who[N], timer, sz, ans[N],vis[N];
vector<int> adj[N];

void dfs(int u, int par) {
    in[u] = timer++;
    who[timer - 1] = u;
    for (auto v: adj[u]) {
        if (v == par)continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        dfs(v, u);
    }
    out[u] = timer++;
    who[timer - 1] = u;
}

int LCA(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    int k = depth[u] - depth[v];
    for (int j = LOG - 1; j >= 0; --j) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    if (u == v)
        return u;
    for (int j = LOG - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

void build() {
    dfs(0, 0);
    for (int j = 1; j < LOG; ++j) {
        for (int i = 0; i < n; ++i) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

struct query {
    int l, r, lca, indx;

    bool operator<(const query &rhs) {
        if (l / sz != rhs.l / sz) {
            return l / sz < rhs.l / sz;
        }
        return (l / sz & 1 ? r < rhs.r : r > rhs.r);
    }
};


void update(int u) {
    if (vis[u]) {
        // remove
    } else{
        // add
    }
    vis[u] ^= 1;
}

void getanswer(vector<query> &q) {
    int l = q[0].l, r = q[0].l - 1;
    for (auto &i: q) {
        while (l > i.l)update(who[--l]);
        while (r < i.r)update(who[++r]);
        while (l < i.l)update(who[l++]);
        while (r > i.r)update(who[r--]);

        int u = who[l],v = who[r];

        if (i.lca != u && i.lca != v)update(i.lca);
        ans[i.indx];
        if (i.lca != u && i.lca != v)update(i.lca);
    }
}


void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    build();
    vector<query> q(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (in[u] > in[v])swap(u, v);
        q[i].indx = i;
        q[i].lca = LCA(u, v);
        if (q[i].lca == u) {
            q[i].l = in[u];
            q[i].r = in[v];
        } else {
            q[i].l = out[u];
            q[i].r = in[v];
        }
    }
    
    sz = (int) sqrt(timer);
    sort(all(q));
    getanswer(q);
    
    for (int i = 0; i < q.size(); ++i) {
        cout << ans[i] << endl;
    }
}