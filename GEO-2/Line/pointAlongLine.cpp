/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division and point absolute value)
 * Requirements: Points a and b must be distinct.
 */
pt pointAlongLine(pt a, pt b, T d) {
    assert(a != b);
    return a + (((b - a) / abs(b - a)) * d);
}
