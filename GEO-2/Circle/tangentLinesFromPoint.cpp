// tangent lines from point q to the circle
int tangentLinesFromPoint(pt p, T r, pt q, line &u, line &v) {
    int x = sgn(sq(p - q) - r * r);
    if (x < 0) return 0; // point in circle
    if (x == 0) { // point on circle
        u = line(q, q + perp(q - p));
        v = u;
        return 1;
    }
    T d = abs(p - q);
    T l = r * r / d;
    T h = sqrt(r * r - l * l);
    u = line(q, p + (((q - p) / d * l) + (perp(q - p) / d * h)));
    v = line(q, p + (((q - p) / d * l) + (-perp(q - p) / d * h)));
    return 2;
}
