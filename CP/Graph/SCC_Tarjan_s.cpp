#include <bits/stdc++.h>
using namespace std;

vector<bool> vis;
stack<int> order;
int timer, n, m, id;
vector<vector<int> > tree;
vector<int> tin, low, comp_id;
vector<vector<pair<int, int> > > al;

void tarjan(int u, int p) {
    vis[u] = true;
    order.push(u);
    tin[u] = low[u] = timer++;
    for (auto &[v, _]: al[u]) {
        if (v == p) continue;
        if (!vis[v]) {
            // white-not-visited
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (comp_id[v] == -1) {
            // gray-in-stack
            low[u] = min(low[u], low[v]);
        }
    }

    if (low[u] == tin[u]) {
        int v;
        do {
            v = order.top();
            order.pop();
            comp_id[v] = id;
        } while (u != v);
        id++;
    }
}

void scc() {
    timer = 1, id = 1;
    vis.assign(n + 1, false);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    comp_id.assign(n + 1, -1);
    for (int u = 1; u <= n; ++u) {
        if (!vis[u]) {
            tarjan(u, -1);
        }
    }
}

void build_tree() {
    vector<bool> added(m + 1, false);
    tree = vector<vector<int> >(id + 1);
    for (int u = 1; u <= n; ++u) {
        for (auto &[v, edge]: al[u]) {
            if (comp_id[v] != comp_id[u] && !added[edge]) {
                added[edge] = true;
                // TODO
                tree[comp_id[u]].push_back(comp_id[v]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);


    return 0;
}
