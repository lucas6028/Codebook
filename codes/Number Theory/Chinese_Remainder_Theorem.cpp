// coprime (p^k)
pair<ll, ll> CRT(const vector<pair<ll, ll>>& congruences) {
    ll M = 1, sol = 0;
    for (auto& [m, a] : congruences) M *= m;
    for (auto& [m, a] : congruences) {
        ll x = M / m, y = MI(x, m);
        sol = MA(sol, MM(MM(a, x, M), y, M), M);
    }
    return {M, sol};
}

// example usage
int main() {
    // x ≡ 2 (mod 3)
    // x ≡ 3 (mod 5)
    // x ≡ 2 (mod 7)
    vector<pair<ll, ll>> congruences = {{3, 2}, {5, 3}, {7, 2}};
    auto [M, sol] = CRT(congruences);
    cout << "M: " << M << ", x: " << sol << endl; // M: 105, x: 23
    return 0;
}
