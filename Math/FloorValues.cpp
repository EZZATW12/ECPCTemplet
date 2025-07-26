code to get all differnet values of floor(n/i)
for (ll l = 1, r = 1; (n/l); l = r + 1) {
    r = (n/(n/l));
    // q = (n/l), process the range [l, r]
}