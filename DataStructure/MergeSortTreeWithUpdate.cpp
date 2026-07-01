//
// Created by ezzat on 12/10/2025.
//
#include <bits/stdc++.h>

using namespace std;
struct Node {
    multiset<int> ele;
};

struct MergeSortTreeUpdate {
    int tree_sz;
    vector<Node> Seg_Data;

    MergeSortTreeUpdate(int n) {
        tree_sz = 1;
        while (tree_sz < n)tree_sz <<= 1;
        Seg_Data.assign(2 * tree_sz, Node());
    }

    Node merge(Node &li, Node &ri) {
        Node parent = Node();
        for (auto i: ri.ele)parent.ele.insert(i);
        for (auto i: li.ele)parent.ele.insert(i);
        return parent;
    }

    int get(int l, int r, int ni, int li, int ri, int k) {
        if (l <= li && r >= ri); // to do (greater than k or less than k ....)
        if (l >= ri || r <= li)
            return 0;
        int mid = (ri + li) >> 1;
        int lnode = get(l, r, ni * 2 + 1, li, mid, k);
        int rnode = get(l, r, ni * 2 + 2, mid, ri, k);
        return lnode + rnode;// todo
    }

    void update(int ni, int li, int ri, int pos, int last_val, int new_val) {
        Seg_Data[ni].ele.erase(Seg_Data[ni].ele.find(last_val));
        Seg_Data[ni].ele.insert(new_val);
        if (ri - li == 1)return;
        int mid = (li + ri) >> 1;
        if (pos < mid)
            update(ni * 2 + 1, li, mid, pos, last_val, new_val);
        else
            update(ni * 2 + 2, mid, ri, pos, last_val, new_val);
    }

    int get(int l, int r, int k) {
        return get(l, r, 0, 0, tree_sz, k);
    }

    void inti(vector<int> &v, int ni, int li, int ri) {
        if (ri - li == 1) {
            if (li < v.size())Seg_Data[ni].ele.insert(v[li]);
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
