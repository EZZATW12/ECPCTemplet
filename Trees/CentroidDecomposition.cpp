int sz[N],par[N];
vector<int> adj[N], nodes;
bool vis[N];
int dfsSz(int u, int p) {
    int &ret = sz[u] = 1;
    for (auto v: adj[u]) {
        if (vis[v] || v == p)continue;
        ret += dfsSz(v, u);
    }
    return ret;
}

int getCentroid(int u, int p, int n) {
    for (auto v: adj[u]) {
        if (vis[v] || v == p)continue;
        if (sz[v] * 2 > n)
            return getCentroid(v, u, n);
    }
    return u;
}

void collect(int u, int p) {
    nodes.push_back(u);
    for(auto v:adj[u]){
        if(vis[v] || v == p)continue;
        collect(v,u);
    }
}


void build(int u, int p) {
    int n = dfsSz(u, p);
    int centroid = getCentroid(u, p, n);
    
    if(~p)par[centroid] = p;
    else par[centroid] = centroid;
    
    vis[centroid] = true;
    for (auto v: adj[centroid]) {
        if(vis[v])continue;
        nodes.clear();
        collect(v, centroid);
    }
    for (auto v: adj[centroid]) {
        if(vis[v])continue;
        build(v, centroid);
    }
}