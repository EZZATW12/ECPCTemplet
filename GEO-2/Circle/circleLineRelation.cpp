// 0 if outside, 1 if on circumference, 2 if inside circle
int circleLineRelation(pt p, T r, pt a, pt b) {
    line l(a, b);
    T d = l.dist(p);
    if (sgn(d - r) < 0) return 2;
    if (sgn(d - r) == 0) return 1;
    return 0;
}
