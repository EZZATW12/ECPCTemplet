/*
 * NAME: Aliens Trick (WQS Binary Search / Lagrangian Relaxation)
 * USE WHEN: DP answers "minimize/maximize cost using EXACTLY k items /
 *           groups / segments", and the cost function is convex in k —
 *           removing the "exactly k" constraint (by adding a penalty
 *           lambda per item chosen) turns an O(n*k) DP into O(n log(range)).
 * COMPLEXITY: O(n log(maxLambda)) instead of O(n*k)
 * GOTCHAS:
 *   - Only valid if cost(k) is convex — sanity check with a small
 *     brute-force O(n*k) DP before trusting this on the real input.
 *   - Binary search on lambda (penalty per extra item); for each lambda,
 *     run the UNCONSTRAINED dp (real cost - lambda per item) and see
 *     how many items it ends up using.
 *   - Ties in "count used" need care: make the DP state (cost, count)
 *     a pair and break ties consistently (e.g. always prefer fewer
 *     items on equal cost, or always more — pick one and stick to it)
 *     or the binary search can give a wrong boundary.
 *   - This is inherently problem-specific — treat solveDP() below as a
 *     skeleton to fill in, not drop-in code.
 * TESTED ON: "exactly k" convex-cost DP problems (general technique)
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int n, K;

// Runs the UNCONSTRAINED dp with a penalty `lambda` subtracted (or added,
// depending on min/max) once per item used. Returns {best value, items used}.
// REPLACE the body with your actual problem's transition.
pair<ll,int> solveDP(ll lambda){
    // Example skeleton shape for "choose items to optimize value, penalized
    // by lambda per item chosen":
    // vector<pair<ll,int>> dp(n+1, {0, 0});
    // for (int i = 1; i <= n; i++) {
    //     // dp[i] = best of (skip item i) vs (take item i: dp[i-1] + val[i] - lambda)
    //     // when costs tie, prefer the option with fewer items used
    // }
    // return dp[n];
    return {0, 0}; // placeholder
}

ll aliensSearch(){
    ll lo = -INF, hi = INF, bestLambda = 0;
    while (lo <= hi){
        ll mid = lo + (hi - lo) / 2;
        auto [val, cnt] = solveDP(mid);
        // adjust the comparison direction based on whether cnt increases
        // or decreases as lambda increases for your specific DP
        if (cnt <= K){ bestLambda = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    auto [val, cnt] = solveDP(bestLambda);
    return val + bestLambda * (ll)K; // undo the penalty to get the exact-K answer
}

/*
 * USAGE EXAMPLE:
 * Fill in solveDP() with your specific unconstrained DP transition
 * (subtract/add lambda exactly once per "item used"). Then:
 * ll ans = aliensSearch(); // answer for exactly K items
 * ALWAYS verify against a brute-force O(n*k) DP on small n before
 * trusting this live — convexity bugs are silent and easy to miss.
 */
