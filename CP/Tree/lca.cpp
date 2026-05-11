#include <bits/stdc++.h>
using namespace std;

vector<int> d;
vector<vector<int> > al, up;

void dfs_lca(int u, int p) {
    up[u][0] = p;
    for (int bit = 1; bit < 18; bit++) {
        up[u][bit] = (up[u][bit - 1] < 0 ? -1 : up[up[u][bit - 1]][bit - 1]);
    }
    for (int v: al[u]) {
        if (v == p) continue;
        d[v] = d[u] + 1;
        dfs_lca(v, u);
    }
}

int kth(int u, int k) {
    for (int bit = 0; bit < 18; bit++) {
        if (k >> bit & 1) u = up[u][bit];
    }
    return u;
}

int lca(int u, int v) {
    if (d[u] > d[v]) swap(u, v);
    v = kth(v, d[v] - d[u]);
    if (u == v) return u;
    for (int bit = 17; bit >= 0; bit--) {
        if (up[u][bit] != up[v][bit]) {
            u = up[u][bit];
            v = up[v][bit];
        }
    }
    return up[u][0];
}

int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}

// return node on path u->v at distance k from u
int kth_on_path(int u, int v, int k) {
    int L = lca(u, v), dis = dist(u, v);
    if (k <= d[u] - d[L]) {
        return kth(u, k);
    }
    return kth(v, dis - k);
}
