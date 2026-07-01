#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, sz;

    DSU(int n) {
        par.resize(n + 1);
        sz.resize(n + 1);
        for (int u = 1; u <= n; u++) {
            par[u] = u;
            sz[u] = 1;
        }
    }

    int parent(int u) {
        if (par[u] == u) return u;
        return par[u] = parent(par[u]);
    }

    void join(int u, int v) {
        u = parent(u), v = parent(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
    }

    bool same(int u, int v) {
        return parent(u) == parent(v);
    }
};
