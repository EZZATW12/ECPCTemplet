#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<bool> vis;
stack<int> order;
vector<vector<int> > al, rev_al, components;

void dfs1(int u) {
    vis[u] = true;
    for (int v: al[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    order.push(u);
}

void kosaraju(int u, vector<int> &comp) {
    vis[u] = true;
    comp.push_back(u);
    for (int v: rev_al[u]) {
        if (!vis[v]) {
            kosaraju(v, comp);
        }
    }
}

void scc() {
    components.clear();
    vis.assign(n + 1, false);

    for (int u = 1; u <= n; u++) {
        if (!vis[u]) {
            dfs1(u);
        }
    }

    vis.assign(n + 1, false);

    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (!vis[u]) {
            components.emplace_back();
            kosaraju(u, components.back());
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);


    return 0;
}
