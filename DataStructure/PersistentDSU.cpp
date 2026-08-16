/*
 * NAME: Persistent DSU (persistent array over union-by-size)
 * USE WHEN: need to answer "were u and v connected at version t" for
 *           ARBITRARY versions/times, not just LIFO undo — e.g. offline
 *           queries mixed with unions across a timeline, or binary
 *           searching over time for when two nodes first connected.
 * COMPLEXITY: O(log^2 n) per find/union (no path compression allowed —
 *             it would silently corrupt older versions), O(log n)
 *             memory allocated per union call
 * GOTCHAS:
 *   - NEVER path-compress; union by size only, or persistence breaks.
 *   - Every union() call returns a NEW version index; old versions stay
 *     valid and queryable forever — this is the whole point.
 *   - Heavier than plain rollback DSU (which you likely already have) —
 *     only reach for this when you need random access to old versions,
 *     not just "undo the last k operations".
 *   - Bump the pool size if you have many unions; each union allocates
 *     roughly O(log n) new nodes for the parent array and O(log n) more
 *     for the size array.
 * TESTED ON: offline dynamic connectivity requiring persistence/versioning
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
struct Node { int val; Node *l, *r; };
Node pool[MAXN * 40];
int poolPtr = 0;
Node* newNode(int val, Node* l, Node* r){
    Node* nd = &pool[poolPtr++];
    nd->val = val; nd->l = l; nd->r = r;
    return nd;
}
Node* buildVal(int l, int r, int val){
    if (l == r) return newNode(val, nullptr, nullptr);
    int m = (l+r)/2;
    return newNode(0, buildVal(l,m,val), buildVal(m+1,r,val));
}
Node* buildIdentity(int l, int r){ // parent[i] = i
    if (l == r) return newNode(l, nullptr, nullptr);
    int m = (l+r)/2;
    return newNode(0, buildIdentity(l,m), buildIdentity(m+1,r));
}
int get(Node* nd, int l, int r, int idx){
    if (l == r) return nd->val;
    int m = (l+r)/2;
    return idx <= m ? get(nd->l, l, m, idx) : get(nd->r, m+1, r, idx);
}
Node* set_(Node* nd, int l, int r, int idx, int val){
    if (l == r) return newNode(val, nullptr, nullptr);
    int m = (l+r)/2;
    if (idx <= m) return newNode(0, set_(nd->l, l, m, idx, val), nd->r);
    else return newNode(0, nd->l, set_(nd->r, m+1, r, idx, val));
}

int n;
vector<Node*> parVer, szVer; // parallel version lists

int findAt(int version, int x){
    while (true){
        int p = get(parVer[version], 1, n, x);
        if (p == x) return x;
        x = p;
    }
}

// unites x,y as of `version`; returns the NEW version index
int unite(int version, int x, int y){
    int rx = findAt(version, x), ry = findAt(version, y);
    if (rx == ry){ parVer.push_back(parVer[version]); szVer.push_back(szVer[version]); return parVer.size()-1; }
    int sx = get(szVer[version], 1, n, rx);
    int sy = get(szVer[version], 1, n, ry);
    if (sx < sy) swap(rx, ry);
    Node* newPar = set_(parVer[version], 1, n, ry, rx);
    Node* newSz = set_(szVer[version], 1, n, rx, sx + sy);
    parVer.push_back(newPar);
    szVer.push_back(newSz);
    return parVer.size()-1;
}

void init(int n_){
    n = n_;
    parVer.push_back(buildIdentity(1, n));
    szVer.push_back(buildVal(1, n, 1));
}

/*
 * USAGE EXAMPLE:
 * init(n);                          // version 0 = all singletons
 * int v1 = unite(0, 3, 5);          // build version 1 on top of version 0
 * int v2 = unite(v1, 2, 3);         // build version 2 on top of version 1
 * bool c1 = (findAt(v1, 3) == findAt(v1, 2)); // query version 1 -> false
 * bool c2 = (findAt(v2, 3) == findAt(v2, 2)); // query version 2 -> true
 */
