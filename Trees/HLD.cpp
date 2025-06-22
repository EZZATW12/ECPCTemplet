class HLD {
public:
    vector<int> par, sz, head, tin, tout, who, depth;

    int dfs1(int u, vector<vector<int>> &adj) {
        for (int &v: adj[u]) {
            if (v == par[u])continue;
            depth[v] = depth[u] + 1;
            par[v] = u;
            sz[u] += dfs1(v, adj);
            if (sz[v] > sz[adj[u][0]] || adj[u][0] == par[u]) swap(v, adj[u][0]);
        }
        return sz[u];
    }

    void dfs2(int u, int &timer, const vector<vector<int>> &adj) {
        tin[u] = timer++;
        for (int v: adj[u]) {
            if (v == par[u])continue;
            head[v] = (timer == tin[u] + 1 ? head[u] : v);
            dfs2(v, timer, adj);
        }
        tout[u] = timer - 1;
    }

    HLD(vector<vector<int>> adj, int r = 0)
            : par(adj.size(), -1), sz(adj.size(), 1), head(adj.size(), r), tin(adj.size()), who(adj.size()), tout(adj.size()),
              depth(adj.size()){
        dfs1(r, adj);
        int x = 0;
        dfs2(r, x, adj);
        for (int i = 0; i < adj.size(); ++i) who[tin[i]] = i;
    }

    vector<pair<int, int>> path(int u, int v) {
        vector<pair<int, int>> res;
        for (;; v = par[head[v]]) {
            if(depth[head[u]] > depth[head[v]])swap(u,v);
            if(head[u] != head[v]){
                res.emplace_back(tin[head[v]], tin[v]);
            }
            else{
                if(depth[u] > depth[v])swap(u,v);
                res.emplace_back(tin[u],tin[v]);
                return res;
            }
        }
    }

    pair<int, int> subtree(int u) {
        return {tin[u], tout[u]};
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int lca(int u, int v) {
        for (;; v = par[head[v]]) {
            if(depth[head[u]] > depth[head[v]])swap(u,v);
            if(head[u] == head[v]){
                if(depth[u] > depth[v])swap(u,v);
                return u;
            }
        }
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
};