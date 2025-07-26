Point of intersection of 2 circles
bool intersect(point a, point b, point c, ll r, point& ans) {
    point vec = b - a;
    ld d2 = dist2(vec), sum = 2 * r, h2 = r * r - 0.25L * d2;
 
    if (sum * sum < d2) {
        return 0;
    }
    point mid = a + vec * 0.5L, per = perp(vec) * sqrtl(fmax(0, h2) / d2);
 
    point x1 = mid + per;
    point x2 = mid - per;
 
    if(dist2(x1 - c) - r * r <= EPS){
        ans = x1;
        return 1;
    }
    if(dist2(x2 - c) - r * r <= EPS){
        ans = x2;
        return 1;
    }
    return 0;
}