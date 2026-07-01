/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses abs, fabs, sgn)
 * Requirements: None
 */
//5 - outside and do not intersect
//4 - intersect outside in one point
//3 - intersect in 2 points
//2 - intersect inside in one point
//1 - inside and do not intersect
int circleCircleRelation(pt a, T r, pt b, T R) {
    T d = abs(a - b);
    if (sgn(d - r - R) > 0)  return 5;
    if (sgn(d - r - R) == 0) return 4;
    T l = fabs(r - R);
    if (sgn(d - r - R) < 0 && sgn(d - l) > 0) return 3;
    if (sgn(d - l) == 0) return 2;
    if (sgn(d - l) < 0) return 1;
    assert(0); return -1;
}
