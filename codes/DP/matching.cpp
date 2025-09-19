/*
Bitmask DP - O(N * 2^N)
有 N 個男人和 N 個女人，分別編號為 1, 2, …, N。

對於每個 i, j (1 ≤ i, j ≤ N)，男人 i 和女人 j 的相容性由整數 a[i][j] 給出。
如果 a[i][j] = 1，則男人 i 和女人 j 是相容的；
如果 a[i][j] = 0，則不是。

A 正在嘗試組成 N 對，每對由一個相容的男人和女人組成。在這裡，每個男人和每個女人必須恰好屬於一對。

求 A 可以組成 N 對的方法數，結果對 10^9 + 7 取模。

定義 dp[S] 為將集合 S 中的女性與前 |S| 個男性配對的方法數。
*/

const int maxn = 21;
const int MOD = 1e9 + 7;
int n;
int grid[maxn][maxn];
int dp[1 << maxn];

void solve() {
    cin >> n;
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    dp[0] = 1;
    for (int s = 0; s < (1 << n); ++s) {
        int ps = __builtin_popcount(s);
        for (int w = 0; w < n; ++w) {
            if ((s & (1 << w)) || !grid[ps][w]) {
                continue;
            }

            dp[s | (1 << w)] += dp[s];
            dp[s | (1 << w)] %= MOD;
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
}