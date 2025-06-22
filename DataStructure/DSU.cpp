//
// Created by Ezzat on 6/2/2025.
//
struct DSU {
    vector<int> par, sz;

    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }

    int find(int x) {
        if (x == par[x])return x;
        return par[x] = find(par[x]);
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y])
            swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return true;
    }

    int size(int x) { return sz[find(x)]; }
};