//
// Created by ezzat on 6/2/2026.
//
#include <bits/stdc++.h>

using namespace std;
typedef complex<long double> pt;
#define X real()
#define Y imag()
#define dot(a, b) ((conj(a)*(b)).real())
#define cross(a, b) ((conj(a)*(b)).imag())
#define vec(a, b) ((b)-(a))
#define EPS 1e-9

// Finds the exact intersection point of line AB and line CD.
pt getIntersection(pt A, pt B, pt C, pt D) {
    long double a1 = cross(vec(A, B), vec(A, C));
    long double a2 = cross(vec(A, B), vec(A, D));
    // The ratio determines exactly where the intersection lies on the segment CD
    long double t = a1 / (a1 - a2);

    // Using complex number math, C + t * CD gives the exact point
    return C + t * vec(C, D);
}


// Clips 'poly' against the left half-plane defined by the directed line AB.
vector<pt> clipPolygon(const vector<pt> &poly, pt A, pt B) {
    vector<pt> newPoly;
    int n = poly.size();
    if (n == 0) return newPoly;

    for (int i = 0; i < n; ++i) {
        pt C = poly[i];
        pt D = poly[(i + 1) % n];

        // Check if vertices C and D are inside (left of or on the line AB)
        bool cInside = cross(vec(A, B), vec(A, C)) >= -EPS;
        bool dInside = cross(vec(A, B), vec(A, D)) >= -EPS;

        if (cInside && dInside) {
            newPoly.push_back(D);
        } else if (cInside && !dInside) {
            newPoly.push_back(getIntersection(A, B, C, D));
        } else if (!cInside && dInside) {
            newPoly.push_back(getIntersection(A, B, C, D));
            newPoly.push_back(D);
        }
        // If both are outside (!cInside && !dInside), we add nothing.
    }
    return newPoly;
}

// Calculates the area of a polygon using the cross product macro (Shoelace formula).
long double getArea(const vector<pt> &poly) {
    int n = poly.size();
    if (n < 3) return 0.0;

    long double area = 0.0;
    for (int i = 0; i < n; ++i) {
        // The cross macro inherently calculates the 2D cross product from the origin
        area += cross(poly[i], poly[(i + 1) % n]);
    }
    return abs(area) / 2.0;
}

void solve() {
    int n;
    cin >> n;
    vector<pt> poly(n);
    for (int i = 0; i < n; ++i) {
        long double x, y;
        cin >> x >> y;
        poly[i] = pt(x, y);
    }
    vector<pt> kernel = poly;
    for (int i = 0; i < n; ++i) {
        pt A = poly[i];
        pt B = poly[(i + 1) % n];
        kernel = clipPolygon(kernel, A, B);
    }
    long double totalArea = getArea(poly);
    long double kernelArea = getArea(kernel);
    if (totalArea < EPS) {
        cout << fixed << setprecision(12) << 0.0 << "\n";
    } else {
        cout << fixed << setprecision(12) << kernelArea / totalArea << "\n";
    }
}