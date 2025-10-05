// ax + by = c
// x0 = x * (c / gcd(a, b))
// y0 = y * (c / gcd(a, b))
// x = x0 + k * (b / gcd(a, b))
// y = y0 - k * (a / gcd(a, b))
// k is any integer

tll extendedEuclid(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    ll d, x1, y1;
    tie(d, x1, y1) = extendedEuclid(b, a % b);
    return {d, y1, x1 - (a / b) * y1};
}

pll linearDiophantine(ll a, ll b, ll c) {
    ll d, x, y;
    tie(d, x, y) = extendedEuclid(a, b);
    if (c % d != 0) return {-1, -1}; // no solution
    x *= c / d;
    y *= c / d;
    return {x, y};
}

// Example usage
int main() {
    ll a = 15, b = 10, c = 35;
    pll res = linearDiophantine(a, b, c);
    if (res.first == -1 && res.second == -1) {
        cout << "No solution exists" << endl;
    } else {
        cout << "One solution is x = " << res.first << ", y = "
             << res.second << endl;
    }
    return 0;
}
ax + by = c