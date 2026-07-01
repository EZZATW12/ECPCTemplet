bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = sgn(orient(a, b, c));
    return o < 0 || (include_collinear && o == 0);
}

bool collinear(pt a, pt b, pt c) { return sgn(orient(a, b, c)) == 0; }

void convex_hull(vector <pt> &a, bool include_collinear = false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt &a, const pt &b) {
        int o = sgn(orient(p0, a, b));
        if (o == 0)
            return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y)
                   < (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int) a.size() - 1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin() + i + 1, a.end());
    }

    vector <pt> st;
    for (int i = 0; i < (int) a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size() - 2], st.back(), a[i], include_collinear))
            st.pop_back();
        if (st.empty() || a[i] != st.back())
            st.push_back(a[i]);
    }

    if (include_collinear == false && st.size() == 2 && st[0] == st[1])
        st.pop_back();

    a = st;
}

T cross(pt o, pt a, pt b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

T sq(pt p) { // get squere of vector
    return p.x * p.x + p.y * p.y;
}

void ConvexHull(vector<pt> &pts) {
    // remove duplicate
    // return ccw
    sort(pts.begin(), pts.end(), [](const pt &a, const pt &b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });

    pts.erase(unique(pts.begin(), pts.end(), [](const pt &a, const pt &b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());

    int n = (int) pts.size();
    if (n < 2) return;

    vector<pt> lower;
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 && cross(lower[(int) lower.size() - 2], lower.back(), pts[i]) <= 0) {
            lower.pop_back();
        }
        lower.push_back(pts[i]);
    }

    vector<pt> upper;
    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2 && cross(upper[(int) upper.size() - 2], upper.back(), pts[i]) <= 0) {
            upper.pop_back();
        }
        upper.push_back(pts[i]);
    }

    lower.pop_back();
    upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());
    pts = lower;
}