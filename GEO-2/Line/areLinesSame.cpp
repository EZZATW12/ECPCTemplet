/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses fabs and EPS)
 * Requirements: None
 */
bool areLinesSame(pt a, pt b, pt c, pt d) {
    if (fabs(cross(a - c, c - d)) < EPS && fabs(cross(b - c, c - d)) < EPS) return true;
    return false;
}
