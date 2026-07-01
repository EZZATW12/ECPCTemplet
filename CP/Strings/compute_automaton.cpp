#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n;) {
        if (s[i] == s[j]) {
            pi[i] = ++j;
            i++;
        } else if (!j) {
            i++;
        } else {
            j = pi[j - 1];
        }
    }
    return pi;
}

vector<vector<int> > compute_automaton(string &s) {
    int n = s.size();
    auto pi = prefix_function(s);
    vector<vector<int> > aut(n, vector<int>(26));
    for (int len = 0; len < n; len++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (s[len] == c) {
                aut[len][c - 'a'] = len + 1;
            } else {
                aut[len][c - 'a'] = (len > 0 ? aut[pi[len - 1]][c - 'a'] : 0);
            }
        }
    }
    return aut;
}
