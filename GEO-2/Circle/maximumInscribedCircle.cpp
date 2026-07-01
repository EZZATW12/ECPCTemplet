/**
 * Time Complexity: O(N log N * log(MAX_R / EPS))
 * Floating Point: Yes (binary search on floats, EPS, abs, perp)
 * Requirements: Polygon must be convex. Points must be sorted in CCW order.
 */
// radius of the maximum inscribed circle in a convex polygon
T maximumInscribedCircle(const vector<pt>& p) {
    int n = p.size();
    if (n <= 2) return 0;
    T l = 0, r = 20000;
    while (r - l > EPS) {
        T mid = (l + r) * 0.5;
        vector<Halfplane> h;
        const T L_val = 1e9;
        h.push_back(Halfplane(pt(-L_val, -L_val), pt(L_val, -L_val)));
        h.push_back(Halfplane(pt(L_val, -L_val), pt(L_val, L_val)));
        h.push_back(Halfplane(pt(L_val, L_val), pt(-L_val, L_val)));
        h.push_back(Halfplane(pt(-L_val, L_val), pt(-L_val, -L_val)));
        for (int i = 0; i < n; i++) {
            pt z = perp(p[(i + 1) % n] - p[i]);
            z = z / abs(z) * mid;
            h.push_back(Halfplane(p[i] + z, p[(i + 1) % n] + z));
        }
        vector<pt> nw = hp_intersect(h);
        if (!nw.empty()) l = mid;
        else r = mid;
    }
    return l;
}
