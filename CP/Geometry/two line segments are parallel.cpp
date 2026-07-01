//
// Created by ezzat on 5/13/2026.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

// 2D Cross Product. Positive if w is counter-clockwise to v around origin
T cross(pt v, pt w, pt origin = {0, 0}) {
    return (v.x - origin.x) * (w.y - origin.y) - (v.y - origin.y) * (w.x - origin.x);
}
T orient(pt a, pt b, pt c) {
    /*
        orient(A, B, C) is positive if when going from A to B to
        C we turn left, negative if we turn right, and zero if A, B, C are collinear
     */
    return cross(b - a, c - a);
}
// Returns true if segment AB is parallel to segment CD
bool isParallel(pt a, pt b, pt c, pt d) {
    pt v1 = b - a; // Direction vector of AB
    pt v2 = d - c; // Direction vector of CD

    // Using your existing cross() function
    return cross(v1, v2) == 0;
}
bool isStrictlyParallel(pt a, pt b, pt c, pt d) {
    // 1. They must be parallel
    if (cross(b - a, d - c) != 0) {
        return false;
    }

    // 2. Point C must NOT be collinear with line AB
    if (orient(a, b, c) == 0) {
        return false; // They are collinear, not strictly parallel
    }

    return true;
}