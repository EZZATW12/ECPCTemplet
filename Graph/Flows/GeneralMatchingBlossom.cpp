/*
 * NAME: General Graph Matching (Blossom Algorithm)
 * USE WHEN: need maximum matching in a graph that is NOT guaranteed
 *           bipartite — Kuhn's / Hopcroft-Karp only work on bipartite
 *           graphs; this is the one that works on any graph.
 * COMPLEXITY: O(V^3)
 * GOTCHAS:
 *   - 1-indexed; vertex 0 is unused, set n before calling.
 *   - match_[v] == 0 means v is currently unmatched.
 *   - This finds a MAXIMUM matching, not necessarily a perfect one —
 *     check match_[] to see which vertices ended up unmatched.
 *   - Bump MAXN to fit your n; this is O(V^3) so don't use it if V is
 *     large (>1000ish) and the graph happens to be bipartite — use
 *     Hopcroft-Karp instead in that case.
 * TESTED ON: general (non-bipartite) maximum matching problems
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n;
vector<int> g[MAXN];
int match_[MAXN], p[MAXN], base_[MAXN];
bool used[MAXN], blossom[MAXN];

int lca(int a, int b){
    static bool used2[MAXN];
    fill(used2+1, used2+n+1, false);
    int u = a;
    while (true){ u = base_[u]; used2[u] = true; if (!match_[u]) break; u = p[match_[u]]; }
    int v = b;
    while (true){ v = base_[v]; if (used2[v]) return v; v = p[match_[v]]; }
}

void markPath(int v, int b, int child){
    while (base_[v] != b){
        blossom[base_[v]] = true;
        blossom[base_[match_[v]]] = true;
        p[v] = child;
        child = match_[v];
        v = p[match_[v]];
    }
}

int findPath(int root){
    fill(used+1, used+n+1, false);
    fill(p+1, p+n+1, 0);
    for (int i = 1; i <= n; i++) base_[i] = i;
    used[root] = true;
    queue<int> q;
    q.push(root);
    while (!q.empty()){
        int v = q.front(); q.pop();
        for (int to : g[v]){
            if (base_[v] == base_[to] || match_[v] == to) continue;
            if (to == root || (match_[to] && p[match_[to]])){
                int curbase = lca(v, to);
                fill(blossom+1, blossom+n+1, false);
                markPath(v, curbase, to);
                markPath(to, curbase, v);
                for (int i = 1; i <= n; i++)
                    if (blossom[base_[i]]){
                        base_[i] = curbase;
                        if (!used[i]) { used[i] = true; q.push(i); }
                    }
            } else if (!p[to]){
                p[to] = v;
                if (!match_[to]) return to;
                else { used[match_[to]] = true; q.push(match_[to]); }
            }
        }
    }
    return 0;
}

int maxMatching(){
    int result = 0;
    fill(match_+1, match_+n+1, 0);
    for (int v = 1; v <= n; v++){
        if (!match_[v]){
            int u = findPath(v);
            if (u){
                result++;
                int a = u, curPar;
                while (a){
                    curPar = p[a];
                    int prevMatch = match_[curPar];
                    match_[a] = curPar;
                    match_[curPar] = a;
                    a = prevMatch;
                }
            }
        }
    }
    return result;
}

/*
 * USAGE EXAMPLE:
 * n = numVertices;
 * g[u].push_back(v); g[v].push_back(u); // add undirected edges (1-indexed)
 * int matchingSize = maxMatching();
 * // match_[v] gives the matched partner of v (0 if unmatched)
 */
