/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses sqrt and division)
 * Requirements: None
 */
pt angleBisector(pt a, pt b, pt c) {
    pt p = a - b, q = c - b;
    return p + q * sqrt(sq(p) / sq(q));
}
