#include <bits/stdc++.h>
using namespace std;

vector<int> d;
vector<vector<int> > up, mx;
vector<vector<pair<int, int> > > al;

void dfs_lca(int u, int p) {
    for (auto &[v, w]: al[u]) {
        if (v == p) continue;

        d[v] = d[u] + 1;
        up[v][0] = u, mx[v][0] = w;
        for (int bit = 1; bit < 18; bit++) {
            up[v][bit] = up[up[v][bit - 1]][bit - 1];
            mx[v][bit] = max(mx[v][bit - 1], mx[up[v][bit - 1]][bit - 1]);
        }

        dfs_lca(v, u);
    }
}

int queryMx(int u, int v) {
    if (d[u] > d[v]) {
        swap(u, v);
    }

    int ans = 0, k = d[v] - d[u];
    for (int bit = 0; bit < 18; bit++) {
        if (k >> bit & 1) {
            ans = max(ans, mx[v][bit]);
            v = up[v][bit];
        }
    }

    if (u == v) return ans;

    for (int bit = 17; bit >= 0; bit--) {
        if (up[u][bit] != up[v][bit]) {
            ans = max(ans, max(mx[u][bit], mx[v][bit]));
            u = up[u][bit];
            v = up[v][bit];
        }
    }
    ans = max(ans, max(mx[u][0], mx[v][0]));

    return ans;
}
