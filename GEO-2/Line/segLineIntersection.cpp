/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division)
 * Requirements: Segment and line must not be collinear.
 */
bool segLineIntersection(pt a, pt b, pt c, pt d, pt &ans) {
    int k = segLineRelation(a, b, c, d);
    assert(k != 2);
    if (k) {
        T d_val = cross(b - a, d - c);
        if (sgn(d_val) != 0) {
            ans = a + (b - a) * (cross(c - a, d - c) / d_val);
        }
    }
    return k;
}
