/**
 * Time Complexity: O(N + M)
 * Floating Point: Yes (uses sqrt)
 * Requirements: Both polygons must be convex. Points must be sorted in CCW order.
 */
// maximum distance from a convex polygon to another convex polygon
T maximumDistFromPolygonToPolygon(vector<pt> u, vector<pt> v){ //O(n)
    int n = (int)u.size(), m = (int)v.size();
    T ans = 0;
    if (n < 3 || m < 3) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ans = max(ans, sq(u[i] - v[j]));
        }
        return sqrt(ans);
    }
    if (u[0].X > v[0].X) { swap(n, m); swap(u, v); }
    int i = 0, j = 0, step = n + m + 10;
    while (j + 1 < m && v[j].X < v[j + 1].X) j++;
    while (step--) {
        if (cross(u[(i + 1)%n] - u[i], v[(j + 1)%m] - v[j]) >= 0) j = (j + 1) % m;
        else i = (i + 1) % n;
        ans = max(ans, sq(u[i] - v[j]));
    }
    return sqrt(ans);
}
