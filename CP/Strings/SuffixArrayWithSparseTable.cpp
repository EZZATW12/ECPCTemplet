#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    vector<int> sa; // sa[i] starting index of i-th smallest suffix
    vector<int> lcp; // lcp[i] LCP of suffixArray[i] and suffixArray[i + 1]
    vector<int> rank; // rank[i] position of suffix starting at i in suffixArray

    // for sparse table
    int sz;
    vector<int> logs;
    vector<vector<int> > t;

    SuffixArray() {
    }

    SuffixArray(string &s) {
        sz = (int) s.size();

        // TODO
        s += ' ';
        sa = build_SuffixArray(s);

        rank.resize(s.size());
        for (int i = 0; i < s.size(); i++) {
            rank[sa[i]] = i;
        }

        lcp = build_lcp(s);

        pre_lcp();
    }

    void count_sort(vector<int> &p, vector<int> &c) {
        int n = (int) p.size();

        vector<int> cnt(n);
        for (auto &it: c) {
            cnt[it]++;
        }

        vector<int> pos(n);
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }

        vector<int> np(n);
        for (auto &it: p) {
            int i = c[it];
            np[pos[i]++] = it;
        }
        swap(p, np);
    }

    vector<int> build_SuffixArray(string &s) {
        int n = (int) s.size();

        vector<pair<char, int> > a(n);
        for (int i = 0; i < n; i++) {
            a[i] = make_pair(s[i], i);
        }
        sort(a.begin(), a.end());

        vector<int> p(n); // p[i] starting index of i-th smallest suffix
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }

        vector<int> c(n); // c[i] class of suffix starting at index i
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
        }

        int k = 0;
        while ((1 << k) < n) {
            for (int i = 0; i < n; i++) {
                p[i] = (p[i] - (1 << k) + n) % n;
            }

            count_sort(p, c);

            vector<int> nc(n);
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = make_pair(c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]);
                pair<int, int> cur = make_pair(c[p[i]], c[(p[i] + (1 << k)) % n]);
                nc[p[i]] = nc[p[i - 1]] + (cur != prev);
            }
            swap(nc, c);

            k++;
        }
        return p;
    }

    vector<int> build_lcp(string &s) {
        int n = (int) s.size(), k = 0;

        lcp.resize(n - 1);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }

            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
                k++;
            }

            lcp[rank[i]] = k;
            k = max(0, k - 1);
        }
        return lcp;
    }

    void pre_lcp() {
        int n = sz + 1;
        logs.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            logs[i] = 1 + logs[i / 2];
        }

        t.resize(logs[n] + 1, vector<int>(n));
        for (int i = 0; i < n; i++) {
            // TODO 0-based
            t[0][i] = lcp[i];
        }
        for (int p = 1; p <= logs[n]; p++) {
            for (int i = 0; i + (1 << p) <= n; i++) {
                t[p][i] = min(t[p - 1][i], t[p - 1][i + (1 << (p - 1))]);
            }
        }
    }

    // TODO l, r 0-based
    // pass r - 1 because lcp sa[i] and sa[i + 1]
    int query_lcp(int l, int r) {
        if (l == r) {
            return lcp[l];
        }

        // TODO
        // l = rank[l], r = rank[r];
        if (l > r) {
            swap(l, r);
        }

        int k = logs[r - l + 1];
        return min(t[k][l], t[k][r - (1 << k) + 1]);
    }
};
