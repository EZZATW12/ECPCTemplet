/**
 * Time Complexity: O(1)
 * Floating Point: Yes (trigonometric functions in radians)
 * Requirements: Angles in radians. Earth Radius ~ 6371.0 km (or 6371000 meters).
 */
#include <bits/stdc++.h>
using namespace std;

typedef long double T;

const T PI = acos(-1.0);
const T EARTH_RADIUS_KM = 6371.0;

T degToRad(T deg) { return deg * PI / 180.0; }
T radToDeg(T rad) { return rad * 180.0 / PI; }

// Convert Latitude / Longitude (in degrees) to 3D Cartesian coordinates on unit sphere
// lat in [-90, 90], lon in [-180, 180]
tuple<T, T, T> latLonToCartesian(T lat_deg, T lon_deg, T R = 1.0) {
    T lat = degToRad(lat_deg);
    T lon = degToRad(lon_deg);
    T x = R * cos(lat) * cos(lon);
    T y = R * cos(lat) * sin(lon);
    T z = R * sin(lat);
    return {x, y, z};
}

// Great Circle Distance using Haversine formula (numerically stable for small distances)
// Inputs: lat1, lon1, lat2, lon2 in degrees, R = sphere radius
T haversineDistance(T lat1_deg, T lon1_deg, T lat2_deg, T lon2_deg, T R = EARTH_RADIUS_KM) {
    T lat1 = degToRad(lat1_deg), lon1 = degToRad(lon1_deg);
    T lat2 = degToRad(lat2_deg), lon2 = degToRad(lon2_deg);
    T dlat = lat2 - lat1;
    T dlon = lon2 - lon1;
    T a = sin(dlat / 2.0) * sin(dlat / 2.0) + cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
    T c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    return R * c;
}

// Spherical Triangle Area using Girard's Theorem
// A, B, C are internal angles of spherical triangle in radians
T sphericalTriangleArea(T A_rad, T B_rad, T C_rad, T R = 1.0) {
    T excess = A_rad + B_rad + C_rad - PI; // Spherical excess
    return R * R * excess;
}

// Spherical Cap Area given polar radius h (height of cap) or angle theta (half-angle in radians)
T sphericalCapArea(T theta_rad, T R = 1.0) {
    return 2.0 * PI * R * R * (1.0 - cos(theta_rad));
}
