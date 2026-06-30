
struct line {
    pt v; T c;

    line(pt v, T c) : v(v), c(c) {}
    line(T a, T b, T _c) { v = {b, -a}; c = _c; }
    line(pt p, pt q) { v = q - p; c = cross(v, p); }

    T side(pt p) { return cross(v, p) - c; }
    T dist(pt p) { return abs(side(p)) / abs(v); }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
    line translate(pt t) { return {v, c + cross(v, t)}; }
    double sqDist(pt p) { return side(p) * side(p) / sq(v); }
    line prepThrought(pt p) { return {p, p + prep(v)}; }
    line shiftLeft(T dist) { return {v, c + dist * abs(v)}; }
    pt proj(pt p) { return p - prep(v) * side(p) / sq(v); }
    pt refl(pt p) { return p - prep(v) * (T) 2.0 * side(p) / sq(v); }
};

bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (sgn(d) == 0) return false; 
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); 
    T sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}

bool inDisk(pt a, pt b, pt p) { return sgn(dot(a - p, b - p)) <= 0; }
bool onSegment(pt a, pt b, pt p) { return sgn(orient(a, b, p)) == 0 && inDisk(a, b, p); }

bool properInter(pt a, pt b, pt c, pt d, pt &inter) {
    T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    if (oa * ob < 0 && oc * od < 0) {
        T s = oa / (oa - ob);
        inter = a + s * (b - a);
        return true;
    }
    return false;
}

T segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p); 
    }
    return min(abs(p - a), abs(p - b)); 
}

T segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy)) return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b)});
}

set<pair<T, T>> inters(pt a, pt b, pt c, pt d) {
    set<pair<T, T>> s; pt out;
    if (a == c || a == d) s.insert({a.X, a.Y});
    if (b == c || b == d) s.insert({b.X, b.Y});
    if (s.size()) return s;
    if (properInter(a, b, c, d, out)) return {{out.X, out.Y}};
    if (onSegment(c, d, a)) s.insert({a.X, a.Y});
    if (onSegment(c, d, b)) s.insert({b.X, b.Y});
    if (onSegment(a, b, c)) s.insert({c.X, c.Y});
    if (onSegment(a, b, d)) s.insert({d.X, d.Y});
    return s;
}