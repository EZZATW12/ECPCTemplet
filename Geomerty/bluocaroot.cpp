// pi
const double Pi = acos(-1);

// radius of soddy circle
double soddy_radius(double r1, double r2, double r3)
{
    double delta = sqrt(r1 * r2 * r3 * (r1 + r2 + r3));

    return (r1 * r2 * r3 / (r2 * r3 + r3 * r1 + r1 * r2 + 2 * delta));
}
// area of triangle
double triangle_area_sides(double a, double b, double c)
{
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
double triange_area_median(double a, double b, double c)
{
    double s = (a + b + c) / 2;
    return 4 / 3. * sqrt(s * (s - a) * (s - b) * (s - c));
}
double triangle_area_alt(double a, double b, double c)
{
    double s = (1 / a + 1 / b + 1 / c) / 2;
    return 1 / (4 * sqrt(s * (s - 1 / a) * (s - 1 / b) * (s - 1 / c)));
}
double triangle_area_angle(double a, double b, double c, double A)
{
    double s = (sin(a) + sin(b) + sin(c)) / 2;
    double D = A / sin(a);
    return D * D * sqrt(s * (s - sin(a)) * (s - sin(b)) * (s - sin(c)));
}
// area of triangle knowing 2 sides and included angle
double triangle_area_2s1a(double a, double b, double c)
{
    return a * b * sin(c) / 2;
}
// area of n sided polygon
double area_polygon(double s, int n)
{
    return n * s * s / tan(M_PI/n) / 4;
}
// measure angle of n sided regular polygon
double angle(int n)
{
    return (n - 2) * M_PI / n;
}
// area of sector of circle with measure angle theta
double area_sector(double r, double theta)
{
    return r * r * theta / 2;
}
// volume of frustum of a cone
double volume_frustum_cone(double h, double r1, double r2)
{
    return M_PI * h / 3 * (r1 * r1 + r1 * r2 + r2 * r2);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct circle
{
    ld r, x, y;
};

bool intersect(circle A, circle b, circle C)
{
    ld x0 = A.x, x1 = b.x, r0 = A.r, r1 = b.r, y0 = A.y, y1 = b.y;
    ld d=sqrt(pow((x1-x0),2) + pow((y1-y0), 2));
    ld a=(pow(r0,2)-pow(r1, 2)+pow(d,2))/(2*d);
    ld h=sqrt(pow(r0, 2) - pow(a, 2));
    ld x2=x0+a*(x1-x0)/d;
    ld y2=y0+a*(y1-y0)/d;
    ld x3=x2+h*(y1-y0)/d;
    ld y3=y2-h*(x1-x0)/d;
    if (hypot(x3, y3) < C.r)
        return true;
    x3=x2-h*(y1-y0)/d;
    y3=y2+h*(x1-x0)/d;
    return hypot(x3, y3) < C.r;
}


double area(pair<ll, ll> a, pair<ll, ll> b)
{
    return ((a.second + b.second) * (b.first - a.first) / 2.);
}

bool CCW(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c)
{
    return (area(a, b) + area(b, c) + area(c, a) < 0);
}

V<pair<ll, ll>> convexHull(V<pair<ll, ll>> &v)
{
    ll ind, l = 0, q;
    V<pair<ll, ll>>hull;

    for (int i = 0; i < v.size(); hull.push_back(v[i++]))
    {
        while (hull.size() > 1 && !CCW(hull[hull.size() - 2], hull.back(), v[i]))
            hull.pop_back();
    }
    ll tmp = hull.size();
    for (int i = (int)v.size() - 2; i >= 0; --i)
    {
        while (hull.size() > tmp && !CCW(hull[hull.size() - 2], hull.back(), v[i]))
            hull.pop_back();
        if (!i)
            break;
        hull.push_back(v[i]);
    }
    return hull;
}
