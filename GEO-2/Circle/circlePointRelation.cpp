// 0 if outside, 1 if on circumference, 2 if inside circle
int circlePointRelation(pt p, T r, pt b) {
    T d = abs(p - b);
    if (sgn(d - r) < 0) return 2;
    if (sgn(d - r) == 0) return 1;
    return 0;
}
