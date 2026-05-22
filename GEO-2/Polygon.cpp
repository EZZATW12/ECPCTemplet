T areaPolygon(const vector<pt> &p) {
    T area = 0.0; int n = p.size();
    for (int i = 0; i < n; i++) area += cross(p[i], p[(i + 1) % n]); 
    return abs(area) / 2.0;
}

bool above(pt a, pt p) { return p.Y >= a.Y; }

bool crossesRay(pt a, pt p, pt q) {
    return (above(a, q) - above(a, p)) * sgn(orient(a, p, q)) > 0;
}

bool inPolygon(const vector<pt> &p, pt a, bool strict = true) {
    int numCrossings = 0; int n = p.size();
    for (int i = 0; i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a)) return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; 
}

vector<pt> convexHull(vector<pt> p) {
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    vector<pt> h(2 * n);

    sort(p.begin(), p.end(), [](pt a, pt b) {
        if (abs(a.X - b.X) > EPS) return a.X < b.X;
        return a.Y < b.Y - EPS;
    });

    for (int i = 0; i < n; ++i) {
        while (k >= 2 && sgn(orient(h[k - 2], h[k - 1], p[i])) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && sgn(orient(h[k - 2], h[k - 1], p[i])) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k - 1); 
    return h;
}

int segmentLatticePointsCount(int x1, int y1, int x2, int y2) {
    return abs(__gcd(x1 - x2, y1 - y2)) + 1;
}