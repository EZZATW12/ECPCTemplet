// https://cses.fi/problemset/result/13802419/

#include <bits/stdc++.h>
using namespace std;

int timer, cnt;
vector<vector<int> > al;
vector<int> flatten, in, sz, frq, col, ans;

void add(int u) {
    //TODO
    cnt += (!frq[col[u]]);
    frq[col[u]]++;
}

void remove(int u) {
    //TODO
    cnt -= (frq[col[u]] == 1);
    frq[col[u]]--;
}

int get_answer() {
    //TODO
    return cnt;
}

void pre_dfs(int u, int p) {
    sz[u] = 1;
    in[u] = timer;
    flatten[timer++] = u;
    for (auto &v: al[u]) {
        if (v == p) continue;
        pre_dfs(v, u);
        sz[u] += sz[v];
    }
}

void dfs(int u, int p, bool keep) {
    int mx = -1, big = -1;
    for (auto &v: al[u]) { // get big child
        if (v != p && sz[v] > mx) {
            big = v;
            mx = sz[v];
        }
    }

    for (auto &v: al[u]) { // process smaller child first
        if (v == p || v == big) continue;
        dfs(v, u, false); // process smaller subtree first
    }

    if (~big) { // solve big child
        dfs(big, u, true);
    }

    // add small children
    add(u);
    for (auto &v: al[u]) {
        if (v == p || v == big) continue;
        int l = in[v], r = in[v] + sz[v];
        for (int t = l; t < r; t++) {
            add(flatten[t]);
        }
    }

    ans[u] = get_answer(); // get answer

    if (!keep) { // remove subtree u
        int l = in[u], r = in[u] + sz[u];
        for (int t = l; t < r; t++) {
            remove(flatten[t]);
        }
    }
}

void compression(vector<int> &a, int &n) {
    vector<int> comp(a.begin() + 1, a.end()); // skip index 0 (1-based)

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin() + 1;
    }
    n = comp.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    in.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    frq.assign(n + 1, 0);
    col.assign(n + 1, 0);
    ans.assign(n + 1, 0);
    flatten.assign(n + 5, 0);
    al.assign(n + 1, vector<int>());

    for (int u = 1; u <= n; u++) {
        cin >> col[u];
    }

    int sz = n;
    compression(col, sz);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        al[u].push_back(v);
        al[v].push_back(u);
    }

    pre_dfs(1, 0);

    dfs(1, 0, true);

    for (int u = 1; u <= n; u++) {
        cout << ans[u] << ' ';
    }

    return 0;
}
