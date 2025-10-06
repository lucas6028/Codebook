using ll = long long;
const ll PM{1000000007};
ll MC(ll a) { return (a % PM + PM) % PM; } // for negative a
ll MA(ll a, ll b) { return (a + b) % PM; } // (a + b) % PM
ll MS(ll a, ll b) { return (a - b + PM) % PM; } // (a - b) % PM
ll MM(ll a, ll b) { return (a * b) % PM; } // (a * b) % PM
ll MP(ll a, ll b) { // (a ^ b) % PM
    ll res{1};
    do {
        if (b & 1) res = MM(res, a);
    } while (a = MM(a, a), b >>= 1);
    return res;
}
ll MI(ll a) { return MP(a, PM - 2); } // modular inverse of a % PM
ll MD(ll a, ll b) { return MM(a, MI(b)); } // (a / b) % PM