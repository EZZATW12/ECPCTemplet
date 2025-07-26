// Solves a*x + b*y = c where c is divisible by gcd(a,b)
int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}


void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}


/*
aX + bY = g
aXt + bYt = c = gt

t = c / g
x *= t, y *= t
xUnit = b / g, yUnit = a / g;
*/

// if you want to use with Y pass: (y, x, yUnit, xUnit, bar, orEqual)

void raiseXOverBar(ll &x, ll &y, ll &xUnit, ll &yUnit, ll bar, bool orEqual){
    if(x > bar or (x == bar and orEqual))
        return;

    ll shift = (bar - x + xUnit - orEqual) / xUnit;
    x += shift * xUnit;
    y -= shift * yUnit;
}

void lowerXUnderBar(ll &x, ll &y, ll &xUnit, ll &yUnit, ll bar, bool orEqual){
    if(x < bar or (x == bar and orEqual))
        return;

    ll shift = (x - bar + xUnit - orEqual) / xUnit;
    x -= shift * xUnit;
    y += shift * yUnit;
}

void minXOverBar(ll &x, ll &y, ll &xUnit, ll &yUnit, ll bar, bool orEqual){
    if(x < bar or (x == bar and !orEqual)){
        ll shift = (bar - x + xUnit - orEqual) / xUnit;
        x += shift * xUnit;
        y -= shift * yUnit;
    }
    else{
        ll shift = (x - bar - !orEqual) / xUnit;
        x -= shift * xUnit;
        y += shift * yUnit;
    }
}

void maxXUnderBar(ll &x, ll &y, ll &xUnit, ll &yUnit, ll bar, bool orEqual){
    if(x < bar or (x == bar and orEqual)){
        ll shift = (bar - x - !orEqual) / xUnit;
        x += shift * xUnit;
        y -= shift * yUnit;
    }
    else{
        ll shift = (x - bar + xUnit - orEqual) / xUnit;
        x -= shift * xUnit;
        y += shift * yUnit;
    }
}
