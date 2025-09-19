/*
機率 DP - O(N^2)
給定一個正奇數 N
有 N 枚編號為 1,2,…,N 的硬幣，第 i 枚出現正面的機率為 p，反面為 1-p。
已經拋擲所有硬幣，求正面數大於反面的機率。

定義 dp[i][j] 為拋完前 i 枚硬幣後，得到 j 次正面的機率。
*/

void solve() {
    int n;
    cin >> n;
    vector<double> a(n);
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0.0));

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1.0;
    }
    
    int least = n / 2 + 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= least; ++j) {
            // head
            dp[i][j] = dp[i - 1][j - 1] * a[i - 1];
            // tail
            dp[i][j] += dp[i - 1][j] * (1 - a[i - 1]);
        }
    }

    cout << fixed << setprecision(10) << dp[n][least] << "\n";
}