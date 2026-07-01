//
// Created by ezzat on 3/13/2026.
//
#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 4e5 + 10, lg = 20;
int ntoi[N], iton[N], dep[N], tin[N], tout[N], dfsorder[N], idx, timer;
vector<int> adj[N];
int LG[N], spr[lg][N];

void dfs(int u, int p, int d) {
    dep[idx] = d;
    iton[ntoi[u] = idx++] = u;
    dfsorder[tin[u] = timer++] = u;
    for (auto v: adj[u]) {
        if (v == p)continue;
        dfs(v, u, d + 1);
        dep[idx] = d;
        iton[idx++] = u;
    }
    dfsorder[tout[u] = timer++] = u;
}

void build() {
    LG[0] = -1;
    for (int i = 0; i < idx; ++i) {
        LG[i + 1] = LG[i] + !(i & (i + 1));
        spr[0][i] = i;
    }
    for (int j = 1; (1 << j) <= idx; ++j) {
        for (int i = 0; i + (1 << j) <= idx; ++i) {
            int a = spr[j - 1][i];
            int b = spr[j - 1][i + (1 << (j - 1))];
            spr[j][i] = dep[a] < dep[b] ? a : b;
        }
    }
}

int query(int l, int r) {
    int len = (r - l + 1);
    int x = LG[len];
    int a = spr[x][l];
    int b = spr[x][r - (1 << x) + 1];
    return dep[a] < dep[b] ? a : b;
}


int lca(int u, int v) {
    u = ntoi[u], v = ntoi[v];
    if (u > v)swap(u, v);
    return iton[query(u, v)];
}
int dist(int u, int v) {
    return dep[ntoi[u]] + dep[ntoi[v]] - 2 * dep[ntoi[lca(u, v)]];
}
