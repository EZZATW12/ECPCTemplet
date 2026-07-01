// intersection between a simple polygon and a circle
T polygonCircleIntersection(const vector<pt> &v, pt p, T r) {
    int n = v.size();
    T ans = 0.00;
    pt org = {0, 0};
    for(int i = 0; i < n; i++) {
        int x = sgn(orient(p, v[i], v[(i + 1) % n]));
        if(x == 0) continue;
        T area = triangleCircleIntersection(org, r, v[i] - p, v[(i + 1) % n] - p);
        if (x < 0) ans -= area;
        else ans += area;
    }
    return abs(ans);
}
