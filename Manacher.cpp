void manacher(string &s,vector<int>&odd,vector<int>&even) {
    int n = s.size();
    odd.resize(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        odd[i] = (i <= r) ? (min(odd[r - i + l], r - i + 1)) : 1;
        while (i + odd[i] < n && i - odd[i] >= 0 && s[i + odd[i]] == s[i - odd[i]])
            odd[i]++;
//        ans = max(ans, 2 * odd[i] - 1);
        if (i + odd[i] - 1 > r) {
            r = i + odd[i] - 1;
            l = i - odd[i] + 1;
        }
    }
    even.resize(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        even[i] = (i <= r) ? (min(even[r - i + l + 1], r - i + 1)) : 0;
        while (i + even[i] < n && i - even[i] - 1 >= 0 && s[i + even[i]] == s[i - even[i] - 1])
            even[i]++;
//        ans = max(ans, 2 * even[i]);
        if (i + even[i] - 1 > r) {
            r = i + even[i] - 1;
            l = i - even[i];
        }
    }
}
