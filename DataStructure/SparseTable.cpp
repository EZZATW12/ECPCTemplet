//
// Created by Ezzat on 6/2/2025.
//

template<typename T, class FUN>
struct sparseTable {
    vector<vector<long long>> sp;
    FUN calc;

    explicit sparseTable(vector<T> &a, FUN calc) : calc(calc) {
        int n = (int) a.size(), max_log = 32 - __builtin_clz(n);
        sp = vector<vector<long long >>(n, vector<long long>(max_log));
        for (int i = 0; i < n; i++) sp[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                sp[i][j] = calc(sp[i][j - 1], sp[i + (1 << (j - 1))][j - 1]);
    }

    long long query(int l, int r) {
        int len = r - l + 1;
        int j = 31 - __builtin_clz(len);
        return calc(sp[l][j], sp[r - (1 << j) + 1][j]);
    }
};