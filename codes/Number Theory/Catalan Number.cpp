// Catalan Number
// C(n) = 1/(n+1) * (2n choose n) = (2n)! / ((n+1)! * n!)

ll catalan(int n) {
    return fact[2 * n] * invf[n + 1] % mod * invf[n] % mod;
}