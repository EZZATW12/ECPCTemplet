#include <bits/stdc++.h>
using namespace std;

// the length of the union of intervals (how much they cover in total, without double-counting overlaps).
// [1, 5], [3, 7], [10, 12]
// [1 -------- 5]
//       [3 -------- 7]     [10 -- 12]
// [1 -------- 7]   [10 -- 12]
// so the total covered length is (7 - 1) + (12 - 10) = 8

int length_union(vector<pair<int, int> > &a) {
    int n = (int) a.size();
    vector<pair<int, bool> > v(2 * n);
    for (int i = 0; i < n; i++) {
        v[2 * i] = make_pair(a[i].first, false); // start
        v[2 * i + 1] = make_pair(a[i].second, true); // end
    }
    sort(v.begin(), v.end());

    int len = 0, cnt_open = 0;
    for (int i = 0; i < n * 2; i++) {
        if (i > 0 && v[i].first > v[i - 1].first && cnt_open > 0) {
            len += v[i].first - v[i - 1].first;
        }
        cnt_open += (v[i].second ? -1 : 1);
    }
    return len;
}
