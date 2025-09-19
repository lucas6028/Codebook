/* exists when a and mod are coprime */
/* but mod is not prime */
long long MI(long long a, long long mod) {
    return power_mod(a, euler_phi(mod) - 1, mod);
}