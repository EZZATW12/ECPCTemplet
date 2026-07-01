T areaOfTriangle(pt a, pt b, pt c) {
    return fabs(cross(b - a, c - a) * 0.5);
}
