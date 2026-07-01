// 1 if ccw, 2 if cw, 3 if on line
int pointLineRelation(pt a, pt b, pt p) {
    int c = sgn(cross(p - a, b - a));
    if (c < 0) return 1;
    if (c > 0) return 2;
    return 3;
}
