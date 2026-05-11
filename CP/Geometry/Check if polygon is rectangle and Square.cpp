#include <bits/stdc++.h>
using namespace std;

typedef int T;
typedef complex<T> pt;
#define x real()
#define y imag()

vector<pt> points(9);

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

T dist(pt v, pt w) {
    return (w.x - v.x) * (w.x - v.x) + (w.y - v.y) * (w.y - v.y);
}

bool check_rectangle(pt a, pt b, pt c, pt d) {
    pt ab = pt(a.x - b.x, a.y - b.y);
    pt bc = pt(b.x - c.x, b.y - c.y);
    pt cd = pt(c.x - d.x, c.y - d.y);
    pt da = pt(d.x - a.x, d.y - a.y);

    if (!sq(ab) || !sq(bc) || !sq(cd) || !sq(da)) {
        return false;
    }

    if (!(!dot(ab, bc) && !dot(bc, cd) && !dot(cd, da) && !dot(da, ab))) {
        return false;
    }

    return ((sq(ab) == sq(cd)) && (sq(da) == sq(bc)));
}

bool check_square(pt p1, pt p2, pt p3, pt p4) {
    set<int> st;
    st.insert(dist(p1, p2));
    st.insert(dist(p2, p3));
    st.insert(dist(p3, p4));
    st.insert(dist(p4, p1));

    return (st.size() == 1 && check_rectangle(p1, p2, p3, p4));
}
