// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
const ld inf = 1e9;


// Basic half-plane struct.
template<class T>
struct Halfplane {

    // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
    T p, pq;
    long double angle;

    Halfplane() {}
    Halfplane(const T& a, const T& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);
    }

    // Check if point 'r' is outside this half-plane.
    // Every half-plane allows the region to the LEFT of its line.
    bool out(const T& r) {
        return dcmp(pq.cross(r - p),0) < 0;
    }

    // Comparator for sorting.
    bool operator < (const Halfplane& e) const {
        return angle < e.angle;
    }

    // Intersection point of the lines of two half-planes. It is assumed they're never parallel.
    friend T inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = (ld)(t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
        return s.p + (s.pq * alpha);
    }
};

template<class T>
vector<T> hpIntersect(vector<Halfplane<T>> H) {

    T box[4] = {  // Bounding box in CCW order
            Point(inf, inf),
            Point(-inf, inf),
            Point(-inf, -inf),
            Point(inf, -inf)
    };

    for(int i = 0; i < 4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort by angle and start algorithm
    sort(H.begin(), H.end());
    deque<Halfplane<T>> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Special case check: Parallel half-planes
        if (len > 0 && fabsl(H[i].pq.cross(dq[len-1].pq)) < eps) {
            // Opposite parallel half-planes that ended up checked against each other.
            if (dcmp(H[i].pq.dot(dq[len-1].pq),0) < 0)
                return vector<T>();

            // Same direction half-plane: keep only the leftmost half-plane.
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<T>();

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<T> ret(len);
    for(int i = 0; i < len; i++) {
        ret[i] = inter(dq[i], dq[(i+1)%len]);
    }
    return ret;
}