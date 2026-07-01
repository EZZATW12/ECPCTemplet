#include <bits/stdc++.h>
using namespace std;

struct sparseTable {
    int sz;
    vector<int> logs;
    vector<vector<int> > t;

    sparseTable() {
    }

    sparseTable(const vector<int> &v) {
        sz = v.size();

        logs.resize(sz + 1);
        for (int i = 2; i <= sz; i++) {
            logs[i] = 1 + logs[i / 2];
        }

        t.assign(logs[sz] + 1, vector<int>(sz));
        for (int i = 0; i < sz; i++) {
            t[0][i] = v[i];
        }
        for (int p = 1; p <= logs[sz]; p++) {
            for (int i = 0; i + (1 << p) <= sz; i++) {
                t[p][i] = min(t[p - 1][i], t[p - 1][i + (1 << (p - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        int k = logs[r - l + 1];
        //TODO
        return min(t[k][l], t[k][r - (1 << k) + 1]);
    }
};

struct SuffixArray {
    vector<int> sa; // sa[i] is the starting index of the i-th smallest suffix

    SuffixArray(const vector<int> &v) {
        vector<int> s = v;

        //TODO
        s.push_back(-1);

        sa = build_SA(s);
    }

    void radix_sort(vector<pair<pair<int, int>, int> > &a) {
        int n = a.size(); {
            vector<int> cnt(n);
            for (auto &it: a) {
                cnt[it.first.second]++;
            }

            vector<int> pos(n);
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            vector<pair<pair<int, int>, int> > na(n);
            for (auto &it: a) {
                na[pos[it.first.second]++] = it;
            }
            a = na;
        } {
            vector<int> cnt(n);
            for (auto &it: a) {
                cnt[it.first.first]++;
            }

            vector<int> pos(n);
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            vector<pair<pair<int, int>, int> > na(n);
            for (auto &it: a) {
                na[pos[it.first.first]++] = it;
            }
            a = na;
        }
    }

    vector<int> build_SA(vector<int> &s) {
        int n = s.size();

        vector<pair<int, int> > a(n);
        for (int i = 0; i < n; i++) {
            a[i] = make_pair(s[i], i);
        }
        sort(a.begin(), a.end());

        vector<int> p(n), c(n);
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }

        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }

        int k = 0;
        vector<pair<pair<int, int>, int> > na(n);
        while ((1 << k) < n) {
            for (int i = 0; i < n; i++) {
                na[i] = make_pair(make_pair(c[i], c[(i + (1 << k)) % n]), i);
            }

            radix_sort(na);

            for (int i = 0; i < n; i++) {
                p[i] = na[i].second;
            }

            c[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                c[p[i]] = c[p[i - 1]] + (na[i].first != na[i - 1].first);
            }
            k++;
        }
        return p;
    }
};

struct LCP {
    int n;
    vector<int> sa, rank, lcp;
    sparseTable st;

    LCP(vector<int> &v) {
        SuffixArray suf(v);

        sa = suf.sa;

        n = sa.size();

        rank.resize(n);
        for (int i = 0; i < n; i++) {
            rank[sa[i]] = i;
        }

        build_lcp(v);

        st = sparseTable(lcp);
    }

    void build_lcp(vector<int> &v) {
        lcp.assign(n - 1, 0);

        int k = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }

            int j = sa[rank[i] + 1];
            while (i + k < n - 1 && j + k < n - 1 && v[i + k] == v[j + k]) k++;

            lcp[rank[i]] = k;
            k = max(0, k - 1);
        }
    }

    // lcp of suffixes starting at i and j
    int query(int i, int j) {
        if (i == j) return n - 1 - i;
        int ri = rank[i], rj = rank[j];
        if (ri > rj) swap(ri, rj);
        return st.query(ri, rj - 1);
    }
};