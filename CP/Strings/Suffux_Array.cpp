#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    vector<int> sa; // sa[i] starting index of i-th smallest suffix
    vector<int> lcp; // lcp[i] LCP of suffixArray[i] and suffixArray[i + 1]
    vector<int> rank; // rank[i] position of suffix starting at i in suffixArray

    SuffixArray() {
    }

    SuffixArray(string &s) {
        // TODO
        s += '$';
        sa = build_SuffixArray(s);

        rank.resize(s.size());
        for (int i = 0; i < s.size(); i++) {
            rank[sa[i]] = i;
        }

        lcp = build_lcp(s);
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
} suf;

int lower_bound(vector<int> &sa, string &s, string &pat) {
    int n = (int) s.size(), l = 0, r = n - 1, ret = n;
    while (l <= r) {
        int md = (l + r) / 2;
        if (s.substr(sa[md], min((int) pat.size(), n - sa[md])) >= pat) {
            ret = md;
            r = md - 1;
        } else {
            l = md + 1;
        }
    }
    return ret;
}

int upper_bound(vector<int> &sa, string &s, string &pat) {
    int n = (int) s.size(), l = 0, r = n - 1, ret = n;
    while (l <= r) {
        int md = (l + r) / 2;
        if (s.substr(sa[md], min((int) pat.size(), n - sa[md])) > pat) {
            ret = md;
            r = md - 1;
        } else {
            l = md + 1;
        }
    }
    return ret;
}

// count the number of distinct substrings that appear in a string s
// substring is prefix of some suffix
long long cnt_distinct(string &s, vector<int> &lcp) {
    int n = (int) s.size() - 1;

    long long total = (1LL * n * (n + 1)) / 2, bad = 0;
    for (int i = 0; i < lcp.size(); i++) {
        bad += lcp[i];
    }
    return total - bad;
}

string longest_common_substring(string &s, string &t) {
    int n = s.size();

    string comb = s + '#' + t;
    int sz = comb.size();

    SuffixArray suf(comb);
    auto pos = suf.sa, lcp = suf.lcp;

    int mx = 0, idx = 0;
    for (int i = 0; i < sz; i++) {
        if ((pos[i] < n == pos[i + 1] < n)) continue; // same class
        if (lcp[i] > mx) {
            mx = lcp[i];
            idx = pos[i];
        }
    }
    return comb.substr(idx, mx);
}
