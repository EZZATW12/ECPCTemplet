
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1005, M = 4005;
const ll INFLL = (ll)1e18;

int head[N], to[M], nxt[M], cap[M], cost[M];
int par[N], flow[N];
ll dist[N], pot[N];

int src, snk;
int ne, n;

// u: current node, v: neighbor, e: edge index
#define edges(u,v,e,cp,cs) \
    for (int e = head[u], v, cp, cs; \
         ~e && (v = to[e], cp = cap[e], cs = cost[e], 1); \
         e = nxt[e])

/* ---------- Graph ---------- */

void init_graph() {
    ne = 0;
    memset(head, -1, n * sizeof head[0]);
}

void add_edge(int u, int v, int cp, int cs) {
    to[ne] = v;
    cap[ne] = cp;
    cost[ne] = cs;
    nxt[ne] = head[u];
    head[u] = ne++;
}

void addAugEdge(int u, int v, int cp, int cs) {
    add_edge(u, v, cp, cs);
    add_edge(v, u, 0, -cs);
}

/* ---------- Dijkstra with Potentials ---------- */

int dijkstra() {
    for (int i = 0; i < n; i++) {
        dist[i] = INFLL;
        par[i] = -1;
    }

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[src] = 0;
    flow[src] = INT_MAX;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        edges(u, v, e, cp, cs) {
            if (cp == 0) continue;

            ll nd = d + cs + pot[u] - pot[v];
            if (nd < dist[v]) {
                dist[v] = nd;
                par[v] = e;
                flow[v] = min(flow[u], cp);
                pq.push({nd, v});
            }
        }
    }

    if (dist[snk] == INFLL) return 0;

    // Update potentials
    for (int i = 0; i < n; i++)
        if (dist[i] < INFLL)
            pot[i] += dist[i];

    return flow[snk];
}

/* ---------- Min Cost Max Flow ---------- */

pair<ll,ll> mcmf() {
    ll fl = 0, cs = 0;
    memset(pot, 0, n * sizeof pot[0]);

    while (dijkstra()) {
        fl += flow[snk];
        cs += 1LL * flow[snk] * pot[snk];

        for (int e = par[snk]; ~e; e = par[to[e ^ 1]]) {
            cap[e] -= flow[snk];
            cap[e ^ 1] += flow[snk];
        }
    }

    return {fl, cs};
}
