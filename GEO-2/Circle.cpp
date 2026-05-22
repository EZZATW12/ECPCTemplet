
pt proj(pt a, pt b, pt p) {
    pt v = b - a;
    return a + v * dot(v, p - a) / sq(v);
}

int circleLineInter(pt c, T r, pt a, pt b, pt &p1, pt &p2) {
    pt p = proj(a, b, c); 
    T d = abs(p - c); 

    if (sgn(d - r) > 0) return 0; 
    if (sgn(d - r) == 0) { p1 = p2 = p; return 1; }

    T offset = sqrt(max((T) 0.0, r * r - d * d));
    pt v = (b - a) / abs(b - a); 

    p1 = p + v * offset;
    p2 = p - v * offset;
    return 2;
}

int circleCircleInter(pt c1, T r1, pt c2, T r2, pt &p1, pt &p2) {
    T d = abs(c2 - c1);

    if (sgn(d - (r1 + r2)) > 0 || sgn(d - abs(r1 - r2)) < 0) return 0;
    if (sgn(d) == 0 && sgn(r1 - r2) == 0) return -1;

    T a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    T h = sqrt(max((T) 0.0, r1 * r1 - a * a));
    pt p = c1 + (c2 - c1) * (a / d);
    pt perpP = perp(c2 - c1) * (h / d);

    p1 = p + perpP;
    p2 = p - perpP;

    return sgn(h) == 0 ? 1 : 2;
}