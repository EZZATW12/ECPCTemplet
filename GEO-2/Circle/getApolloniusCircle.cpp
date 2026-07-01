// returns the center and radius of the circle such that for all points w on the circumference of the circle
// dist(w, a) : dist(w, b) = rp : rq
// rp != rq
// https://en.wikipedia.org/wiki/Circles_of_Apollonius
pair<pt, T> getApolloniusCircle(pt p, pt q, T rp, T rq) {
    rq *= rq;
    rp *= rp;
    T a = rq - rp;
    assert(sgn(a));
    T g = rq * p.X - rp * q.X; g /= a;
    T h = rq * p.Y - rp * q.Y; h /= a;
    T c = rq * p.X * p.X - rp * q.X * q.X + rq * p.Y * p.Y - rp * q.Y * q.Y;
    c /= a;
    pt o(g, h);
    T r = g * g + h * h - c;
    r = sqrt(r);
    return {o, r};
}
