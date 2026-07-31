//
// Created by ezzat on 7/13/2026.
//
// Time Complexity O(V^3)
// Global Minimum Cut for undirected graph

pair<long long, vector<int> > stoer_wagner(vector<vector<long long> > g) {
    int n = (int) g.size() - 1;

    long long min_cut = -1;
    vector<vector<int> > v(n + 1);
    vector<int> nodes, best_partition;
    for (int u = 0; u <= n; ++u) {
        v[u].push_back(u);
        nodes.push_back(u);
    }

    vector<bool> in(n + 1);
    vector<long long> w(n + 1);
    while (nodes.size() > 1) {
        fill(w.begin(), w.end(), 0);
        fill(in.begin(), in.end(), false);

        int prev = -1;
        for (int i = 0; i < nodes.size(); ++i) {
            int next = -1;
            for (auto &u: nodes) {
                if (!in[u] && (next == -1 || w[u] > w[next])) {
                    next = u;
                }
            }

            if (i == (int) nodes.size() - 1) {
                if (min_cut == -1 || w[next] < min_cut) {
                    min_cut = w[next];
                    best_partition = v[next];
                }

                v[prev].insert(v[prev].end(), v[next].begin(), v[next].end());
                for (auto &u: nodes) {
                    if (u != prev && u != next) {
                        g[prev][u] += g[next][u];
                        g[u][prev] += g[u][next];
                    }
                }
                nodes.erase(find(nodes.begin(), nodes.end(), next));
            } else {
                in[next] = true;
                for (auto &u: nodes) {
                    if (!in[u]) w[u] += g[next][u];
                }
                prev = next;
            }
        }
    }
    return make_pair(min_cut, best_partition); // best_partition is only the left side
}
