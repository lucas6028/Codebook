long long binomial(long long n, long long k, long long p) {
    // dp[i][j] = iCj
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
        if (i <= k) dp[i][i] = 1;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            if (i != j) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % p;
            }
        }
    }

    return dp[n][k];
}