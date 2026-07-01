/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division, sgn, abs)
 * Requirements: None
 */
// requires circleCircleInter from Circle.cpp
// returns two circle c1, c2 through points a, b and of radius r
// 0 if there is no such circle, 1 if one circle, 2 if two circle
int getCircle(pt a, pt b, T r, pt &c1, pt &c2) {
    int t = circleCircleInter(a, r, b, r, c1, c2);
    if (t == -1) t = 0; // if infinite intersections, return 0 for this context
    return t;
}

// returns two circle c1, c2 which is tangent to line u,  goes through
// point q and has radius r1; 0 for no circle, 1 if c1 = c2 , 2 if c1 != c2
int getCircle(line u, pt q, T r1, pt &c1, pt &c2) {
    T d = u.dist(q);
    if (sgn(d - r1 * 2.0) > 0) return 0;
    if (sgn(d) == 0) {
        c1 = q + perp(u.v) / abs(u.v) * r1;
        c2 = q - perp(u.v) / abs(u.v) * r1;
        return 2;
    }
    line u1 = u.shiftLeft(r1);
    line u2 = u.shiftLeft(-r1);
    pt p1_tmp, p2_tmp;
    int t = circleLineInter(q, r1, u1.v + u1.proj(pt(0,0)), u1.proj(pt(0,0)), p1_tmp, p2_tmp); // we need two points on u1
    if (!t) {
        t = circleLineInter(q, r1, u2.v + u2.proj(pt(0,0)), u2.proj(pt(0,0)), p1_tmp, p2_tmp);
    }
    c1 = p1_tmp;
    if (t == 1) {
        c2 = c1;
        return 1;
    }
    c2 = p2_tmp;
    return 2;
}
