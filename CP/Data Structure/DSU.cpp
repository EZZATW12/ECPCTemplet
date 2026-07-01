#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int comp;
    vector<int> p;

    DSU(int n) {
        comp = n;
        p.resize(n + 1, -1);
    }

    int parent(int u) {
        if (p[u] < 0) return u;
        return p[u] = parent(p[u]);
    }

    void join(int u, int v) {
        int pu = parent(u), pv = parent(v);
        if (pu == pv) return;
        if (p[pu] > p[pv]) swap(pu, pv);
        p[pu] += p[pv];
        p[pv] = pu;
        comp--;
    }

    int sz(int u) {
        return -1 * p[parent(u)];
    }

    bool same(int u, int v) {
        return parent(u) == parent(v);
    }

    int count() {
        return comp;
    }
};

int main() {
    return 0;
}
