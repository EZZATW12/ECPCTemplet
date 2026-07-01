bool rayRayIntersection(pt as, pt ad, pt bs, pt bd) {
    T dx = bs.X - as.X, dy = bs.Y - as.Y;
    T det = bd.X * ad.Y - bd.Y * ad.X;
    if (fabs(det) < EPS) return 0;
    T u = (dy * bd.X - dx * bd.Y) / det;
    T v = (dy * ad.X - dx * ad.Y) / det;
    if (sgn(u) >= 0 && sgn(v) >= 0) return 1;
    else return 0;
}
