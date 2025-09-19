fac[0] = 1;
for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % MOD;
}

inv_fac[n] = power_mod(fac[n], MOD - 2, MOD);
for (int i = n - 1; i >= 0; --i) {
    inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
}

// C(n, k) = fac[n] * inv_fac[k] * inv_fac[n - k];
