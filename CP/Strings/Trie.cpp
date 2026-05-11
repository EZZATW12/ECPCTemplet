#include <bits/stdc++.h>
using namespace std;

struct node {
    map<char, int> nxt;

    int &operator[](char c) {
        return nxt[c];
    }
};

struct trie {
    vector<node> t;

    int new_node() {
        t.push_back(node());
        return t.size() - 1;
    }

    trie() {
        t.clear();
        new_node();
    }

    void insert(string &s) {
        int u = 0;
        for (auto &c: s) {
            if (!t[u].nxt.count(c)) { // to avoid memory limit
                int id = new_node();
                t[u][c] = id;
            }
            u = t[u][c];
        }
    }
};
