//
// Created by ezzat on 6/1/2026.
//
#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 1e5 + 4, mod = 1e9 + 7;
const long long INF = 1e8;
// Define a 2D point/vector using complex numbers (Real = X, Imaginary = Y)
typedef complex<long double> point;

// Short-hand utility macros
#define sz(a) ((int)(a).size())
#define all(n) (n).begin(),(n).end()

// Constants for geometry
#define EPS 1e-9
#define OO 1e9
#define PI  acos(-1.0)

// Syntax sugar to access coordinates like properties (e.g., p.X and p.Y)
#define X real()
#define Y imag()

// Vector arithmetic & properties

#define polar(r, t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((long double)hypot((v).Y,(v).X))
#define lengthSqr(v) (dot(v,v))

// Vector products
#define dot(a, b) ((conj(a)*(b)).real())
#define cross(a, b) ((conj(a)*(b)).imag())

// Rotations and reflections
#define rotate(v, t) (polar(v,t))
#define rotateabout(v, t, a) (rotate(vec(a,v),t)+(a))
#define reflect(p, m) ((conj((p)/(m)))*(m))

// Coordinate modifications & checks
#define normalize(p) ((p)/length(p))
#define same(a, b) (lengthSqr(vec(a,b))<EPS)
#define mid(a, b) (((a)+(b))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))
double orient(point a, point b, point c) {
    /*
        orient(A, B, C) is positive if when going from A to B to
        C we turn left, negative if we turn right, and zero if A, B, C are collinear
     */
    return cross(b - a, c - a);
}
}
bool intersect(const point &a, const point &b, const point &p, const point &q, point &ret) {
    long double d1 = cross(p - a, b - a);
    long double d2 = cross(q - a, b - a);

    // 1. Check if the lines are parallel FIRST
    if (fabs(d1 - d2) <= EPS) {
        return false; // Returns false (0) if lines are parallel or collinear
    }
    // 2. Calculate the intersection safely (we know d1 - d2 is not zero here)
    ret = (d1 * q - d2 * p) / (d1 - d2);

    return true; // Returns true (1) because we successfully found the intersection
}

long double pointLineDist(const point &a, const point &b, const point &p) {
    // Safely handle the degenerate case first to prevent Division By Zero
    if (same(a, b)) {
        return length(vec(a, p)); // Just return the distance from p to a
    }
    return fabs(cross(vec(a, b), vec(a, p)) / length(vec(a, b)));
}

// Helper function (needed because 'colliner' was undefined in the original macros)
// Checks if point p lies anywhere on the infinite line passing through a and b.
bool collinear(const point &a, const point &b, const point &p) {
    // If the cross product (area of the parallelogram) is 0, the points form a flat line.
    return fabs(cross(vec(a, b), vec(a, p))) < EPS;
}

bool pointOnRay(const point &a, const point &b, const point &p) {
    // IMP NOTE: a,b,p must be collinear before calling this function!

    // The dot product calculates the directional relationship.
    // If the dot product of vector AP and vector AB is positive (or zero),
    // it means they point in the exact same direction.
    // > -EPS is used instead of >= 0 to safely account for floating-point errors.
    return dot(vec(a, p), vec(a, b)) > -EPS;
}

bool pointOnSegment(const point &a, const point &b, const point &p) {
    // 1. First, verify the point is actually on the line segment's infinite path.
    if (!collinear(a, b, p)) return false;

    // 2. A line segment is just the intersection of two opposing rays!
    // If 'p' is on the ray shooting from 'a' towards 'b',
    // AND 'p' is on the ray shooting from 'b' towards 'a',
    // then 'p' MUST be trapped exactly between point 'a' and point 'b'.
    return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

long double pointSegmentDist(const point &a, const point &b, const point &p) {
    // CASE 1: Point P is "behind" point A.
    // We check this using the dot product of vector AB and vector AP.
    // If the dot product is negative (< EPS), the angle between them is 90 degrees or more (obtuse).
    // This means the closest part of the segment to P is simply the endpoint A.
    if (dot(vec(a, b), vec(a, p)) < EPS)
        return length(vec(a, p));

    // CASE 2: Point P is "behind" point B.
    // We flip the vectors and look from B towards A.
    // If the dot product of BA and BP is negative, the angle at B is obtuse.
    // This means the closest part of the segment to P is the endpoint B.
    if (dot(vec(b, a), vec(b, p)) < EPS)
        return length(vec(b, p));

    // CASE 3: Point P is "between" A and B.
    // If neither angle is obtuse, P projects perfectly onto the segment AB itself.
    // We can just use the infinite line distance function you defined earlier!
    return pointLineDist(a, b, p);
}

// 1. The Classic: Base and Height
// Requires the length of the base and the perpendicular height.
long double triangleAreaBH(long double b, long double h) {
    return b * h / 2.0;
}

// 2. Trigonometry: Two Sides and the Included Angle
// Uses the formula: Area = 1/2 * a * b * sin(theta)
// 't' must be in radians! fabs() ensures area is positive even if angle direction is reversed.
long double triangleArea2sidesAngle(long double a, long double b, long double t) {
    return fabs(a * b * sin(t) / 2.0);
}

// 3. Law of Sines: Two Angles and the Included Side
// Derives the missing side using the Law of Sines, then applies the formula above.
long double triangleArea2anglesSide(long double t1, long double t2, long double s) {
    // The third angle t3 = PI - (t1 + t2).
    // Since sin(PI - x) = sin(x), we can just divide by sin(t1 + t2).
    return fabs(s * s * sin(t1) * sin(t2) / (2.0 * sin(t1 + t2)));
}

// 4. Heron's Formula: Three Sides
// Calculates area using only the lengths of the three sides.
long double triangleArea3sides(long double a, long double b, long double c) {
    // 's' is the semi-perimeter (half of the total perimeter)
    long double s = (a + b + c) / 2.0;

    // sqrt(s * (s-a) * (s-b) * (s-c))
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// 5. Shoelace Formula / Cross Product: Three Coordinate Points
// 'point' refers to the complex<long double> definition from your first snippet.
long double triangleArea3points(const point &a, const point &b, const point &c) {
    // cross(a,b) calculates (a.x * b.y - a.y * b.x)
    // Summing these cross products for the perimeter gives twice the signed area.
    // fabs() is used to return the absolute (positive) area regardless of clockwise/counter-clockwise point order.
    return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2.0;
}

// 1. Law of Cosines: Find the angle opposite to side 'a' (given sides a, b, c)
long double cosRule(long double a, long double b, long double c) {
    // Safely handle denom = 0 (If b or c is 0, it's a degenerate triangle/point)
    if (b < EPS || c < EPS) return 0.0;

    // Formula: cos(A) = (b^2 + c^2 - a^2) / (2bc)
    long double res = (b * b + c * c - a * a) / (2 * b * c);

    // Floating point domain clamping (Prevents NaN crashes)
    if (fabs(res - 1) < EPS) res = 1;
    if (fabs(res + 1) < EPS) res = -1;

    return acos(res);
}

// 2. Law of Sines: Find an angle given two sides and an angle opposite one of them
// s1 is opposite to a1. s2 is opposite to the angle we want to find.
long double sinRuleAngle(long double s1, long double s2, long double a1) {
    // Safely handle denom = 0 (If side 1 is 0)
    if (s1 < EPS) return 0.0;

    // Formula: sin(A2) = (s2 * sin(a1)) / s1
    long double res = s2 * sin(a1) / s1;

    // Floating point domain clamping
    if (fabs(res - 1) < EPS) res = 1;
    if (fabs(res + 1) < EPS) res = -1;

    return asin(res);
}

// 3. Law of Sines: Find a side given one side and two angles
// s1 is opposite to a1. The side we want to find is opposite to a2.
long double sinRuleSide(long double s1, long double a1, long double a2) {
    // Safely handle denom = 0 (If sin(a1) is 0, meaning angle a1 is 0 or 180 degrees)
    if (fabs(sin(a1)) < EPS) return 0.0;

    // Formula: s2 = (s1 * sin(a2)) / sin(a1)
    long double res = s1 * sin(a2) / sin(a1);

    return fabs(res); // Ensure length is strictly positive
}

/*
 *        u
 *       /|\
 *      / | \
 *    a/  |  \b
 *    /   |m  \
 *   /____|____\
 *  p  h   c-h  q
 */

int dcmp(const double &a, const double &b) {
    if (fabs(a - b) < EPS)
        return 0;
    return ((a > b) << 1) - 1;
}

int triangleThirdPoint(const point &p, const point &q, const double &a,
                       const double &b, point &u1, point &u2) {
    point pq = vec(p, q);
    double c = length(pq);
    double arr[] = {a, b, c};
    sort(arr, arr + 3);
    if (dcmp(arr[0] + arr[1], arr[2]) < 0)
        return false;

    //m^2=a^2-h^2
    //m^2=b^2-(c-h)^2
    //m^2=b^2-(c^2-2ch+h^2)
    //m^2=b^2-c^2+2ch-h^2
    //a^2-h^2=b^2-c^2+2ch-h^2
    //0=b^2-c^2+2ch-h^2-a^2+h^2
    //0=b^2-c^2+2ch-a^2
    //2ch=a^2-b^2+c^2
    //h=(a^2-b^2+c^2)/2c
    long double h = (a * a - b * b + c * c) / (2.0 * c);
    long double sq = a * a - h * h;
    if (!dcmp(sq, 0))sq = 0;
    long double m = sqrt(sq);
    point npq = normalize(pq);
    point prp = perp(npq);
    u1 = p + (npq * h) + m * prp;
    u2 = p + (npq * h) - m * prp;
    return 1 + (dcmp(arr[0] + arr[1], arr[2]) != 0);
}

// Returns the number of intersections (0, 1, or 2)
// Populates r1 and r2 with the actual intersection points
int circleLineIntersection(const point &p0, const point &p1, const point &cen,
                           long double rad, point &r1, point &r2) {

    // BUG FIX 1: Safely handle degenerate case if p0 == p1
    // If the line segment is just a single point, it doesn't form a line.
    if (same(p0, p1)) return 0;

    long double a, b, c, t1, t2;

    // Setting up the quadratic equation coefficients (at^2 + bt + c = 0)
    a = dot(p1 - p0, p1 - p0);
    b = 2 * dot(p1 - p0, p0 - cen);
    c = dot(p0 - cen, p0 - cen) - rad * rad;

    // Calculate the discriminant
    // (Note: Changed 'double' to 'long double' for consistency)
    long double det = b * b - 4 * a * c;
    int res;

    if (fabs(det) < EPS) {
        det = 0;
        res = 1; // Tangent (1 intersection)
    } else if (det < 0) {
        res = 0; // No intersection
    } else {
        res = 2; // Secant (2 intersections)
    }

    // BUG FIX 2: Early exit if no intersection
    // If det < 0, sqrt(det) will result in NaN (Not a Number),
    // which would poison r1 and r2. We must return immediately!
    if (res == 0) return 0;

    det = sqrt(det);

    // Solve for 't' using the quadratic formula
    t1 = (-b + det) / (2 * a);
    t2 = (-b - det) / (2 * a);

    // Plug 't' back into the parametric line equation to get the physical coordinates
    r1 = p0 + t1 * (p1 - p0);
    r2 = p0 + t2 * (p1 - p0);

    return res;
}

enum CircleState {
    IDENTICAL,
    CONCENTRIC,
    INSIDE,
    TANGENT_INTERNAL,
    INTERSECTING,
    TANGENT_EXTERNAL,
    DISJOINT
};

CircleState
intersectCirclesDetailed(const point &c1, long double r1, const point &c2, long double r2, point &res1, point &res2) {

    long double d = length(c1 - c2);
    long double rSum = r1 + r2;
    long double rDiff = fabs(r1 - r2);
    CircleState state;

    // 1. Determine the exact state
    if (d < EPS) {
        if (rDiff < EPS) return IDENTICAL;
        return CONCENTRIC;
    }
    if (d < rDiff - EPS) state = INSIDE;
    else if (fabs(d - rDiff) < EPS) state = TANGENT_INTERNAL;
    else if (fabs(d - rSum) < EPS) state = TANGENT_EXTERNAL;
    else if (d > rSum + EPS) state = DISJOINT;
    else state = INTERSECTING;

    // 2. If they don't touch at all, bail out immediately!
    if (state == IDENTICAL || state == CONCENTRIC || state == INSIDE || state == DISJOINT) {
        return state;
    }

    // 3. If they DO touch (Tangent or Intersecting), calculate the points
    long double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    long double h = sqrt(std::max(0.0L, r1 * r1 - a * a));

    // p3 is the point on the line between the centers where the chord crosses
    point p3 = c1 + (c2 - c1) * (a / d);

    // Calculate the perpendicular offset (distance 'h' perpendicular to the center line)
    point perp = (c2 - c1) / d * point(0, 1) * h;

    // Apply the offset to get the actual coordinates
    res1 = p3 + perp;
    res2 = p3 - perp;

    // Note: If the state is TANGENT_INTERNAL or TANGENT_EXTERNAL,
    // the height 'h' will be exactly 0, meaning 'res1' and 'res2'
    // will hold the exact same single coordinate!

    return state;
}

// 1. Define a circle given two points on opposite sides (the diameter)
// Populates 'cen' with the center point and 'r' with the radius.
void circle2(const point &p1, const point &p2, point &cen, long double &r) {
    // The center is simply the midpoint between the two points
    cen = mid(p1, p2);

    // The radius is half the distance between the two points
    r = length(vec(p1, p2)) / 2.0;
}

// 2. Define a circle given three points (Circumcircle)
// Returns 'true' if a circle can be formed, 'false' if the points are collinear.
// Populates 'cen' with the center point and 'r' with the radius.
bool circle3(const point &p1, const point &p2, const point &p3, point &cen, long double &r) {
    // Find the midpoints of two sides of the triangle formed by the points
    point m1 = mid(p1, p2);
    point m2 = mid(p2, p3);

    // Find the perpendicular vectors to those sides
    point perp1 = perp(vec(p1, p2));
    point perp2 = perp(vec(p2, p3));

    // The center of the circumcircle is the intersection of the perpendicular bisectors.
    // 'intersect' takes two points for the first line (m1, m1+perp1),
    // two points for the second line (m2, m2+perp2), and outputs the intersection to 'cen'.
    bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);

    // The radius is the distance from the calculated center to ANY of the original points
    r = length(vec(cen, p1));

    // Will return false if the perpendicular bisectors are parallel
    // (which only happens if p1, p2, and p3 form a straight line)
    return res;
}

// Define the three possible states for the point's location
enum STATE {
    IN,
    OUT,
    BOUNDARY
};

// Determines where point 'p' is relative to a circle defined by 'cen' and 'r'
STATE circlePoint(const point &cen, const long double &r, const point &p) {

    // Calculate the SQUARED distance from the center to the point
    long double lensqr = lengthSqr(vec(cen, p));

    // Check if the squared distance is equal to the squared radius (with EPS for safety)
    if (fabs(lensqr - r * r) < EPS)
        return BOUNDARY;

    // If the squared distance is strictly less than the squared radius, it's inside
    if (lensqr < r * r)
        return IN;

    // Otherwise, it must be outside
    return OUT;
}

// Returns a list of line segments representing the common tangents.
// Each pair contains (Tangent Point on Circle 1, Tangent Point on Circle 2)
vector<pair<point, point>> circleTangents(const point &c1, long double r1,
                                          const point &c2, long double r2) {
    vector<pair<point, point>> tangents;

    // Using complex abs() gives the distance between the two centers
    long double d = abs(c1 - c2);

    // If circles are identical or perfectly concentric, we can't define distinct tangents
    if (d < EPS) return tangents;

    // The base angle of the imaginary line connecting the two centers
    long double base_angle = arg(c2 - c1);

    // ------------------------------------------------------------------
    // 1. EXTERNAL TANGENTS (The lines that don't cross the center line)
    // ------------------------------------------------------------------
    long double dr = r1 - r2;
    if (d >= fabs(dr) - EPS) {
        // Clamp to [-1, 1] to prevent NaN crashes from floating point errors
        long double val = max((long double) -1.0, min((long double) 1.0, dr / d));
        long double theta = acos(val);

        // Calculate tangent points on Circle 1
        point p1a = c1 + polar(r1, base_angle + theta);
        point p1b = c1 + polar(r1, base_angle - theta);

        // Calculate corresponding tangent points on Circle 2
        point p2a = c2 + polar(r2, base_angle + theta);
        point p2b = c2 + polar(r2, base_angle - theta);

        tangents.push_back({p1a, p2a});

        // If theta > 0, there are two distinct lines. If theta == 0, the circles
        // are perfectly touching inside one another, so there is only 1 tangent!
        if (theta > EPS) {
            tangents.push_back({p1b, p2b});
        }
    }

    // ------------------------------------------------------------------
    // 2. INTERNAL TANGENTS (The lines that cross in an 'X' shape)
    // ------------------------------------------------------------------
    long double sr = r1 + r2;
    if (d >= sr - EPS) {
        long double val = max((long double) -1.0, min((long double) 1.0, sr / d));
        long double theta = acos(val);

        point p1a = c1 + polar(r1, base_angle + theta);
        point p1b = c1 + polar(r1, base_angle - theta);

        // Because internal tangents cross over, the points on Circle 2
        // are exactly 180 degrees (PI radians) flipped!
        point p2a = c2 + polar(r2, base_angle + theta + PI);
        point p2b = c2 + polar(r2, base_angle - theta + PI);

        tangents.push_back({p1a, p2a});

        // Avoid duplicating the line if the circles are kissing exactly on the outside
        if (theta > EPS) {
            tangents.push_back({p1b, p2b});
        }
    }

    return tangents;
}

long double getIntersectionArea(point c1, long double r1, point c2, long double r2) {
    long double d = abs(c1 - c2);

    // Case 1: No intersection
    if (d >= r1 + r2) {
        return 0.0;
    }

    // Case 2: One completely inside the other
    if (d <= abs(r1 - r2)) {
        long double r = min(r1, r2);
        return PI * r * r;
    }

    // Case 3: Partial intersection
    // Using Law of Cosines to find the half-angles
    long double alpha = acos((r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d));
    long double beta = acos((r2 * r2 + d * d - r1 * r1) / (2.0 * r2 * d));

    // Area of the circular segment from C1
    long double a1 = r1 * r1 * alpha - 0.5 * r1 * r1 * sin(2.0 * alpha);

    // Area of the circular segment from C2
    long double a2 = r2 * r2 * beta - 0.5 * r2 * r2 * sin(2.0 * beta);

    return a1 + a2;
}