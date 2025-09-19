void sieve(vector<int>& primes) {
    vector<int> is_prime(INF + 1, 0);
    is_prime[0] = 1;
    is_prime[1] = 1;

    int sq = sqrt(INF);

    for (int i = 2; i <= sq; ++i) {
        if (!is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= INF; j += i) {
                is_prime[j] = 1;
            }
        }
    }
}