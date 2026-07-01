#include <bits/stdc++.h>
using namespace std;
 
int k;
long long ans;
vector<int> sz, frq;
vector<bool> removed;
vector<vector<int> > al;
 
int get_sz(int u, int p) {
    sz[u] = 1;
    for (auto &v: al[u]) {
        if (v == p || removed[v]) continue;
        sz[u] += get_sz(v, u);
    }
    return sz[u];
}
 
int get_centroid(int u, int p, int cur_sz) {
    for (auto &v: al[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] > cur_sz / 2) {
            return get_centroid(v, u, cur_sz);
        }
    }
    return u;
}
 
void get_answer(int u, int p, int d) {
    ans += (k >= d ? frq[k - d] : 0);
    for (auto &v: al[u]) {
        if (v == p || removed[v]) continue;
        get_answer(v, u, d + 1);
    }
}
 
void update(int u, int p, int d, int op) {
    frq[d] += op;
    for (auto &v: al[u]) {
        if (v == p || removed[v]) continue;
        update(v, u, d + 1, op);
    }
}
 
void decomp(int u) {
    int cur_sz = get_sz(u, -1);
    int centroid = get_centroid(u, -1, cur_sz);
 
    frq[0] = 1;
 
    for (auto &v: al[centroid]) {
        if (removed[v]) continue;
        get_answer(v, centroid, 1);
        update(v, centroid, 1, 1);
    }
 
    for (auto &v: al[centroid]) {
        if (removed[v]) continue;
        update(v, centroid, 1, -1);
    }
 
    removed[centroid] = true;
 
    for (auto &v: al[centroid]) {
        if (removed[v]) continue;
        decomp(v);
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n >> k;
    sz.assign(n + 1, 0);
    frq.assign(n + 5, 0);
    removed.assign(n + 1, false);
    al.assign(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        al[u].push_back(v);
        al[v].push_back(u);
    }
 
    decomp(1);
 
    cout << ans;
 
    return 0;
}
