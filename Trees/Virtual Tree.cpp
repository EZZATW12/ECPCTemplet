//
// Created by josal on 6/30/2026.
//

constexpr int MAX_N = 2e6 + 1;
constexpr int LG = 20;

int n;
int tin[MAX_N], tout[MAX_N], d[MAX_N], lift[MAX_N][LG], timer;
vector<int> adj[MAX_N], vadj[MAX_N];

void dfs(int v, int p) {
    tin[v] = timer++;

    lift[v][0] = p;
    for (int i = 1; i < LG; i++) { lift[v][i] = lift[lift[v][i - 1]][i - 1]; }

    for (int u: adj[v]) {
        if (u == p) { continue; }
        dfs(u, v);
    }

    tout[v] = timer++;
}

int is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

int lca(int u, int v) {
    if (is_ancestor(u, v)) { return u; }
    if (is_ancestor(v, u)) { return v; }

    for (int i = LG - 1; i >= 0; i--) {
        if (!is_ancestor(lift[u][i], v)) { u = lift[u][i]; }
    }
    return lift[u][0];
}

bool sort_tin(const int &a, const int &b) { return tin[a] < tin[b]; }

vector<int> vtree(const vector<int> &key) {
    if (key.empty()) return {};

    vector<int> res = key;
    sort(res.begin(), res.end(), sort_tin);

    for (int i = 1; i < (int) key.size(); i++) {
        res.push_back(lca(res[i - 1], res[i]));
    }

    sort(res.begin(), res.end(), sort_tin);
    res.erase(unique(res.begin(), res.end()), res.end());

    for (int v: res) { vadj[v].clear(); }

    for (int i = 1; i < (int) res.size(); i++) {
        vadj[lca(res[i - 1], res[i])].push_back(res[i]);
    }

    return res;
}

ll ans{};
vector<bool> vis(N);
vector<int> cnt(N);

void solve() {
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1);
    int q;
    cin >> q;

    for (int col = 1; col <= q; col++) {
        int k;
        cin >> k;
        ans = 0;
        vector<int> vv(k);
        for (int i = 0; i < k; i++) {
            cin >> vv[i];
            ans += vv[i];
            vis[vv[i]] = true;
        }
        vector<int> vt = vtree(vv);
        reverse(vt.begin(), vt.end());

        for (int v: vt) {
            cnt[v] = vis[v];
            int ch = 0;
            ll sum{cnt[v]};

            for (int u: vadj[v]) {
                ch++;
                cnt[v] += cnt[u];
                sum += cnt[u];
            }
            if (ch == 1) {
                if (vis[v]) {
                    ans += max(0ll, 1ll * v * (cnt[v] - 1));
                }
            } else {
                for (auto u: vadj[v]) {
                    sum -= cnt[u];
                    ans += max(0ll, 1ll * v * (cnt[u]) * sum);
                }
            }
        }
        for (int i = 0; i < k; i++) vis[vv[i]] = false;
        cout << ans << '\n';
    }
}
