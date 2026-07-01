/**
 * Time Complexity: O(N^3)
 * Floating Point: No (integer-safe; relies on orient and isPointInTriangle)
 * Requirements: None
 */
// ear decomposition, O(n^3) but faster
vector<vector<pt>> triangulate(vector<pt> p) {
    vector<vector<pt>> v;
    while (p.size() >= 3) {
        for (int i = 0, n = p.size(); i < n; i++) {
            int pre = i == 0 ? n - 1 : i - 1;
            int nxt = i == n - 1 ? 0 : i + 1;
            int ori = sgn(orient(p[pre], p[i], p[nxt])); 
            if (ori < 0) { 
                int ok = 1;
                for (int j = 0; j < n; j++) {
                    if (j == i || j == pre || j == nxt) continue;
                    if (isPointInTriangle(p[pre], p[i], p[nxt], p[j]) < 1) { 
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    v.push_back({p[pre], p[i], p[nxt]});
                    p.erase(p.begin() + i);
                    break;
                }
            }
        }
    }
    return v;
}
