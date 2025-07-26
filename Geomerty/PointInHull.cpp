/*
 * Description: Determine whether a point t lies inside a convex hull (CCW
 * order, with no collinear points). Returns true if point lies within
 * the hull. If strict is true, points on the boundary aren't included.
*/

template<class T>
bool onSegment(T p, T s, T e) {
    return dcmp(p.cross(s, e), 0) == 0 && dcmp((s - p).dot(e - p), 0) <= 0;
}


template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double EPS) {
    auto a = (e-s).cross(p-s);
    double l = (e-s).dist()*EPS;
    return (a > l) - (a < -l);
}

template<class T>
bool inHull(const vector<T>& l, T p, bool strict = true) {
    int a = 1, b = (int)l.size() - 1, r = !strict;
    if ((int)l.size() < 3) return r && onSegment(l[0], l.back(), p);
    if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
    if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}