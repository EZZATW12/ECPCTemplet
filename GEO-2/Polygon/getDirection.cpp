/**
 * Time Complexity: O(N)
 * Floating Point: No (strictly integer-safe operations like cross product and sgn)
 * Requirements: None
 */
// 0 if cw, 1 if ccw
bool getDirection(const vector<pt> &p) {
    T ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    if (sgn(ans) > 0) return 1;
    return 0;
}
