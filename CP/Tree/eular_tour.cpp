#include <bits/stdc++.h>
using namespace std;

int timer = 1;
vector<vector<int>> al;
vector<int> dep, tin, tout, flatten;

void euler_tour(int u, int p) {
    tin[u] = timer;
    flatten[timer++] = u;
    for (auto &v: al[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        euler_tour(v, u);
    }
    tout[u] = timer;
    flatten[timer++] = u;
}