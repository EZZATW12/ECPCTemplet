/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses sqrt, cos)
 * Requirements: Side lengths must form a valid quadrilateral.
 */
#include <bits/stdc++.h>
using namespace std;

typedef long double T;

// Brahmagupta's Formula for cyclic quadrilateral (all vertices on a circle)
// Area = sqrt((s-a)(s-b)(s-c)(s-d)) where s = (a+b+c+d)/2
T cyclicQuadrilateralArea(T a, T b, T c, T d) {
    T s = (a + b + c + d) / 2.0;
    return sqrt((s - a) * (s - b) * (s - c) * (s - d));
}

// Bretschneider's Formula for general quadrilateral
// Area = sqrt((s-a)(s-b)(s-c)(s-d) - a*b*c*d * cos^2((alpha + gamma)/2))
// where alpha and gamma are two opposite angles in radians
T generalQuadrilateralArea(T a, T b, T c, T d, T opposite_angle1_rad, T opposite_angle2_rad) {
    T s = (a + b + c + d) / 2.0;
    T cos_half = cos((opposite_angle1_rad + opposite_angle2_rad) / 2.0);
    return sqrt((s - a) * (s - b) * (s - c) * (s - d) - a * b * c * d * cos_half * cos_half);
}
