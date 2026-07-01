struct SuffixArray {
    vector<int> sa, lcp, rank;

    SuffixArray(vector<int> &s) {
        s.push_back(0);
        int n = s.size();
        sa = build_SuffixArray(s);
        rank.resize(n);
        lcp.resize(n - 1);
        for (int i = 0; i < sa.size(); i++) {
            rank[sa[i]] = i;
        }
        lcp = build_lcp(s);
        s.pop_back();
    }

    void radix_sort(vector<pair<pair < int, int>, int>> &a) {
        int n = a.size();
        {
            vector<int> cnt(n);
            for (auto &it: a) {
                cnt[it.first.second]++;
            }

            vector<int> pos(n);
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            vector < pair < pair < int, int >, int > > na(n);
            for (auto &it: a) {
                int i = it.first.second;
                na[pos[i]] = it;
                pos[i]++;
            }
            a = na;
        }

        {
            vector<int> cnt(n);
            for (auto &it: a) {
                cnt[it.first.first]++;
            }

            vector<int> pos(n);
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            vector < pair < pair < int, int >, int > > na(n);
            for (auto &it: a) {
                int i = it.first.first;
                na[pos[i]] = it;
                pos[i]++;
            }
            a = na;
        }
    }

    vector<int> build_SuffixArray(vector<int> &s) {
        int n = s.size();
        vector <pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = make_pair(s[i], i);
        }
        sort(a.begin(), a.end());

        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }

        vector<int> c(n);
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
        }

        int k = 0;
        while ((1 << k) < n) {
            vector < pair < pair < int, int >, int > > a(n);
            for (int i = 0; i < n; i++) {
                a[i] = make_pair(make_pair(c[i], c[(i + (1 << k)) % n]), i);
            }

            radix_sort(a);

            for (int i = 0; i < n; i++) {
                p[i] = a[i].second;
            }

            c[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
            }
            k++;
        }
        return p;
    }

    vector<int> build_lcp(vector<int> &s) {
        int n = s.size(), k = 0;
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
};
