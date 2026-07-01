/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses fabs and EPS)
 * Requirements: None
 */
// 0 if not parallel, 1 if parallel, 2 if collinear
int isParallel(pt a, pt b, pt c, pt d) {
    T k = fabs(cross(b - a, d - c));
    if (k < EPS) {
        if (fabs(cross(a - b, a - c)) < EPS && fabs(cross(c - d, c - a)) < EPS) return 2;
        else return 1;
    }
    else return 0;
}
