//
// Created by Ezzat on 6/22/2025.
//
vector<int> adj[N], adjr[N], scc[N];
int vis[N], head[N], n;
stack<int> topo;

void dfs(int u) {
    vis[u] = 1;
    for (auto v: adj[u]) if (!vis[v]) dfs(v);
    topo.push(u);
}

void dfs2(int u, int g) {
    if (~head[u]) return;
    head[u] = g;
    for (auto v: adjr[u]) dfs2(v, g);
}

void kosaraju() {
    for (int i = 0; i < n; ++i) {
        vis[i] = false;
        head[i] = -1;
    }
    int comps = 0;
    for (int i = 0; i < n; i++)if (!vis[i]) dfs(i);
    while (!topo.empty()) {
        int u = topo.top();
        topo.pop();
        if(~head[u])continue;
        dfs2(u, comps++);
    }
    for (int u = 0; u < n; ++u) {
        for (auto v: adj[u]) {
            if (head[u] == head[v])continue;
            scc[head[u]].push_back(head[v]);
        }
    }
}
