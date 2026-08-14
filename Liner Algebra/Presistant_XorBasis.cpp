#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5 + 5, LOG = 18;


/*
 You are given a tree consisting of n
 vertices. There is an integer written on each vertex; the i
-th vertex has integer ai
 written on it.

You have to process q
 queries. The i
-th query consists of three integers xi
, yi
 and ki
. For this query, you have to answer if it is possible to choose a set of vertices v1,v2,…,vm
 (possibly empty) such that:

every vertex vj
 is on the simple path between xi
 and yi
 (endpoints can be used as well);
av1⊕av2⊕⋯⊕avm=ki
, where ⊕
 denotes the bitwise XOR operator.
 * */
struct Basis {
    int sz, basis[20], last[20];

    Basis() {
        sz = 0;
        memset(basis, 0, sizeof basis);
        memset(last, 0, sizeof last);
    }

    void insert(int mask, int id) {
        for (int i = 19; ~i; --i) {
            if (mask >> i & 1 ^ 1)continue;
            if (last[i] < id) {
                swap(last[i], id);
                swap(basis[i], mask);
            }
            mask ^= basis[i];
        }
    }

    void merge(Basis &other) {
        for (int i = 19; ~i; --i) {
            insert(other.basis[i], other.last[i]);
        }
    }

    bool exist(int k, int id) {
        for (int i = 19; ~i; --i) {
            if (k >> i & 1 ^ 1)continue;
            if (last[i] < id) {
                return 0;
            }
            k ^= basis[i];
        }
        return (k == 0);
    }

    int kth(int k) {
        int ret = 0, cnt = (1 << sz);
        for (int i = 29; ~i; --i) {
            if (basis[i]) {
                cnt >>= 1;
                if (k > cnt && (ret >> i & 1 ^ 1))
                    ret ^= basis[i];
                if (k <= cnt && (ret >> i & 1))
                    ret ^= basis[i];
                if (k > cnt) k -= cnt;
            }
        }
        return ret;
    }
};

vector<int> adj[N];
int depth[N], up[N][LOG], n, timer, tin[N], tout[N], val[N];
Basis pre[N];

void dfs(int u, int p) {
    tin[u] = timer++;
    pre[u].insert(val[u], tin[u]);
    for (auto v: adj[u]) {
        if (v == p)continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u, pre[v] = pre[u];
        dfs(v, u);

    }
    tout[u] = timer - 1;
}

bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int KthAncestor(int u, int k) {
    if (k > depth[u])return 0;
    for (int j = LOG - 1; j >= 0; --j) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    return u;
}

int LCA(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    int k = depth[u] - depth[v];
    u = KthAncestor(u, k);
    if (u == v)
        return u;
    for (int i = LOG - 1; i >= 0; --i)
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    return up[u][0];
}

void build() {
    timer = 1;
    dfs(1, 0);
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build();
    int q;
    cin >> q;
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        int lc = LCA(u, v);
        Basis curr = pre[u];
        curr.merge(pre[v]);
        cout << (curr.exist(k, tin[lc]) ? "YES\n" : "NO\n");
    }

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //  cin >> t;
    for (int i = 1; i <= t; ++i) {
//        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}