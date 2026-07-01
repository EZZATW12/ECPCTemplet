long double triangleAreaBH(long double b, long double h) { return b * h / 2; }

long double triangleArea2sidesAngle(long double a, long double b, long double t) {
    return fabs(a * b * sin(t) / 2);
}

long double triangleArea2anglesSide(long double t1, long double t2, long double s) {
    return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}

long double triangleArea3sides(long double a, long double b, long double c) {
    long double s((a + b + c) / 2);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

long double triangleArea3points(const pt& a, const pt& b, const pt& c) {
    return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2;
}