//
// Created by Ezzat on 6/22/2025.
//
vector <vector<int>> adj, SCC;
int compId[N], dfn[N], low[N], vis[N], self[N], compself[N], compsz[N], in[N], out[N], good[N];
int vid, idx, timer, comp, n, m;
stack<int> ord;

void Tarjan(int u) {
    vis[u] = vid;
    dfn[u] = low[u] = idx++;
    ord.push(u);
    for (auto v: adj[u]) {
        if (vis[v] != vid) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!~compId[v]) {
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int v;
        do {
            v = ord.top();
            ord.pop();
            compId[v] = comp;
            compsz[comp]++;
        } while (v != u);
        comp++;
    }
}

void Build_SCC() {
    vid++, timer = idx = comp = 1;
    memset(compId, -1, sizeof compId);
    for (int i = 1; i <= n; ++i) {
        if (vis[i] != vid)Tarjan(i);
    }
    SCC = vector < vector < int >> (comp + 5);
    for (int u = 1; u <= n; ++u) {
        compself[compId[u]] |= self[u];
        compself[compId[u]] |= (compsz[compId[u]] >= 2);
        for (auto v: adj[u]) {
            if (compId[v] != compId[u]) {
                SCC[compId[u]].push_back(compId[v]);
            }
        }
    }
    for (int u = 1; u < comp; ++u) {
        std::sort(SCC[u].begin(), SCC[u].end());
        SCC[u].erase(std::unique(SCC[u].begin(), SCC[u].end()), SCC[u].end());
        for (auto v: SCC[u]) {
            in[v]++;
            out[u]++;
        }
    }
};

void dfs(int u) {
    good[u] = 1;
    for (auto v: SCC[u]) {
        if (!good[v])dfs(v);
    }
}

vector<int> topo_sort() {
    dfs(compId[1]);
    queue<int> q;
    vector<int> order;
    for (int u = 1; u < comp; ++u) {
        if (in[u] == 0) {
            q.push(u);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (good[u]) {
            order.push_back(u);
        }
        for (auto v: SCC[u]) {
            if (--in[v] == 0)q.push(v);
        }
    }
    return order;
}