/**
 * Time Complexity: O(log N)
 * Floating Point: Yes (uses double literals 1e100, sqrt, and segPoint)
 * Requirements: Polygon must be convex. Point must lie strictly outside the polygon.
 */
// minimum distance from a point to a convex polygon
// it assumes point lie strictly outside the polygon
T distFromPointToPolygon(const vector<pt> &p, pt z) {
    T ans = 1e100;
    int n = p.size();
    if (n <= 3) {
        for(int i = 0; i < n; i++) ans = min(ans, segPoint(p[i], p[(i + 1) % n], z));
        return ans;
    }
    auto [r, l] = tangentsFromPointToPolygon(p, z);
    if(l > r) r += n;
    while (l < r) {
        int mid = (l + r) >> 1;
        T left = sq(p[mid % n] - z), right = sq(p[(mid + 1) % n] - z);
        ans = min({ans, left, right});
        if(left < right) r = mid;
        else l = mid + 1;
    }
    ans = sqrt(ans);
    ans = min(ans, segPoint(p[l % n], p[(l + 1) % n], z));
    ans = min(ans, segPoint(p[l % n], p[(l - 1 + n) % n], z));
    return ans;
}
