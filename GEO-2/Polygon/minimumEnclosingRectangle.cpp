/**
 * Time Complexity: O(N)
 * Floating Point: Yes (uses double literal 1e100, division, and l.dist)
 * Requirements: Polygon must be convex. Points must be sorted in CCW order.
 */
// minimum perimeter
T minimumEnclosingRectangle(const vector<pt> &p) {
    int n = p.size();
    if (n <= 2) return perimeter(p);
    int mndot = 0; T tmp = dot(p[1] - p[0], p[0]);
    for (int i = 1; i < n; i++) {
        if (dot(p[1] - p[0], p[i]) <= tmp) {
            tmp = dot(p[1] - p[0], p[i]);
            mndot = i;
        }
    }
    T ans = 1e100;
    int i = 0, j = 1, mxdot = 1;
    while (i < n) {
        pt cur = p[(i + 1) % n] - p[i];
        while (cross(cur, p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        while (dot(p[(mxdot + 1) % n], cur) >= dot(p[mxdot], cur)) mxdot = (mxdot + 1) % n;
        while (dot(p[(mndot + 1) % n], cur) <= dot(p[mndot], cur)) mndot = (mndot + 1) % n;
        line l(p[i], p[(i + 1) % n]);
        ans = min(ans, 2.0 * ((dot(p[mxdot], cur) / abs(cur) - dot(p[mndot], cur) / abs(cur)) + l.dist(p[j])));
        i++;
    }
    return ans;
}
