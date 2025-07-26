struct DSURollback {
    struct Operation {
        int u, v, szU;
    };
    stack<Operation> st;
    vector<int> sz, par;

    DSURollback(int n) {
        par.resize(n);
        sz.resize(n);
    }

    void init() {
        fill(sz.begin(), sz.end(), 1);
        iota(par.begin(), par.end(), 0);
    }

    void rollback(int x) {
        while (st.size() > x) {
            auto e = st.top();
            st.pop();
            sz[e.u] = e.szU;
            par[e.v] = e.v;
        }
    }

    int findSet(int u) {
        return par[u] == u ? u : findSet(par[u]);
    }

    bool sameSet(int u, int v) {
        return findSet(u) == findSet(v);
    }

    void update(int u, int v) {
        st.push({u, v, sz[u]});
        par[v] = u;
        sz[u] += sz[v];
    }

    void unionSet(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u != v) {
            if (sz[u] < sz[v])
                swap(u, v);
            update(u, v);
        }
    }
};

struct SegmentTree {
    int n;
    vector<int> ans;
    vector<vector<pair<int, int>>> tree;
    DSURollback dsuRollback;

    SegmentTree(int N, int Q) : dsuRollback(N) {
        ans.resize(Q, -1);
        n = 1;
        while (n < Q)n *= 2;
        tree.resize(2 * n + 5);
    }

    void solve(int x, int l, int r) {
        int cur = dsuRollback.st.size();
        for (auto i: tree[x])
            dsuRollback.unionSet(i.first, i.second);

        if (l == r) {
            // solve the query at time l
            dsuRollback.rollback(cur);
            return;
        }
        int m = (l + r) >> 1;
        solve(x * 2, l, m);
        solve(x * 2 + 1, m + 1, r);
        dsuRollback.rollback(cur);
    }

    void solve() {
        solve(1, 0, n - 1);
    }

    void addEdge(int x, int lX, int rX, int l, int r, int u, int v) {
        if (rX < l || lX > r)
            return;
        if (lX >= l && rX <= r) {
            tree[x].emplace_back(u, v);
            return;
        }
        int m = (lX + rX) >> 1;
        addEdge(x * 2, lX, m, l, r, u, v);
        addEdge(x * 2 + 1, m + 1, rX, l, r, u, v);
    }

    void addEdge(int u, int v, int l, int r) {
        addEdge(1, 0, n - 1, l, r, u, v);
    }
};