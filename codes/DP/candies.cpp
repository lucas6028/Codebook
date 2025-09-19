/*
組合 DP - O(NK)
有 N 個小孩，編號為 1,2,…,N。

他們決定將 K 顆糖果分給自己。對於每個 i (1≤i≤N)，第 i 個小孩最多可以拿到 ai 顆糖果（包含 0 顆）。所有糖果都必須分完，不能剩下。

請問有多少種分配糖果的方法？請將答案對 10^9+7 取模。若存在某個小孩分到的糖果數不同，則視為不同的分配方式。

令 dp[i][j] 表示將 j 顆糖果分給前 i 個小孩的方法數。
*/

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> dp(k + 1, 0), S(k + 1, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        vector<int> new_dp(k + 1, 0);
        S[0] = dp[0];
        for (int j = 1; j <= k; ++j) {
            S[j] = (S[j - 1] + dp[j]) % MOD;
        }
        for (int j = 0; j <= k; ++j) {
            if (j - a[i] - 1 >= 0) {
                new_dp[j] = (S[j] - S[j - a[i] - 1] + MOD) % MOD;
            }
            else {
                new_dp[j ] = S[j] % MOD;
            }
        }
        dp = new_dp;
    }
    cout << dp[k] << "\n";
}