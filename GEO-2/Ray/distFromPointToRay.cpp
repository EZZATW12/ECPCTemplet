T distFromPointToRay(pt a, pt b, pt c) {
    b = a + b;
    T r = dot(c - a, b - a);
    if (r < 0.0) return abs(c - a);
    
    // distFromPointToLine equivalent
    line l(a, b);
    return l.dist(c);
}
