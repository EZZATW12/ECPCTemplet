#include <bits/stdc++.h>
using namespace std;

vector<int> par;
vector<vector<int> > al;
int diameter, farthest, start, endd;

void dfs(int u, int p, int d) {
    par[u] = p;

    if (d > diameter) {
        farthest = u;
        diameter = d;
    } else if (d == diameter) {
        farthest = max(farthest, u);
    }

    for (auto v: al[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
    }
}

void find_diameter(int u) {
    diameter = -1;
    farthest = u;
    dfs(farthest, -1, 0);
    start = farthest;

    diameter = -1;
    farthest = start;
    dfs(farthest, -1, 0);
    endd = farthest;
}
