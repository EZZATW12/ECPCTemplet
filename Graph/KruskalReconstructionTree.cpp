/*
 * NAME: Kruskal Reconstruction Tree
 * USE WHEN: queries ask "minimize the maximum edge weight on a path"
 *           or "which nodes are reachable using only edges <= x" —
 *           anything phrased as a bottleneck/threshold connectivity query.
 * COMPLEXITY: O((n+m) log n) build, O(log n) per LCA query after
 * GOTCHAS:
 *   - Build tree has up to 2n-1 nodes; original nodes are leaves
 *     (indices 1..n), new internal nodes get weight = the edge weight
 *     that merged them.
 *   - Built from edges sorted ascending, root holds the largest merge
 *     weight — LCA(u,v) weight = min possible max-edge on the u-v path.
 *   - Use binary lifting for LCA since the tree is static right after build.
 * TESTED ON: bottleneck-path style problems (min possible max edge weight)
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005, LOG = 20;

int par[MAXN], up[MAXN][LOG], depth[MAXN], weight[MAXN];
int n, cnt;
vector<int> children[MAXN];

int find(int x){ return par[x] == x ? x : par[x] = find(par[x]); }

struct Edge { int u, v, w; };

// nOrig = number of original vertices; edges = all candidate edges
void build(vector<Edge>& edges, int nOrig){
    n = nOrig;
    cnt = n;
    for (int i = 1; i <= 2*n; i++) par[i] = i;
    sort(edges.begin(), edges.end(), [](const Edge&a, const Edge&b){ return a.w < b.w; });
    for (auto& e : edges){
        int ru = find(e.u), rv = find(e.v);
        if (ru == rv) continue;
        cnt++;
        weight[cnt] = e.w;
        par[ru] = cnt; par[rv] = cnt;
        children[cnt].push_back(ru);
        children[cnt].push_back(rv);
        par[cnt] = cnt;
    }
}

void dfs(int u, int p){
    up[u][0] = p;
    for (int k = 1; k < LOG; k++)
        up[u][k] = up[up[u][k-1]][k-1];
    for (int c : children[u]){
        depth[c] = depth[u] + 1;
        dfs(c, u);
    }
}

int lca(int u, int v){
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; k++) if (diff & (1<<k)) u = up[u][k];
    if (u == v) return u;
    for (int k = LOG-1; k >= 0; k--)
        if (up[u][k] != up[v][k]) { u = up[u][k]; v = up[v][k]; }
    return up[u][0];
}

/*
 * USAGE EXAMPLE:
 * build(edges, n);          // root ends up being node `cnt`
 * dfs(cnt, cnt);
 * int bottleneck = weight[lca(u, v)]; // min possible max-edge on any u-v path
 * // Note: if u,v end up in different components entirely, lca is undefined —
 * // check connectivity via find() first if the graph might be disconnected.
 */
