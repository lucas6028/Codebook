/*
抽象 DP - O(N^2)
設 N 為正整數。給定一個長度為 N−1 的字串 s，字元僅包含 '<' 與 '>'。

求滿足條件的排列 (p1, p2, …, pN)（即 1 到 N 的排列）數量，答案對 10^9+7 取模：

對於每個 i（1 ≤ i ≤ N−1），若 s 的第 i 個字元為 '<'，則要求 p_i < p_{i+1}；若為 '>'，則要求 p_i > p_{i+1}。

令 dp[i][j] 表示：在考慮前 i 個比較符號（即構成長度為 i+1 的排列）且最後一個元素為 j 的有效排列數量。
*/

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<int> prefix(n + 1, 0);
    dp[1][0] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int k = 0; k < n; ++k) {
            prefix[k + 1] = prefix[k] + dp[i - 1][k];
        }
        for (int j = 0; j < i; ++j) {
            if (s[i - 2] == '>') {
                dp[i][j] += prefix[i - 1] - prefix[j];
                dp[i][j] %= MOD;
                /*
                for (int k = j; k < i - 1; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
                */
            }
            else {
                dp[i][j] += prefix[j];
                dp[i][j] %= MOD;
                /*
                for (int k = 0; k < j; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
                */
            }
        }
    }
    int ans = 0;
    for (int j = 0; j < n; ++j) {
        ans += dp[n][j];
        ans %= MOD;
    }
    cout << ans << "\n";
}