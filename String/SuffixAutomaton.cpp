#include <bits/stdc++.h>

using namespace std;

// Suffix Automaton (SAM) - God Mode Black Box
// Build Time: O(N)
// Memory: O(N * ALPHABET)
template<int ALPHABET = 26, char OFFSET = 'a'>
struct SuffixAutomaton {
    struct State {
        int len;              // Length of longest string in this class
        int link;             // Suffix link
        long long cnt;        // Occurrences in original string
        long long paths;      // Distinct paths in DAG from this state (for K-th substring)
        int first_pos;        // 0-indexed end position of first occurrence
        bool terminal;        // True if suffix of original string
        array<int, ALPHABET> next;

        State() : len(0), link(-1), cnt(0), paths(0), first_pos(-1), terminal(false) {
            next.fill(-1);
        }
    };

    vector<State> st;
    int sz, last;

    SuffixAutomaton(const string &s) {
        int n = s.length();
        st.resize(max(2, 2 * n));
        sz = 1;
        last = 0;

        for (char c: s) add_char(c - OFFSET);

        for (int p = last; p != -1; p = st[p].link) st[p].terminal = true;

        preprocess_topology(n);
    }

private:
    void add_char(int c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        st[cur].first_pos = st[cur].len - 1;
        st[cur].cnt = 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        last = cur;

        if (p == -1) {
            st[cur].link = 0;
            return;
        }

        int q = st[p].next[c];
        if (st[q].len == st[p].len + 1) {
            st[cur].link = q;
            return;
        }

        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        st[clone].first_pos = st[q].first_pos; // Clone inherits first occurrence
        st[clone].cnt = 0;

        while (p != -1 && st[p].next[c] == q) {
            st[p].next[c] = clone;
            p = st[p].link;
        }

        st[q].link = st[cur].link = clone;
    }

    void preprocess_topology(int n) {
        // O(N) Topological sort by length using Counting Sort
        vector<int> order(sz);
        vector<int> count(n + 1, 0);
        for (int i = 0; i < sz; i++) count[st[i].len]++;
        for (int i = 1; i <= n; i++) count[i] += count[i - 1];
        for (int i = sz - 1; i >= 0; i--) order[--count[st[i].len]] = i;

        // 1. Calculate occurrences using Suffix Link Tree (bottom-up)
        for (int i = sz - 1; i > 0; i--) {
            int u = order[i];
            st[st[u].link].cnt += st[u].cnt;
        }

        // 2. Calculate paths using DAG transitions (bottom-up)
        for (int i = sz - 1; i >= 0; i--) {
            int u = order[i];
            st[u].paths = 1; // 1 for the path stopping exactly at this state
            for (int c = 0; c < ALPHABET; c++) {
                if (st[u].next[c] != -1) {
                    st[u].paths += st[st[u].next[c]].paths;
                }
            }
        }
    }

public:
    // --- APPLICATION 1: Substring Checks ---
    // O(|T|) - Exact occurrences
    long long count_occurrences(const string &t) {
        int cur = 0;
        for (char c: t) {
            cur = st[cur].next[c - OFFSET];
            if (cur == -1) return 0;
        }
        return st[cur].cnt;
    }

    // --- APPLICATION 2: First Occurrence Index ---
    // O(|T|) - Returns 0-indexed start position of first match, or -1
    int get_first_occurrence(const string &t) {
        int cur = 0;
        for (char c: t) {
            cur = st[cur].next[c - OFFSET];
            if (cur == -1) return -1;
        }
        return st[cur].first_pos - t.length() + 1;
    }

    // --- APPLICATION 3: Longest Common Substring (LCS) ---
    // O(|T|) - Finds the longest substring common between 's' and a new string 't'
    string longest_common_substring(const string &t) {
        int v = 0, l = 0, best_len = 0, best_pos = 0;
        for (int i = 0; i < t.length(); i++) {
            int c = t[i] - OFFSET;
            while (v > 0 && st[v].next[c] == -1) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                l++;
            }
            if (l > best_len) {
                best_len = l;
                best_pos = i;
            }
        }
        if (best_len == 0) return "";
        return t.substr(best_pos - best_len + 1, best_len);
    }

    // --- APPLICATION 4: Lexicographically K-th  Substring ---
    // --- Lexicographically K-th Substring ---
    // is_distinct = true  -> ignores duplicate occurrences (T = 0)
    // is_distinct = false -> counts all occurrences (T = 1)
    string kth_substring(long long k, bool is_distinct = true) {
        // Total valid substrings from root (excluding empty string)
        long long total = is_distinct ? st[0].paths_distinct - 1 : st[0].paths_all - st[0].cnt;
        if (k > total || k <= 0) return "";

        string res = "";
        int cur = 0;

        while (k > 0) {
            for (int c = 0; c < ALPHABET; c++) {
                int nxt = st[cur].next[c];
                if (nxt != -1) {
                    long long branches = is_distinct ? st[nxt].paths_distinct : st[nxt].paths_all;

                    if (k <= branches) {
                        res += (char) (c + OFFSET);
                        // Consume the strings that stop exactly at state 'nxt'
                        long long consume = is_distinct ? 1 : st[nxt].cnt;
                        k -= consume;
                        cur = nxt;
                        break;
                    } else {
                        // Skip all strings starting with this character
                        k -= branches;
                    }
                }
            }
        }
        return res;
    }


    // --- APPLICATION 5: Distinct Substring Math ---
    // O(1) - Total distinct substrings
    long long count_distinct_substrings() {
        return st[0].paths - 1; // Subtract 1 to exclude the empty string
    }
};