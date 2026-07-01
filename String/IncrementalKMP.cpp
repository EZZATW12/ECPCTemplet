//
// Created by ezzat on 4/24/2026.
//
struct IncrementalKMP {
    vector <char> s;
    vector<int> pi;
    int j;

    IncrementalKMP() : j(0) {}

    // C , PI
    int add(T c) {
        if (s.empty()) {
            s.push_back(c);
            pi.push_back(0);
            j = 0;
            return 0;
        }
        while (j > 0 && c != s[j]) {
            j = pi[j - 1];
        }
        if (c == s[j]) {
            j++;
        }
        s.push_back(c);
        pi.push_back(j);
        return j;
    }
};
struct IncrementalKMP {
    vector<char> s;
    vector<int> pi;
    int j;

    vector<array<int, 256>> memo;
    IncrementalKMP() : j(0) {}
    int add(char c) {
        if (s.empty()) {
            s.push_back(c);
            pi.push_back(0);
            j = 0;
            return 0;
        }

        while (memo.size() <= j) {
            array<int, 256> empty_row;
            empty_row.fill(-1);
            memo.push_back(empty_row);
        }
        unsigned char uc = c;
        if (memo[j][uc] != -1) {
            j = memo[j][uc];
        } else {
            int original_j = j;

            while (j > 0 && c != s[j]) {
                j = pi[j - 1];
            }
            if (c == s[j]) {
                j++;
            }
            memo[original_j][uc] = j;
        }
        s.push_back(c);
        pi.push_back(j);
        return j;
    }
};