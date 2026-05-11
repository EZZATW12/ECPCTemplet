#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
vector<array<int, 3> > edges;
vector<vector<pair<int, int> > > al;

bool spfa(int src, vector<int> &d) {
    d.assign(n, INF);
    d[src] = 0;

    vector<int> cnt(n + 1, 0);

    vector<bool> inqueue(n + 1);
    inqueue[src] = true;

    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;
        for (auto &[v, w]: al[u]) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                if (!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n) {
                        return false; // negative cycle
                    }
                }
            }
        }
    }
    return true;
}

vector<int> detect_any_cycle() {
    vector<int> cycle, par(n + 1);
    vector<long long> dist(n + 1);

    int lst = -1;
    for (int i = 1; i <= n; i++) {
        lst = -1; // DON'T MISS IT
        for (auto &[u, v, w]: edges) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                par[v] = u;
                lst = v;
            }
        }
    }

    if (~lst) {
        for (int i = 1; i <= n; i++) {
            lst = par[lst];
        }

        int u = lst;
        do {
            cycle.push_back(lst);
            lst = par[lst];
        } while (lst != u);
        cycle.push_back(u);

        reverse(cycle.begin(), cycle.end());
    }
    return cycle;
}