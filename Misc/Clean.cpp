// Cmake files
//add_definitions(-D Clion)
//set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000000")

#pragma GCC optimize("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("Ofast");
#pragma GCC target("avx2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define PI acos(-1)
#define fi first
#define se second
#define pp push_back
#define all(x) (x).begin(), (x).end()
#define Ones(n) __builtin_popcountll(n)
#define endl '\n'
#define mem(arrr, xx) memset(arrr,xx,sizeof arrr)
//#define int long long

int dx[] = {+0, +0, -1, +1, +1, +1, -1, -1};
int dy[] = {-1, +1, +0, +0, +1, -1, +1, -1};

const double EPS = 1e-9;
const ll LOO = 0X3F3F3F3F3F3F3F3F;
const int N = 2e5 + 5, OO = 0X3F3F3F3F, MOD = 1e9 + 7, LOG = 20;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef Clion
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
}


ll gcd(ll x, ll y) {
    return y ? gcd(y, x % y) : x;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll mul(const ll &a,const ll&b){
    return (a % MOD + MOD) * (b % MOD + MOD) % MOD;
}

ll add(const ll &a,const ll&b){
    return (a + b + 2 * MOD)%MOD;
}

ll pw(ll b, ll p) {
    if(p < 0)return 0;
    if (!p) return 1LL;
    ll ret = pw(b, p >> 1LL);
    ret = mul(ret,ret);
    if (p & 1LL)
        ret = mul(ret,b);
    return ret;
}


void solve() {

}


signed main() {
    fast();
    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
}
