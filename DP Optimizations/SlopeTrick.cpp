/*
 * NAME: Slope Trick
 * USE WHEN: minimizing a piecewise-linear convex function built by
 *           repeatedly adding |x - a| terms or clamping the slope —
 *           common in DP problems phrased as "minimize total cost where
 *           cost grows with distance from a moving target" (e.g. make
 *           an array non-decreasing with minimum total change cost).
 * COMPLEXITY: O(n log n) total across all operations
 * GOTCHAS:
 *   - L is a MAX-heap holding the left slope's breakpoints (top =
 *     rightmost breakpoint of the left/flat-or-decreasing half); R is
 *     a MIN-heap for the right slope, symmetric.
 *   - addAbs(a) is the core primitive: adding |x-a| widens the flat
 *     valley by inserting a into both heaps and rebalancing if needed.
 *   - minValue tracks the function's minimum separately — the heaps
 *     only store slope breakpoints, not function values.
 *   - This is genuinely fiddly to get exactly right for YOUR problem's
 *     specific operations (chmin-prefix, chmax-suffix, shifting, etc).
 *     Treat this as a starting skeleton, not a guaranteed drop-in —
 *     verify against brute force on small cases before trusting it.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SlopeTrick {
    priority_queue<ll> L;                              // max-heap, left slope
    priority_queue<ll, vector<ll>, greater<ll>> R;      // min-heap, right slope
    ll minValue = 0;
    ll addL = 0, addR = 0; // lazy shift offsets

    // adds |x - a| to the function
    void addAbs(ll a){
        ll l0 = L.empty() ? a : L.top() + addL;
        ll r0 = R.empty() ? a : R.top() + addR;
        if (a < l0){
            minValue += l0 - a;
            L.pop(); L.push(a - addL);
            L.push(r0 - addL);
            R.pop(); R.push(l0 - addR);
        } else if (a > r0){
            minValue += a - r0;
            R.pop(); R.push(a - addR);
            R.push(l0 - addR);
            L.pop(); L.push(r0 - addL);
        } else {
            L.push(a - addL);
            R.push(a - addR);
        }
    }

    // f(x) = min(f(x), f(a)) for x > a  -- clips breakpoints above a on the right slope
    void chminSuffix(ll a){
        while (!R.empty() && R.top() + addR > a) R.pop();
        R.push(a - addR);
    }
    // f(x) = min(f(x), f(a)) for x < a  -- clips breakpoints below a on the left slope
    void chminPrefix(ll a){
        while (!L.empty() && L.top() + addL < a) L.pop();
        L.push(a - addL);
    }

    // shifts the entire function: flat region widens by dl to the left, dr to the right
    void shift(ll dl, ll dr){ addL -= dl; addR += dr; }

    ll query(){ return minValue; }
};

/*
 * USAGE EXAMPLE:
 * SlopeTrick f;
 * f.addAbs(3);       // f(x) += |x - 3|
 * f.addAbs(7);       // f(x) += |x - 7|
 * f.shift(0, 2);      // widen the flat minimum region 2 to the right
 * ll ans = f.query(); // minimum value of the accumulated function
 */
