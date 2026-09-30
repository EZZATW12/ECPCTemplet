//
// Created by joo on 9/29/26.
//

const int N = 1e5 + 5;

struct Node {
    Node *left, *right;
    ll sum, lazy;

    Node(ll s = 0, ll lz = 0, Node *l = nullptr, Node *r = nullptr) : sum(s), lazy(lz), left(l), right(r) {
    }
};

Node *GetL(Node *x) { return x == nullptr ? x : x->left; }
Node *GetR(Node *x) { return x == nullptr ? x : x->right; }
ll GetSum(Node *x) { return x == nullptr ? 0 : x->sum; }
ll GetLazy(Node *x) { return x == nullptr ? 0 : x->lazy; }
Node *NewNode(ll val, ll lz = 0) { return new Node(val, lz); }

Node *AddLazy(Node *x, int l, int r, ll lz) {
    return new Node(GetSum(x) + (r - l) * lz, GetLazy(x) + lz, GetL(x), GetR(x));
}

void propagate(Node *x,int l, int r) {
    assert(x != nullptr);
    if (GetLazy(x) == 0)return;
    if (l != r) {
        int mid = (l + r) / 2;
        x->left = AddLazy(GetL(x), l, mid, GetLazy(x));
        x->right = AddLazy(GetR(x), mid, r, GetLazy(x));
    }
    x->lazy = 0;
}

Node *merge(Node *l, Node *r) {
    Node *par = new Node(0);
    par->left = l, par->right = r;
    par->sum = GetSum(l) + GetSum(r);
    return par;
}

Node *build(vector<int> &v, int lx = 0, int rx = N) {
    if (rx - lx == 1)
        return NewNode(v[lx]);
    int mid = (lx + rx) / 2;
    return merge(build(v, lx, mid), build(v, mid, rx));
}

Node *update(int l,int r, ll v, Node *x, int lx = 0, int rx = N) {
    propagate(x, lx, rx);
    if (lx >= l && rx <= r)
        return AddLazy(x, lx, rx, v);
    if (lx >= r || rx <= l)return x;
    int mid = (lx + rx) / 2;
    return merge(update(l, r, v, GetL(x), lx, mid), update(l, r, v, GetR(x), mid, rx));
}

ll query(int l, int r, Node *x, int lx = 0, int rx = N) {
    propagate(x, lx, rx);
    if (lx >= l && rx <= r)
        return GetSum(x);
    if (lx >= r || rx <= l)
        return 0;
    int mid = (lx + rx) / 2;
    return query(l, r, GetL(x), lx, mid) + query(l, r, GetR(x), mid, rx);
}
