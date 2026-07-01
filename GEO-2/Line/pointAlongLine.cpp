pt pointAlongLine(pt a, pt b, T d) {
    assert(a != b);
    return a + (((b - a) / abs(b - a)) * d);
}
