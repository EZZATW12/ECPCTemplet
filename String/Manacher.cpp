#include <bits/stdc++.h>
using namespace std;

// Manacher's Algorithm - Ultimate Black Box
// Build Time: O(N)
struct Manacher {
    int n;
    string s;
    vector<int> odd, even;

    Manacher(const string& str) : s(str), n(str.size()) {
        odd.assign(n, 0);
        even.assign(n, 0);

        for (int i = 0, l = 0, r = -1; i < n; i++) {
            odd[i] = (i <= r) ? min(odd[r - i + l], r - i + 1) : 1;
            while (i + odd[i] < n && i - odd[i] >= 0 && s[i + odd[i]] == s[i - odd[i]]) odd[i]++;
            if (i + odd[i] - 1 > r) {
                r = i + odd[i] - 1;
                l = i - odd[i] + 1;
            }
        }

        for (int i = 0, l = 0, r = -1; i < n; i++) {
            even[i] = (i <= r) ? min(even[r - i + l + 1], r - i + 1) : 0;
            while (i + even[i] < n && i - even[i] - 1 >= 0 && s[i + even[i]] == s[i - even[i] - 1]) even[i]++;
            if (i + even[i] - 1 > r) {
                r = i + even[i] - 1;
                l = i - even[i];
            }
        }
    }

    // Application 1: O(1) Range Query
    // Checks if the substring s[l...r] (0-indexed, inclusive) is a palindrome.
    bool is_palindrome(int l, int r) {
        if (l > r) return false;
        int len = r - l + 1;
        if (len % 2 != 0) {
            return (2 * odd[(l + r) / 2] - 1) >= len;
        } else {
            return (2 * even[(l + r + 1) / 2]) >= len;
        }
    }

    // Application 2: O(N) Count Total Palindromes
    // Returns the total number of palindromic substrings.
    long long count_palindromes() {
        long long total = 0;
        for (int x : odd) total += x;
        for (int x : even) total += x;
        return total;
    }

    // Application 3: O(N) Longest Palindromic Substring Length
    // Returns the length of the longest palindrome in the string.
    int max_palindrome_length() {
        int max_len = 0;
        for (int i = 0; i < n; i++) {
            max_len = max(max_len, 2 * odd[i] - 1);
            max_len = max(max_len, 2 * even[i]);
        }
        return max_len;
    }

    // Application 4: O(N) Get Longest Palindromic Substring
    // Returns the actual string of the longest palindrome.
    string get_longest_palindrome() {
        int max_len = 0, start_idx = 0;
        for (int i = 0; i < n; i++) {
            if (2 * odd[i] - 1 > max_len) {
                max_len = 2 * odd[i] - 1;
                start_idx = i - odd[i] + 1;
            }
            if (2 * even[i] > max_len) {
                max_len = 2 * even[i];
                start_idx = i - even[i];
            }
        }
        return s.substr(start_idx, max_len);
    }

    // Application 5: O(N) Longest Palindromic Prefix Length
    // Useful for finding shortest string to append to make 's' a palindrome.
    int longest_palindromic_prefix() {
        for (int len = n; len >= 1; --len) {
            if (is_palindrome(0, len - 1)) return len;
        }
        return 0;
    }

    // Application 6: O(N) Longest Palindromic Suffix Length
    // Useful for finding shortest string to prepend to make 's' a palindrome.
    int longest_palindromic_suffix() {
        for (int len = n; len >= 1; --len) {
            if (is_palindrome(n - len, n - 1)) return len;
        }
        return 0;
    }
};