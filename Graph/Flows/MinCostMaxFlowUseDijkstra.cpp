struct MCMF {
    struct Edge {
        int to;
        int cap;
        int cost;
        int nxt; // index of the next edge from the same node
    };

    const long long INFLL = 1e18;
    int n;

    vector<Edge> edges;
    vector<int> head, par, flow;
    vector<long long> dist, pot;

    MCMF(int _n) {
        n = _n;
        head.assign(n, -1);
        dist.resize(n);
        pot.resize(n);
        par.resize(n);
        flow.resize(n);
    }

    // Returns the ID of the newly added forward edge
    int addEdge(int u, int v, int cp, int cs) {
        int edge_id = edges.size();

        // Forward edge (index e)
        edges.push_back({v, cp, cs, head[u]});
        head[u] = edges.size() - 1;

        // Backward edge (index e ^ 1)
        edges.push_back({u, 0, -cs, head[v]});
        head[v] = edges.size() - 1;

        return edge_id;
    }

    bool dijkstra(int src, int snk) {
        fill(dist.begin(), dist.end(), INFLL);
        fill(par.begin(), par.end(), -1);

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        dist[src] = 0;
        flow[src] = 2e9; // Infinity for capacity flow
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            // Iterate through the linked list of edges for node u
            for (int e = head[u]; ~e; e = edges[e].nxt) {
                int v = edges[e].to;
                int cp = edges[e].cap;
                int cs = edges[e].cost;

                if (cp == 0) continue;

                long long nd = d + cs + pot[u] - pot[v];
                if (nd < dist[v]) {
                    dist[v] = nd;
                    par[v] = e;
                    flow[v] = min(flow[u], cp);
                    pq.push({nd, v});
                }
            }
        }

        if (dist[snk] == INFLL) return false;

        // Update potentials for the next round
        for (int i = 0; i < n; i++) {
            if (dist[i] < INFLL) {
                pot[i] += dist[i];
            }
        }
        return true;
    }

    // Returns {max_flow, min_cost}
    pair<long long, long long> solve(int src, int snk) {
        long long max_fl = 0, min_cs = 0;
        fill(pot.begin(), pot.end(), 0);

        while (dijkstra(src, snk)) {
            max_fl += flow[snk];
            min_cs += 1LL * flow[snk] * pot[snk];

            // Backtrack to update residual capacities
            for (int e = par[snk]; ~e; e = par[edges[e ^ 1].to]) {
                edges[e].cap -= flow[snk];
                edges[e ^ 1].cap += flow[snk];
            }
        }
        return {max_fl, min_cs};
    }

    // The flow through the forward edge is the capacity of its backward edge (e ^ 1)
    int getFlow(int edge_id) {
        return edges[edge_id ^ 1].cap;
    }
};