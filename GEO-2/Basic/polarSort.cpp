/**
 * Time Complexity: O(N log N)
 * Floating Point: No (integer-safe, uses cross product and squared distances)
 * Requirements: None
 */
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt a, pt b) {
        return make_tuple(half(a), 0.0, sq(a)) < make_tuple(half(b), cross(a, b), sq(b));
    });
}

void polarSort(vector<pt> &v, pt o) {
    sort(v.begin(), v.end(), [&](pt a, pt b) {
        return make_tuple(half(a - o), 0.0, sq(a - o)) < make_tuple(half(b - o), cross(a - o, b - o), sq(b - o));
    });
}
