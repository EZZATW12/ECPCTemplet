// Iterate through all distinct values of floor(n / i)
for (long long l = 1, r; l <= n; l = r + 1) {
long long q = n / l;
r = n / q; // The rightmost index that gives quotient 'q'

// Range [l, r] has the exact same quotient 'q'.
// Example: To calculate the sum of floor(n/i) for all i from 1 to n:
// ans += q * (r - l + 1);
}