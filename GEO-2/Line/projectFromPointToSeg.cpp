/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division for ratio)
 * Requirements: None
 */
pt projectFromPointToSeg(pt a, pt b, pt c) {
    T r = sq(a - b);
    if (sgn(r) == 0) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}
