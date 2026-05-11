#include <bits/stdc++.h>

using namespace std;
const int N = 205, M = 405;
const int INF = INT_MAX;

int head[N], to[M], nxt[M], cap[M];
int vis[N], par[N], flow[N];
int vid = 0;
int src, snk;
int ne, n; // Number of edges, Number of nodes

// u: current node, v: neighbor, e: edge index, c: capacity
#define edges(u, v, e, c) for(int e = head[u], c, v; ~e && (c = cap[e] , v = to[e] , 1); e = nxt[e])

void init_graph() {
    ne = 0;
    // Note: Ensure 'n' covers all potential node indices (0 to n-1).
    memset(head, -1, n * sizeof(head[0]));
}

void add_edge(int u, int v, int c) {
    to[ne] = v;
    nxt[ne] = head[u];
    cap[ne] = c;
    head[u] = ne++;
}

void addAugEdge(int u, int v, int forward_cost, int backward_cost = 0) {
    add_edge(u, v, forward_cost); // Forward edge: index 2*k
    add_edge(v, u, backward_cost); // Backward edge: index 2*k + 1
}

// BFS to find an augmenting path from src to snk
int bfs() {
    vis[src] = ++vid, par[src] = -1, flow[src] = INF;
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        edges(u, v, e, c) {
            if (vis[v] == vid || !c) continue;
            vis[v] = vid;
            par[v] = e; // Store the edge index that led here
            flow[v] = min(flow[u], c);

            if (v == snk)
                return flow[snk];

            q.push(v);
        }
    }
    return 0;
}

int max_flow() {
    int flow_sum = 0;
    int f;

    while ((f = bfs())) {
        flow_sum += f;

        // Backtrack from Sink to Source using parent array
        // 'e' is the edge index.
        // 'to[e ^ 1]' gives the node u where the edge u->v started.

        for (int e = par[snk]; ~e; e = par[to[e ^ 1]]) {
            cap[e] -= f; // Decrease forward capacity
            cap[e ^ 1] += f; // Increase backward capacity (residual)
        }
    }

    return flow_sum;
}
