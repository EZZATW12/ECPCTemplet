//
// Created by ezzat on 4/26/2026.
//
// O(N * M)
struct Kuhn {
    int n, m;
    vector <vector<int>> adj;
    vector<int> matchL, matchR;
    vector<bool> used;

    Kuhn(int n, int m) : n(n), m(m), adj(n), matchL(n, -1), matchR(m, -1), used(m) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool dfs(int u) {
        for (int v: adj[u]) {
            if (!used[v]) {
                used[v] = true;
                if (matchR[v] == -1 || dfs(matchR[v])) {
                    matchL[u] = v;
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    int maxMatching() {
        int result = 0;
        // Greedy pre-matching
        for (int u = 0; u < n; u++)
            for (int v: adj[u])
                if (matchR[v] == -1) {
                    matchL[u] = v;
                    matchR[v] = u;
                    result++;
                    break;
                }
        // Augment
        for (int u = 0; u < n; u++) {
            if (matchL[u] != -1) continue;
            fill(used.begin(), used.end(), false);
            result += dfs(u);
        }
        return result;
    }

    // ============================================
    //  CONSTRUCT THE MATCHING
    // ============================================

    // Returns list of {left, right} pairs
    vector <pair<int, int>> getMatching() {
        vector <pair<int, int>> res;
        for (int u = 0; u < n; u++)
            if (matchL[u] != -1)
                res.push_back({u, matchL[u]});
        return res;
    }

    // Returns right node matched to left node u (-1 if unmatched)
    int getMatchOfLeft(int u) { return matchL[u]; }

    // Returns left node matched to right node v (-1 if unmatched)
    int getMatchOfRight(int v) { return matchR[v]; }
};