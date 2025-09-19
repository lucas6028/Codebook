/* a and mod are not coprime */
long long MI(long long a, long long mod) {
    long long d, x, y;
    extEcu(a, mod, d, x, y);
    return d == 1 ? (x + mod) % mod : -1;
}