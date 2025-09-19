ll Cnm(ll n, ll m) {
    if (m > n / 2) m = n - m;
    ll r{1};
    for (ll i{1}, j{n}; i <= m; ++i, --j) r *= j, r /= i;
    return r;
}
