// https://judge.yosupo.jp/problem/maximum_independent_set

#include <bits/stdc++.h>
using namespace std;

// Bron-Kerbosch
// Used to find the Maximum Independent Set (The maximum clique in complement graph)

int n;
vector<int> mx, cur;
vector<bitset<40> > al;

void bronk(bitset<40> cur_clique, bitset<40> can_add, bitset<40> used) {
    if (can_add.none() && used.none()) {
        if (cur.size() > mx.size()) {
            mx = cur;
        }
        return;
    }

    int u = -1; // choose a pivot u
    for (int node = 0; node < n; node++) {
        if (can_add[node] || used[node]) {
            u = node;
            break;
        }
    }

    bitset<40> to_iterate = can_add;
    if (u != -1) { // iterate only over vertices in can_add that are not neighbors of the pivot
        to_iterate &= ~al[u];
    }

    for (int v = 0; v < n; v++) {
        if (!to_iterate[v]) continue;

        cur.push_back(v);

        bronk(cur_clique | bitset<40>().set(v), can_add & al[v], used & al[v]);

        cur.pop_back();

        // move v from can_add to used
        can_add.reset(v);
        used.set(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;
    al.assign(n, bitset<40>());
    vector<vector<bool> > g(n, vector<bool>(n));
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u][v] = true;
        g[v][u] = true;
    }

    // build the complement graph if two vertices are not connected in the original graph, connect them here
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && !g[u][v]) {
                al[u].set(v);
            }
        }
    }

    bitset<40> cur_clique, can_add, used;
    for (int u = 0; u < n; u++) {
        can_add.set(u);
    }

    bronk(cur_clique, can_add, used);

    cout << mx.size() << '\n';
    for (auto &it: mx) {
        cout << it << ' ';
    }

    return 0;
}
