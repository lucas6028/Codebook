/*
遊戲 DP - O(N^2)
有一個集合 A={a1,a2,…,aN}，包含 N 個正整數。太郎和次郎將進行以下的遊戲。

一開始有一堆 K 顆石頭。兩位玩家輪流進行以下操作，從太郎開始：

選擇集合 A 中的一個元素 x，並從石堆中移除恰好 x 顆石頭。
當某位玩家無法進行操作時即輸掉比賽。假設兩位玩家都採取最優策略，請判斷誰會獲勝。

定義 dp[i] 表示當剩下 i 顆石頭時，是否有可能獲勝。
*/

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<bool> dp(k + 1, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= k; ++i) {
        for (int x : a) {
            if (i >= x && !dp[i - x]) {
                dp[i] = 1;
            }
        }
    }
    cout << (dp[k] ? "First" : "Second") << "\n";
}