/*
 * NAME: Block Cut Tree
 * USE WHEN: problem needs the structure of biconnected components and
 *           how they connect through articulation points — e.g. "count
 *           paths that don't pass through a cut vertex", or reducing a
 *           graph to a tree to run tree DP/queries on 2-vertex-connectivity
 *           structure.
 * COMPLEXITY: O(n + m)
 * GOTCHAS:
 *   - Fill g[u] with undirected edges BEFORE calling dfs.
 *   - New tree has original vertices (1..n) PLUS one new node per
 *     biconnected component (component nodes start at n+1).
 *   - A non-articulation vertex belongs to exactly one component node.
 *   - An articulation point can belong to multiple component nodes —
 *     it's the hub connecting them, which is why the result is a tree.
 *   - Call dfs once per unvisited vertex to handle disconnected graphs.
 * TESTED ON: standard articulation-point / BCC decomposition problems
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

vector<int> g[MAXN], tree[MAXN];
int disc[MAXN], low[MAXN], timer_ = 0;
int n, m, compCnt;
bool isArt[MAXN];
stack<pair<int,int>> edgeStack;

void addComponent(vector<pair<int,int>>& compEdges){
    compCnt++;
    int comp = compCnt;
    set<int> nodes;
    for (auto& e : compEdges){ nodes.insert(e.first); nodes.insert(e.second); }
    for (int v : nodes){ tree[comp].push_back(v); tree[v].push_back(comp); }
}

void dfs(int u, int p){
    disc[u] = low[u] = ++timer_;
    int children = 0;
    for (int v : g[u]){
        if (v == p) continue;
        if (!disc[v]){
            children++;
            edgeStack.push({u, v});
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= disc[u]){
                if (p != -1 || children > 1) isArt[u] = true;
                vector<pair<int,int>> comp;
                while (edgeStack.top() != make_pair(u, v)){
                    comp.push_back(edgeStack.top());
                    edgeStack.pop();
                }
                comp.push_back(edgeStack.top());
                edgeStack.pop();
                addComponent(comp);
            }
        } else if (disc[v] < disc[u]){
            edgeStack.push({u, v});
            low[u] = min(low[u], disc[v]);
        }
    }
}

/*
 * USAGE EXAMPLE:
 * g[u].push_back(v); g[v].push_back(u); // add all undirected edges first
 * compCnt = n;
 * for (int i = 1; i <= n; i++) if (!disc[i]) dfs(i, -1);
 * // `tree` now holds the block-cut tree over nodes [1..compCnt]
 * // original articulation points are marked isArt[u] == true
 */
