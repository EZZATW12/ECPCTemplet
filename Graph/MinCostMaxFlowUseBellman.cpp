#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005, M = 4005;
const int INF = INT_MAX;
// The Time In The Worst Case is O(N * M * F)
int head[N], work[N], to[M], nxt[M], cap[M], cost[M], flow[N];
ll dist[N];
int vis[N], inq[N], par[N], inqid;
int vid = 0;
int src, snk;
int ne, n; // Number of edges, Number of nodes

// u: current node, v: neighbor, e: edge index, c: capacity
#define edges(u,v,e,cp,cs) for(int e = head[u], cp,cs, v; ~e && (cp = cap[e] , v = to[e] , cs = cost[e] , 1); e = nxt[e])

void init_graph() {
    ne = 0;
    // Note: Ensure 'n' covers all potential node indices (0 to n-1).
    memset(head, -1, n * sizeof(head[0]));
}

void add_edge(int u, int v, int cp, int cs) {
    to[ne] = v;
    nxt[ne] = head[u];
    cap[ne] = cp;
    cost[ne] = cs;
    head[u] = ne++;
}

void addAugEdge(int u, int v, int cp, int cs) {
    add_edge(u, v, cp, cs); // Forward edge: index 2*k
    add_edge(v, u, 0, -cs); // Backward edge: index 2*k + 1
}

int bellman_ford() {
    memset(dist, 0x3f, sizeof dist[0] * N);
    dist[src] = 0;
    par[src] = -1;
    flow[snk] = 0;
    flow[src] = INF;

    queue<int> q;
    q.push(src);
    inq[src] = ++inqid;

    int cnt = n;
    while (!q.empty() and --cnt) {
        int sz = q.size();
        while (sz--) {
            int u = q.front();
            q.pop();
            inq[u] = 0;

            edges(u, v, e, cp, cs) {
                if (cp == 0) continue;
                ll new_dist = dist[u] + cs;
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    flow[v] = min(flow[u], cp);
                    par[v] = e;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = inqid;
                    }
                }
            }
        }
    }

    return flow[snk];
}

pair<ll, ll> mcmf() {
    ll fl = 0, f = 0, cs = 0;
    while (bellman_ford()) {
        fl += flow[snk];
        cs += flow[snk] * dist[snk];

        for (int e = par[snk]; ~e; e = par[to[e ^ 1]]) {
            cap[e ^ 1] += flow[snk];
            cap[e] -= flow[snk];
        }
    }

    return {fl, cs};
}