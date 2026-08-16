/*
 * NAME: Eertree (Palindromic Tree)
 * USE WHEN: need to count/enumerate distinct palindromic substrings,
 *           count palindromic substring occurrences, or find the
 *           longest palindromic suffix ending at each position online.
 * COMPLEXITY: O(n) build (amortized), O(n) total distinct palindromes
 * GOTCHAS:
 *   - Two roots: node 1 = length -1 (imaginary), node 2 = length 0.
 *   - `link` = longest palindromic proper suffix that is itself
 *     extendable — this is what people get wrong when reimplementing.
 *   - s[0] is a sentinel; real characters are added from index 1.
 *   - Change ALPHA/the -'a' offset if the alphabet isn't lowercase a-z.
 * TESTED ON: CF 17E, CF 906E (Reverses)
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005, ALPHA = 26;

struct Eertree {
    int len[MAXN], link[MAXN], to[MAXN][ALPHA];
    long long cnt[MAXN]; // occurrences (valid after countOccurrences())
    char s[MAXN];
    int sz, last, n;

    void init(){
        sz = 2; n = 0; last = 2;
        link[1] = 1; len[1] = -1;
        link[2] = 1; len[2] = 0;
        memset(to[1], 0, sizeof(to[1]));
        memset(to[2], 0, sizeof(to[2]));
        s[0] = -1; // sentinel
    }

    int getLink(int v){
        while (s[n - len[v] - 1] != s[n]) v = link[v];
        return v;
    }

    void add(char c){
        s[++n] = c;
        int ci = c - 'a';
        int cur = getLink(last);
        if (!to[cur][ci]){
            int now = sz++;
            len[now] = len[cur] + 2;
            if (len[now] == 1) link[now] = 2;
            else link[now] = to[getLink(link[cur])][ci];
            memset(to[now], 0, sizeof(to[now]));
            to[cur][ci] = now;
            cnt[now] = 0;
        }
        last = to[cur][ci];
        cnt[last]++;
    }

    // call after adding all chars to get true occurrence counts per node
    void countOccurrences(){
        for (int v = sz - 1; v >= 3; v--)
            cnt[link[v]] += cnt[v];
    }
} tree;

/*
 * USAGE EXAMPLE:
 * tree.init();
 * for (char c : str) tree.add(c);
 * int distinctPalindromes = tree.sz - 2;
 * tree.countOccurrences();
 * // tree.cnt[v] = number of occurrences of the palindrome ending at node v
 * // tree.len[v] = length of that palindrome
 */
