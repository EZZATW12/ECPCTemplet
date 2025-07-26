template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
    typedef Point P;
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }

    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }

    P operator+(P p) const { return P(x + p.x, y + p.y); }

    P operator-(P p) const { return P(x - p.x, y - p.y); }

    P operator*(T d) const { return P(x * d, y * d); }

    P operator/(T d) const { return P(x / d, y / d); }

    T dot(P p) const { return x * p.x + y * p.y; }

    T cross(P p) const { return x * p.y - y * p.x; }

    T cross(P a, P b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }

    double dist() const { return sqrt((double) dist2()); }

    double dist(P b) { return (*this - b).dist(); };

    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }

    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }

    P getVector(const P &p) const { return p - (*this); }

    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }

    friend istream &operator>>(istream &is, P &p) {
        return is >> p.x >> p.y;
    }


    // Project point onto line through a and b (assuming a != b).
    P projectOnLine(const P &a, const P &b) const {
        P ab = a.getVector(b);
        P ac = a.getVector(*this);
        return a + ab * ac.dot(ab) / a.dist2(b);
    }

    // Project point c onto line segment through a and b (assuming a != b).
    P projectOnSegment(const P &a, const P &b) const {
        P &c = *this;
        P ab = a.getVector(b);
        P ac = a.getVector(c);

        long double r = dot(ac, ab), d = a.dist2(b);
        if (r < 0) return a;
        if (r > d) return b;

        return a + ab * r / d;
    }

    P reflectAroundLine(const P &a, const P &b) const {
        return projectOnLine(a, b) * 2 - (*this);
    }
};

const ld eps = 1e-9;

int dcmp(const ld &a, const ld &b){
    if(fabs(a - b) < eps)
        return 0;

    return (a > b ? 1 : -1);
}
