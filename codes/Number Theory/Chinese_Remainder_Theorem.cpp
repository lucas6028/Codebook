// coprime (p^k)
pair<ll, ll> CRT(const vector<pair<ll, ll>>& congruences) {
    ll M{1}, sol{};
    for (auto& [m, a] : congruences) M *= m;
    for (auto& [m, a] : congruences) {
        ll x{M / m}, y{MI(x, m)};
        sol = MA(sol, MM(MM(a, x, M), y, M), M);
    }
    return {M, sol};
}
