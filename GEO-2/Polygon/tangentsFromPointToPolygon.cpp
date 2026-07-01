/**
 * Time Complexity: O(log N)
 * Floating Point: No (integer-safe; pointPolyTangent is integer-safe)
 * Requirements: Polygon must be convex. Point must lie strictly outside the polygon.
 */
// (ccw, cw) tangents from a point that is outside this convex polygon
// returns indexes of the points
// ccw means the tangent from Q to that point is in the same direction as the polygon ccw direction
pair<int, int> tangentsFromPointToPolygon(const vector<pt> &p, pt Q){
    int ccw = pointPolyTangent(p, Q, 1, 0, (int)p.size() - 1).second;
    int cw = pointPolyTangent(p, Q, -1, 0, (int)p.size() - 1).second;
    return make_pair(ccw, cw);
}
