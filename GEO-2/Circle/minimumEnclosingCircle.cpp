// given n points, find the minimum enclosing circle of the points
// call convex_hull() before this for faster solution
// expected O(n)
pair<pt, T> minimumEnclosingCircle(vector<pt> &p) {
    random_shuffle(p.begin(), p.end());
    int n = p.size();
    pt c = p[0];
    T r = 0;
    for (int i = 1; i < n; i++) {
        if (sgn(abs(c - p[i]) - r) > 0) {
            c = p[i];
            r = 0;
            for (int j = 0; j < i; j++) {
                if (sgn(abs(c - p[j]) - r) > 0) {
                    c = (p[i] + p[j]) / (T)2.0;
                    r = abs(p[i] - p[j]) / 2.0;
                    for (int k = 0; k < j; k++) {
                        if (sgn(abs(c - p[k]) - r) > 0) {
                            pt temp1, temp2;
                            circleCircleInter(p[i], r, p[j], r, temp1, temp2); // this would be getCircle
                            // wait, circumcircle of triangle is easier
                            pt b = (p[i] + p[j]) / (T)2.0;
                            pt c_mid = (p[i] + p[k]) / (T)2.0;
                            line l1(b, b + perp(p[i] - p[j]));
                            line l2(c_mid, c_mid + perp(p[i] - p[k]));
                            inter(l1, l2, c);
                            r = abs(p[i] - c);
                        }
                    }
                }
            }
        }
    }
    return {c, r};
}
