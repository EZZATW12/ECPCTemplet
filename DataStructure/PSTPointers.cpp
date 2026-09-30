//
// Created by joo on 9/29/26.
//
const int N = 1e5 + 5;

struct Node {
    Node *left, *right;
    ll sum;

    Node(ll s = 0, Node *l = nullptr, Node *r = nullptr) : sum(s), left(l), right(r) {
    }
};

Node *GetL(Node *x) { return x == nullptr ? x : x->left; }
Node *GetR(Node *x) { return x == nullptr ? x : x->right; }
ll GetSum(Node *x) { return x == nullptr ? 0 : x->sum; }
Node *NewNode(ll val) { return new Node(val); }

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

Node *update(int i, int v, Node *x, int l = 0, int r = N) {
    if (r - l == 1)
        return NewNode(v + GetSum(x));
    int mid = (l + r) / 2;
    if (i < mid) {
        return merge(update(i, v, GetL(x), l, mid), GetR(x));
    }
    return merge(GetL(x), update(i, v, GetR(x), mid, r));
}

ll query(int l, int r, Node *x, Node *y, int lx = 0, int rx = N) {
    if (lx >= l && rx <= r)
        return GetSum(y) - GetSum(x);
    if (lx >= r || rx <= l)
        return 0;
    int mid = (lx + rx) / 2;
    return query(l, r, GetL(x), GetL(y), lx, mid) + query(l, r, GetR(x), GetR(y), mid, rx);
}

ll kth(int k, Node *x, Node *y, int lx = 0, int rx = N) {
    if (rx - lx == 1)
        return lx;
    int mid = (lx + rx) / 2;
    int sum = GetSum(GetL(y)) - GetSum(GetL(x));
    if (k > sum) {
        k -= sum;
        return kth(k, GetR(x), GetR(y), mid, rx);
    }
    return kth(k, GetL(x), GetL(y), lx, mid);
}
