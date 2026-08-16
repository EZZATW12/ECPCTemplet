#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;

const T EPS = 1e-9;
const T PI = acos(-1.0);

#define X real()
#define Y imag()

int sgn(T val) {
    return (val > EPS) - (val < -EPS);
}

T dot(pt v, pt w) { return (conj(v) * w).real(); }
T cross(pt v, pt w) { return (conj(v) * w).imag(); }
T sq(pt p) { return dot(p, p); }

T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
pt prep(pt p) { return {-p.Y, p.X}; }
pt perp(pt p) { return {-p.Y, p.X}; }

struct Halfplane {
    pt p, pq;
    long double angle;

    Halfplane() {}
    Halfplane(const pt& a, const pt& b) : p(a), pq(b - a) {
        angle = atan2l(pq.Y, pq.X);
    }

    bool out(const pt& r) const {
        return cross(pq, r - p) < -EPS;
    }

    bool operator < (const Halfplane& e) const {
        return angle < e.angle;
    }

    friend pt inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};

vector<pt> hp_intersect(vector<Halfplane>& H) {
    const int inf = 1e9;
    pt box[4] = {
            pt(inf, inf),
            pt(-inf, inf),
            pt(-inf, -inf),
            pt(inf, -inf)
    };

    for(int i = 0; i < 4; i++) {
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }
        if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < EPS) {
            if (dot(H[i].pq, dq[len-1].pq) < 0.0)
                return vector<pt>();
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }
        dq.push_back(H[i]);
        ++len;
    }

    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }
    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    if (len < 3) return vector<pt>();

    vector<pt> ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}

/**
 * Time Complexity: O(N log N * log(MAX_R / EPS))
 * Floating Point: Yes (binary search on floats, EPS, abs, perp)
 * Requirements: Polygon must be convex. Points must be sorted in CCW order.
 */
// radius of the maximum inscribed circle in a convex polygon
T maximumInscribedCircle(const vector<pt>& p) {
    int n = p.size();
    if (n <= 2) return 0;
    T l = 0, r = 20000;
    while (r - l > EPS) {
        T mid = (l + r) * 0.5;
        vector<Halfplane> h;
        const T L_val = 1e9;
        h.push_back(Halfplane(pt(-L_val, -L_val), pt(L_val, -L_val)));
        h.push_back(Halfplane(pt(L_val, -L_val), pt(L_val, L_val)));
        h.push_back(Halfplane(pt(L_val, L_val), pt(-L_val, L_val)));
        h.push_back(Halfplane(pt(-L_val, L_val), pt(-L_val, -L_val)));
        for (int i = 0; i < n; i++) {
            pt z = perp(p[(i + 1) % n] - p[i]);
            z = z / abs(z) * mid;
            h.push_back(Halfplane(p[i] + z, p[(i + 1) % n] + z));
        }
        vector<pt> nw = hp_intersect(h);
        if (!nw.empty()) l = mid;
        else r = mid;
    }
    return l;
}

