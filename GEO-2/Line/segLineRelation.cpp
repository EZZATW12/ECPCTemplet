/**
 * Time Complexity: O(1)
 * Floating Point: No (integer safe)
 * Requirements: None
 */
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect collinear
int segLineRelation(pt a, pt b, pt c, pt d) {
    T p = orient(c, d, a);
    T q = orient(c, d, b);
    if (sgn(p) == 0 && sgn(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}
