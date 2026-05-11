#include <bits/stdc++.h>
using namespace std;

// pi[i] is the length of the longest proper prefix of the substring s[0...i] which is also a suffix of this substring.
// A proper prefix of a string is a prefix that is not equal to the string itself

// we can get all porder for string by

// int k = lps.back();
// while (k > 0) {
//    porders.push_back(k);
//    k = pi[k - 1];
// }

// if len of string is len n, and porder is len k, the period is n - k

vector<int> prefix_function(string &s) {
    int n = (int) s.size();
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

int kmp(string &s, string &p) {
    int n = s.size(), m = p.size(), cnt = 0;
    if (m > n) return 0;
    vector<int> pi = prefix_function(p);
    for (int i = 0, j = 0; i < n;) {
        if (s[i] == p[j]) {
            i++, j++;
            if (j == m) {
                cnt++;
                j = pi[j - 1];
            }
        } else if (!j) {
            i++;
        } else {
            j = pi[j - 1];
        }
    }
    return cnt;
}
