// minimum distance from convex polygon p to line ab
// returns 0 is it intersects with the polygon
// top - upper right vertex
T distFromPolygonToLine(const vector<pt> &p, pt a, pt b, int top) { //O(log n)
    pt orth = perp(b - a);
    if (sgn(orient(a, b, p[0])) > 0) orth = perp(a - b);
    int id = extremeVertex(p, orth, top);
    if (dot(p[id] - a, orth) > 0) return 0.0; 
    line l(a, b);
    return l.dist(p[id]); 
}
