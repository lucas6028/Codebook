/*
Digit DP - O(|K| * D)
計算在 1 到 K（含）之間，滿足其十進位數字和為 D 的倍數的整數數量，答案對 10^9+7 取模。

令 dp[i][j] 表示在已確定前 i 位數字的情況下，構成長度為 |K| 的數字且目前數字和 mod D 等於 j 的方法數。
*/

const int MOD = 1e9 + 7;
int dp[10001][101][2];

void solve() {
    string K;
    int D;
    cin >> K >> D;
    int len = K.size();
    memset(dp, 0, sizeof(dp));
    dp[0][0][1] = 1;

    for (int i = 1; i <= len; ++i) {
        int limit = K[i - 1] - '0';
        for (int s = 0; s < D; ++s) {
            for (int flag = 0; flag <= 1; ++flag) {
                int ways = dp[i - 1][s][flag];
                if (ways == 0) continue;
                int max_d = (flag ? limit : 9);
                for (int d = 0; d <= max_d; ++d) {
                    int rs = (s + d) % D;
                    int rflag = (flag && d == max_d ? 1 : 0);
                    dp[i][rs][rflag] += ways;
                    dp[i][rs][rflag] %= MOD;
                }
            }
        }
    }

    int ans = (dp[len][0][0] + dp[len][0][1]) % MOD;
    ans = (ans - 1 + MOD) % MOD;
    cout << ans << "\n";
}