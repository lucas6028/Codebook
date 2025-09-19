/*
遊戲 DP - O(N^2)
A 與 B 將進行以下的遊戲。

最初，他們會得到一個序列 a = (a1, a2, ..., aN)。在 a 尚未為空時，兩位玩家輪流進行以下操作，從 A 開始：

從 a 的開頭或結尾移除一個元素。玩家會獲得 x 分，其中 x 為被移除的元素。
設 X 與 Y 分別為遊戲結束時 A 與 B 的總得分。A 會嘗試最大化 X−Y，而 B 會嘗試最小化 X−Y。

假設兩位玩家都採取最優策略，請求出最後的 X−Y 值。

定義 dp[i][j] 為在區間 [i, j] 上，對於 B 來說的最優分數 (X−Y)。
*/

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        dp[i][i] = a[i];
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            dp[i][j] = max(a[i] - dp[i + 1][j], a[j] - dp[i][j - 1]);
        }
    }
    cout << dp[0][n - 1] << "\n";
}