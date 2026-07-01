/**
 * Time Complexity: O(N)
 * Floating Point: No (integer-safe assuming onSegment is integer-safe)
 * Requirements: None
 */
bool isPointOnPolygon(const vector<pt> &p, const pt& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}
