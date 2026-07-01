/**
 * Time Complexity: O(N)
 * Floating Point: Yes (uses floating literal 1e100 and l.dist)
 * Requirements: Polygon must be convex. Points must be sorted in CCW order.
 */
// minimum distance between two parallel lines (non necessarily axis parallel)
// such that the polygon can be put between the lines
T width(const vector<pt> &p) {
    int n = (int)p.size();
    if (n <= 2) return 0;
    T ans = 1e100;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        line l(p[i], p[(i + 1) % n]);
        ans = min(ans, l.dist(p[j]));
        i++;
    }
    return ans;
}
