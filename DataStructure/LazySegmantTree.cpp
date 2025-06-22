//
// Created by Ezzat on 6/2/2025.
//
struct Node {
    ll val, lazy;
    bool is_lazy;

    Node(int x = 0) {
        val = x;
        lazy = is_lazy = 0;
    }

    void change(ll x, int li, int ri) {
        val += x * (ri - li);
        lazy += x;
        is_lazy = 1;
    }
};

struct SegTreeLazy {
    int tree_sz;
    vector <Node> Seg_Data;

    SegTreeLazy(int n) {
        tree_sz = 1;
        while (tree_sz < n)tree_sz <<= 1;
        Seg_Data.assign(2 * tree_sz, Node());
    }

    Node merge(Node &li, Node &ri) {
        Node parent = Node();
        parent.val = li.val + ri.val;
        return parent;
    }

    void propagate(int ni, int li, int ri) {
        if (!Seg_Data[ni].is_lazy or ri - li == 1)return;
        int mid = (li + ri) >> 1;
        Seg_Data[(ni << 1) + 1].change(Seg_Data[ni].lazy, li, mid);
        Seg_Data[(ni << 1) + 2].change(Seg_Data[ni].lazy, mid, ri);
        Seg_Data[ni].lazy = 0;
        Seg_Data[ni].is_lazy = 0;
    }

    void update(int l, int r, ll val, int ni, int li, int ri) {
        propagate(ni, li, ri);
        if (li >= l && ri <= r) {
            Seg_Data[ni].change(val, li, ri);
            return;
        }
        if (ri <= l || li >= r)
            return;
        int mid = (li + ri) >> 1;
        update(l, r, val, ni * 2 + 1, li, mid);
        update(l, r, val, ni * 2 + 2, mid, ri);
        Seg_Data[ni] = merge(Seg_Data[ni * 2 + 1], Seg_Data[ni * 2 + 2]);
    }

    void update(int l, int r, ll val) {
        update(l, r, val, 0, 0, tree_sz);
    }

    Node query(int l, int r, int ni, int li, int ri) {
        propagate(ni, li, ri);
        if (l <= li && r >= ri)
            return Seg_Data[ni];
        if (l >= ri || r <= li)
            return Node();
        int mid = (ri + li) >> 1;
        Node lnode = query(l, r, ni * 2 + 1, li, mid);
        Node rnode = query(l, r, ni * 2 + 2, mid, ri);
        return merge(lnode, rnode);
    }

    ll query(int l, int r) { // note r not included
        return query(l, r, 0, 0, tree_sz).val;
    }
};