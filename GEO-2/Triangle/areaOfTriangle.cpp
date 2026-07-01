/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses multiplication by 0.5 and fabs)
 * Requirements: None
 */
T areaOfTriangle(pt a, pt b, pt c) {
    return fabs(cross(b - a, c - a) * 0.5);
}
