//
// Created by Ezzat on 7/26/2025.
//
#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 4e5 + 10, lg = 20;
int ntoi[N], iton[N], dep[N], tin[N], tout[N], dfsorder[N], qlca[N], ans[N], val[N], idx, timer, frq[N], frq_blk[N];
vector<int> adj[N];
int LG[N], spr[lg][N];
bool isinside[N];

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

void code() {
    int q, n;
    cin >> n >> q;
    vector<int> elm;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        elm.push_back(val[i]);
    }
    std::sort(elm.begin(), elm.end());
    elm.erase(std::unique(elm.begin(), elm.end()), elm.end());
    for (int i = 1; i <= n; ++i) {
        val[i] = std::lower_bound(elm.begin(), elm.end(), val[i]) - elm.begin();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, -1, 0);
    build();
    vector<array<int, 4>> Q(q);
    for (int i = 0; i < q; i++) {
        auto &[l, r, k, Idx] = Q[i];
        int u, v;
        cin >> u >> v >> k;
        if (tin[u] > tin[v])swap(u, v);
        qlca[i] = lca(u, v);
        if (qlca[i] == u) {
            l = tin[u] + 1;
            r = tin[v];
        } else {
            l = tout[u];
            r = tin[v];
        }
        Idx = i;
    }
    int sq = sqrt(N) + 5;
    sort(Q.begin(), Q.end(), [&](array<int, 4> a, array<int, 4> b) {
        return make_pair(a[0] / sq, a[1]) < make_pair(b[0] / sq, b[1]);
    });
    int l = 0, r = -1;
    auto add = [&](int node) {
        // todo
    };
    auto remove = [&](int node) {
        // todo
    };
    auto query = [&](int k) {

    };
    auto toggle = [&](int node) {
        if (isinside[node]) {
            remove(node);
        } else {
            add(node);
        }
        isinside[node] ^= 1;
    };
    for (auto [L, R, k, Idx]: Q) {
        while (l > L)toggle(dfsorder[--l]);
        while (r < R)toggle(dfsorder[++r]);
        while (l < L)toggle(dfsorder[l++]);
        while (r > R)toggle(dfsorder[r--]);
        toggle(dfsorder[tin[qlca[Idx]]]);
        toggle(dfsorder[tin[qlca[Idx]]]);
    }
    for (int i = 0; i < q; ++i) {
        cout << elm[ans[i]] << '\n';
    }

}

int main() {
    int t = 1;
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    // cin >> t;
    for (int i = 0; i < t; ++i) {
        code();
    }
}

