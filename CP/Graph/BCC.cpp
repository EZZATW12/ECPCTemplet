#include <bits/stdc++.h>
using namespace std;

stack<int> order;
int timer, n, m, cur_id;
vector<int> tin, low, comp_id, d;
vector<bool> vis, is_cutpoint;
vector<vector<int> > al, comps, tree, up;

void dfs(int u, int p) {
    vis[u] = true;
    tin[u] = low[u] = timer++;
    order.push(u);
    int children = 0;
    for (int v: al[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tin[u]) {
                is_cutpoint[u] = (p != -1 || children > 1);

                int w;
                vector<int> comp;
                do {
                    w = order.top();
                    order.pop();
                    comp.push_back(w);
                } while (!order.empty() && w != v);
                comp.push_back(u);
                comps.push_back(comp);
            }
            children++;
        }
    }
    if (p == -1 && children > 1) {
        is_cutpoint[u] = true;
    }
}

void build_tree() {
    for (int u = 1; u <= n; u++) {
        if (is_cutpoint[u]) {
            comp_id[u] = cur_id++;
            tree.emplace_back();
        }
    }

    for (auto &comp: comps) {
        int u = cur_id++;
        tree.emplace_back();
        for (int v: comp) {
            if (is_cutpoint[v]) {
                tree[u].push_back(comp_id[v]);
                tree[comp_id[v]].push_back(u);
            } else {
                comp_id[v] = u;
            }
        }
    }
}

void BCC() {
    timer = 1;
    low.assign(n + 1, -1);
    tin.assign(n + 1, -1);
    vis.assign(n + 1, false);
    is_cutpoint.assign(n + 1, false);

    for (int u = 1; u <= n; u++) {
        if (!vis[u]) {
            dfs(u, -1);
        }
    }

    cur_id = 1;
    comp_id = vector<int>(n + 1, -1);
    tree = vector<vector<int> >(1);
    build_tree();
}
