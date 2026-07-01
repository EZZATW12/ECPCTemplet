// returns 1e9 if the point is on the polygon 
int windingNumber(const vector<pt> &p, const pt& z) { // O(n)
    if (isPointOnPolygon(p, z)) return 1e9;
    int n = p.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        bool below = p[i].Y < z.Y;
        if (below != (p[j].Y < z.Y)) {
            auto orient_val = orient(z, p[j], p[i]);
            if (sgn(orient_val) == 0) return 0;
            if (below == (orient_val > 0)) ans += below ? 1 : -1;
        }
    }
    return ans;
}
