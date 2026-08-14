#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SuffixArray {
    // sa[i]   = the starting index of the i-th smallest suffix in the original string.
    // rank[i] = the position (rank) of the suffix starting at index i in the sorted suffix array.
    // lcp[i]  = the longest common prefix between the i-th and (i + 1)-th suffixes in the sorted SA (sa[i] and sa[i+1]).
    vector<int> sa, lcp, rank;

    SuffixArray(vector<int> &s) {
        // Append a distinct, strictly smallest element to mark the end of the string.
        s.push_back(0);
        int n = s.size();

        // Build the suffix array in O(N log N)
        sa = build_SuffixArray(s);

        rank.resize(n);
        lcp.resize(n - 1);

        // Compute the rank array: inverse of the suffix array
        for (int i = 0; i < sa.size(); i++) {
            rank[sa[i]] = i;
        }

        // Build the LCP array using Kasai's algorithm in O(N)
        lcp = build_lcp(s);

        // Remove the appended zero to restore the original string
        s.pop_back();
    }

    // O(N) Radix sort to sort pairs of equivalence classes
    void radix_sort(vector<pair<pair<int, int>, int>> &a) {
        int n = a.size();

        // First pass: sort by the second element of the pair
        {
            vector<int> cnt(n);
            for (auto &it: a) {
                cnt[it.first.second]++;
            }

            vector<int> pos(n);
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            vector<pair<pair<int, int>, int>> na(n);
            for (auto &it: a) {
                int i = it.first.second;
                na[pos[i]] = it;
                pos[i]++;
            }
            a = na;
        }

        // Second pass: sort by the first element of the pair
        // Since counting sort is stable, the array is now sorted by (first, second)
        {
            vector<int> cnt(n);
            for (auto &it: a) {
                cnt[it.first.first]++;
            }

            vector<int> pos(n);
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            vector<pair<pair<int, int>, int>> na(n);
            for (auto &it: a) {
                int i = it.first.first;
                na[pos[i]] = it;
                pos[i]++;
            }
            a = na;
        }
    }

    // Builds the suffix array using Prefix Doubling in O(N log N)
    vector<int> build_SuffixArray(vector<int> &s) {
        int n = s.size();
        vector<pair<int, int>> a(n);

        // Base case: sort suffixes by their first character (k = 0)
        for (int i = 0; i < n; i++) {
            a[i] = make_pair(s[i], i);
        }
        sort(a.begin(), a.end());

        vector<int> p(n); // p holds the sorted positions (the suffix array)
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }

        vector<int> c(n); // c holds the equivalence classes
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            // If the current character is identical to the previous, it belongs to the same class
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
        }

        int k = 0;
        // Loop transitions from k -> k + 1 (comparing prefixes of length 2^k)
        while ((1 << k) < n) {
            vector<pair<pair<int, int>, int>> a(n);
            for (int i = 0; i < n; i++) {
                // Pair consists of: class of first half, class of second half
                a[i] = make_pair(make_pair(c[i], c[(i + (1 << k)) % n]), i);
            }

            // Sort the pairs in O(N) using radix sort
            radix_sort(a);

            // Update the suffix array based on sorted pairs
            for (int i = 0; i < n; i++) {
                p[i] = a[i].second;
            }

            // Recalculate equivalence classes
            c[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
            }
            k++;
        }
        return p;
    }

    // Kasai's algorithm to compute the Longest Common Prefix (LCP) array in O(N)
    vector<int> build_lcp(vector<int> &s) {
        int n = s.size(), k = 0;
        for (int i = 0; i < n; i++) {
            // If it's the last suffix in the sorted SA, there is no next suffix to compare with
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }

            // j is the index of the suffix that comes directly after suffix 'i' in the sorted SA
            int j = sa[rank[i] + 1];

            // Expand the matching prefix length
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
                k++;
            }

            // lcp[rank[i]] stores the LCP between sa[rank[i]] and sa[rank[i] + 1]
            lcp[rank[i]] = k;

            // If k > 0, the next suffix in the original string will share a prefix of at least length k - 1
            k = max(0, k - 1);
        }
        return lcp;
    }
};