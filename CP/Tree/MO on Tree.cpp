// https://www.spoj.com/problems/COT2/

#include <bits/stdc++.h>
using namespace std;

void compression(vector<int> &a, int &n) {
    vector<int> comp(a.begin() + 1, a.end());

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin() + 1;
    }
}

const int N = 40005;

bool seen[N];
vector<int> a, al[N];
int tin[N], tout[N], flatten[2 * N], timer, d[N], up[N][20], cur, frq[N];

void euler_tour(int u, int p) {
    tin[u] = ++timer;
    flatten[timer] = u;
    for (int &v: al[u]) {
        if (v == p) continue;
        euler_tour(v, u);
    }
    tout[u] = ++timer;
    flatten[timer] = u;
}

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

struct Query {
    int l, r, idx, lca;
};

void add(int u) {
    frq[a[u]]++;
    cur += (frq[a[u]] == 1);
}

void remove(int u) {
    cur -= (frq[a[u]] == 1);
    frq[a[u]]--;
}

void toggle(int u) {
    if (seen[u]) {
        remove(u);
    } else {
        add(u);
    }
    seen[u] = !seen[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int block_size = ceil(sqrt(n));

    a.assign(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        cin >> a[u];
    }

    compression(a, n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        al[u].push_back(v);
        al[v].push_back(u);
    }

    euler_tour(1, 0);

    dfs_lca(1, 0);

    vector<Query> queries;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (tin[v] < tin[u]) swap(u, v);

        int lc = lca(u, v);
        if (lc == u) {
            queries.push_back({tin[u], tin[v], i, -1});
        } else {
            queries.push_back({tout[u], tin[v], i, lc});
        }
    }

    sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) {
        return make_pair(a.l / block_size, ((a.l / block_size) & 1) ? -a.r : +a.r) < make_pair(b.l / block_size, ((b.l / block_size) & 1) ? -b.r : +b.r);
    });

    vector<int> ans(m);
    int mo_left = 1, mo_right = 0;
    for (const auto &[l, r, idx, lca]: queries) {
        while (mo_left > l) toggle(flatten[--mo_left]);
        while (mo_right < r) toggle(flatten[++mo_right]);
        while (mo_left < l) toggle(flatten[mo_left++]);
        while (mo_right > r) toggle(flatten[mo_right--]);

        if (~lca) add(lca);
        ans[idx] = cur;
        if (~lca) remove(lca);
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
