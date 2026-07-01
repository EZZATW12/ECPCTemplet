//
// Created by ezzat on 6/29/2026.
//

vector<pair<int, int> > all_anti_podal(int n, vector<pt> &p) {
    vector<pair<int, int> > result;

    auto nx = [&](int i) { return (i + 1) % n; };
    auto pv = [&](int i) { return (i - 1 + n) % n; };

    // parallel edges should't be visited twice
    vector<bool> vis(n, false);

    for (int p1 = 0, p2 = 0; p1 < n; ++p1) {
        // the edge that we are going to consider in this iteration
        // the datatype is Point, but it acts as a vector
        pt base = p[nx(p1)] - p[p1];

        // the last condition makes sure that the cross products don't have the same sign
        while (p2 == p1 || p2 == nx(p1) || sgn(cross(base, p[nx(p2)] - p[p2])) == sgn(cross(base, p[p2] - p[pv(p2)]))) {
            p2 = nx(p2);
        }

        if (vis[p1]) continue;
        vis[p1] = true;

        result.push_back({p1, p2});
        result.push_back({nx(p1), p2});

        // if both edges from p1 and p2 are parallel to each other
        if (sgn(cross(base, p[nx(p2)] - p[p2])) == 0) {
            result.push_back({p1, nx(p2)});
            result.push_back({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }

    return result;
}