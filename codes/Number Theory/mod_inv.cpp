// Modular inverse when mod is prime
long long mod_inverse(long long a, long long mod) {
    return power_mod(a, mod - 2, mod);  // Fermat's Little Theorem
}