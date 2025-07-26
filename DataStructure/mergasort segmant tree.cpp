struct Node {
    vector<int> ele;
};

struct SegTree {
    int tree_sz;
    vector<Node> Seg_Data;

    SegTree(int n) {
        tree_sz = 1;
        while (tree_sz < n)tree_sz <<= 1; // the nearst pow 2 greater than or eql n
        Seg_Data.assign(2 * tree_sz, Node());
    }

    // can change to  (min,max,gcd,lcm......)
    Node merge(Node &li, Node &ri) {
        Node parent = Node();
        std::merge(li.ele.begin(), li.ele.end(), ri.ele.begin(), ri.ele.end(), back_inserter(parent.ele));
        return parent;
    }

    void set(int idx, ll val, int ni, int li, int ri) {
        if (ri - li == 1) {
            Seg_Data[ni].ele.push_back(val);
            return;
        }
        int mid = (li + ri) >> 1;
        if (idx < mid)
            set(idx, val, 2 * ni + 1, li, mid);
        else
            set(idx, val, 2 * ni + 2, mid, ri);
        Seg_Data[ni] = merge(Seg_Data[2 * ni + 1], Seg_Data[2 * ni + 2]);
    }

    void set(int idx, ll val) {
        set(idx, val, 0, 0, tree_sz);
    }

    ll get(int l, int r, int ni, int li, int ri, int k) {
        if (l <= li && r >= ri)
            return (upper_bound(Seg_Data[ni].ele.begin(), Seg_Data[ni].ele.end(), k) - Seg_Data[ni].ele.begin());
        if (l >= ri || r <= li)
            return 0;
        int mid = (ri + li) >> 1;
        ll lnode = get(l, r, ni * 2 + 1, li, mid, k);
        ll rnode = get(l, r, ni * 2 + 2, mid, ri, k);
        return lnode + rnode;
    }

    ll get(int l, int r, int k) {
        return get(l, r, 0, 0, tree_sz, k);
    }

    void inti(vector<int> &v, int ni, int li, int ri) {
        if (ri - li == 1) {
            if (li < v.size())Seg_Data[ni].ele.push_back(v[li]);
            return;
        }
        int mid = (li + ri) >> 1;
        inti(v, 2 * ni + 1, li, mid);
        inti(v, 2 * ni + 2, mid, ri);
        Seg_Data[ni] = merge(Seg_Data[ni * 2 + 1], Seg_Data[ni * 2 + 2]);
    }

    void inti(vector<int> &v) {
        inti(v, 0, 0, tree_sz);
    }
};
