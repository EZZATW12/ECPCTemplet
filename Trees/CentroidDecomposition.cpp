#include <bits/stdc++.h>

using namespace std;
const int N = 1e5;
int n, q, sz[N], removed[N], par[N], best[N]; // the par for the centroid tree !!!
vector<int> adj[N];

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v == p || removed[v]) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int p, int tree_sz) {
    for (auto v: adj[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] * 2 > tree_sz)
            return get_centroid(v, u, tree_sz);
    }
    return u;
}

void build_centroid_tree(int u, int p) {
    dfs_sz(u, u);
    int c = get_centroid(u, u, sz[u]);
    par[c] = p;
    removed[c] = 1;
    for (auto v: adj[c]) {
        if (removed[v])continue;
        build_centroid_tree(v, c);
    }
}

long long query(int u, int p) {
    // todo
    long long ret = 0;
    for (auto v: adj[u]) {
        if (v == p || removed[v])continue;
        ret += query(v, u);
    }
    return ret;
}

void update(int u, int p) {
    // todo
    for (auto v: adj[u]) {
        if (v == p || removed[v])continue;
        update(v, u);
    }
}

void rec(int u) {
    dfs_sz(u, -1);
    int c = get_centroid(u, -1, sz[u]);
    // calc  the ans
    for (auto v: adj[c]) {
        if (removed[v])continue;
       // query
       // update
    }

    // remove the centroid
    removed[c] = 1;
    for (auto v: adj[c]) {
        if (removed[v])continue;
        rec(v);
    }
}

