// https://codeforces.com/gym/106063/problem/L

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

template<typename T>
struct segtree {
    int sz = 1;

    vector<T> t, lazy;

    segtree(int n) {
        while (sz < n) sz += sz;
        t.resize(2 * sz, 1);
        lazy.resize(2 * sz, 1);
    }

    long long combine(long long a, long long b) {
        return (a + b) % mod;
    }

    void pull(int x) {
        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void push(int x, int lx, int rx) {
        if (lazy[x] == 1) return;
        //TODO
        t[x] = (t[x] * lazy[x]) % mod;
        if (lx != rx) {
            lazy[2 * x] = (lazy[2 * x] * lazy[x]) % mod;
            lazy[2 * x + 1] = (lazy[2 * x + 1] * lazy[x]) % mod;
        }
        lazy[x] = 1;
    }

    void update(int x, int lx, int rx, int l, int r, T val) {
        push(x, lx, rx);
        if (lx > r || rx < l) return;
        if (lx >= l && rx <= r) {
            lazy[x] = (lazy[x] * val) % mod;
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        update(2 * x, lx, m, l, r, val);
        update(2 * x + 1, m + 1, rx, l, r, val);
        pull(x);
    }

    void update(int l, int r, T val) {
        update(1, 1, sz, l, r, val);
    }

    T query(int x, int lx, int rx, int l, int r) {
        push(x, lx, rx);
        if (rx < l || lx > r) return 0;
        if (lx >= l && rx <= r) return t[x];
        int m = (lx + rx) >> 1;
        return combine(query(2 * x, lx, m, l, r), query(2 * x + 1, m + 1, rx, l, r));
    }

    T query(int l, int r) {
        return query(1, 1, sz, l, r);
    }
};

struct HLD {
    int timer = 1;
    segtree<long long> seg;
    vector<vector<pair<int, int> > > al;
    vector<int> sz, d, par, id, heavy, head, weight;

    HLD(int n, vector<vector<pair<int, int> > > &_al) : seg(n), al(_al), sz(n + 1), heavy(n + 1),
                                                        par(n + 1), id(n + 1), d(n + 1), head(n + 1), weight(n + 1) {
        dfs_sz(1);
        head[1] = 1;
        dfs_hld(1);
        for (int u = 1; u <= n; u++) {
            if (par[u]) seg.update(id[u], id[u], weight[u]);
        }
    }

    void dfs_sz(int u) {
        sz[u] = 1;
        for (auto &[v, w]: al[u]) {
            if (v == par[u]) continue;
            weight[v] = w;
            par[v] = u;
            d[v] = d[u] + 1;
            dfs_sz(v);
            sz[u] += sz[v];
            if (!heavy[u] || sz[v] > sz[heavy[u]]) {
                heavy[u] = v;
            }
        }
    }

    void dfs_hld(int u) {
        id[u] = timer++;
        if (heavy[u]) {
            head[heavy[u]] = head[u];
            dfs_hld(heavy[u]);
        }
        for (auto &[v, w]: al[u]) {
            if (v == par[u] || v == heavy[u]) continue;
            head[v] = v;
            dfs_hld(v);
        }
    }

    vector<pair<int, int> > process(int u, int v, bool edges) {
        vector<pair<int, int> > path;
        while (head[u] != head[v]) {
            if (d[head[u]] > d[head[v]]) swap(u, v);
            path.push_back(make_pair(id[head[v]], id[v]));
            v = par[head[v]];
        }
        if (d[u] > d[v]) swap(u, v);
        path.push_back(make_pair(id[u] + edges, id[v]));
        return path;
    }

    void update(int u, int v, long long x) {
        auto path = process(u, v, true);
        for (auto &[l,r]: path) {
            seg.update(l, r, x);
        }
    }

    long long query(int u, int v) {
        long long ans = 0;
        auto path = process(u, v, true);
        for (auto &[l, r]: path) {
            ans += seg.query(l, r);
            ans %= mod;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<pair<int, int> > > al(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        al[u].push_back(make_pair(v, w));
        al[v].push_back(make_pair(u, w));
    }

    HLD hld(n, al);

    while (q--) {
        int u, v, x;
        cin >> u >> v >> x;
        hld.update(u, v, x);
        cout << hld.query(u, v) << '\n';
    }

    return 0;
}
