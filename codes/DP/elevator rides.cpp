/*
狀壓 DP - O(2^N)
有 n 個人想要搭電梯到樓頂，建築物只有一部電梯。你知道每個人的體重以及電梯的最大允許載重。最少需要搭乘多少次電梯？

定義 dp[S] = {r, w}，其中 r 是將集合 S 中的所有人送到樓頂所需的最少電梯次數，w 是最後一次電梯所載人的總重量。
*/

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    vector<pii> dp(1<<n, {INF, INF});
 
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
 
    dp[0] = {1, 0};
    for (int b = 1; b < (1<<n); ++b) {
        for (int i = 0; i < n; ++i) {
            if (b & (1<<i)) {
                auto [r_prev, w_prev] = dp[b ^ (1<<i)];
                pii can;
                if (w_prev + w[i] <= x) {
                    can = {r_prev, w_prev + w[i]};
                }
                else {
                    can = {r_prev + 1, w[i]};
                }
                dp[b] = min(dp[b], can);
            }
        }
    }
    cout << dp[(1<<n) - 1].first << "\n";
}
