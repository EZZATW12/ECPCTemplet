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

/**
 * Basic half-plane struct representing region to the LEFT of directed line through point p in direction pq.
 */
struct Halfplane {
    pt p, pq;
    long double angle;

    Halfplane() {}
    Halfplane(const pt& a, const pt& b) : p(a), pq(b - a) {
        angle = atan2l(pq.Y, pq.X);
    }

    // Check if point r is outside this half-plane (to the right of directed line)
    bool out(const pt& r) const {
        return cross(pq, r - p) < -EPS;
    }

    // Comparator for polar angle sorting
    bool operator < (const Halfplane& e) const {
        return angle < e.angle;
    }

    // Intersection point of the lines of two non-parallel half-planes
    friend pt inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};

/**
 * Computes intersection of vector of half-planes H in O(N log N) time using S&I algorithm.
 * Returns vector of vertices of resulting convex polygon (or empty vector if intersection is empty).
 */
vector<pt> hp_intersect(vector<Halfplane>& H) {
    const int inf = 1e9;
    pt box[4] = {  // Bounding box in CCW order
            pt(inf, inf),
            pt(-inf, inf),
            pt(-inf, -inf),
            pt(inf, -inf)
    };

    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort by angle and start algorithm
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
