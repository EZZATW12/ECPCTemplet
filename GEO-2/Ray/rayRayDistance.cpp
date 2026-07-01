T rayRayDistance(pt as, pt ad, pt bs, pt bd) {
    if (rayRayIntersection(as, ad, bs, bd)) return 0.0;
    T ans = distFromPointToRay(as, ad, bs);
    ans = min(ans, distFromPointToRay(bs, bd, as));
    return ans;
}
