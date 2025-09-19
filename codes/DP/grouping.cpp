/*
狀壓 DP - O(3^N * + 2^N * N^2)
有 N 隻兔子，編號為 1,2,…,N。

對於每一對 i,j (1≤i,j≤N)，兔子 i 與 j 的相容度由整數 a_i,j 描述。這裡 a_i,i = 0 對於每個 i (1≤i≤N)，且 a_i,j = a_j,i 對於任意 i 與 j (1≤i,j≤N)。

A 將 N 隻兔子分成若干個群組。每隻兔子必須且僅屬於一個群組。分群後，對於每一對 i 與 j (1≤i<j≤N)，若兔子 i 與 j 屬於同一群組，A 即可獲得 a_i,j 分。

求 A 能獲得的最大總分。

令 cost[S] 表示將集合 S 中的所有兔子放在同一群組時所得到的分數。此值可在 O(2^N * N^2) 時間內計算。

接著我們計算 dp[S]，表示對集合 S 中的兔子進行分群時所能得到的最大分數。
*/

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> cost(1<<n, 0);
    vector<int> dp(1<<n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    // backtrack all subset
    for (int b = 0; b < (1<<n); ++b) {
        vector<int> subset;
        for (int i = 0; i < n; ++i) {
            if (b & (1<<i)) {
                for (const int& j : subset) {
                    cost[b] += a[i][j];
                }
                subset.pb(i);
            }
        }
    }

    // dp
    for (int i = 0; i < (1<<n); ++i) {
        int j = ((1<<n) - 1) ^ i;
        for (int s = j; s != 0; s = (s - 1) & j) {
            dp[i ^ s] = max(dp[i ^ s], dp[i] + cost[s]);
        }
    }
    cout << dp[(1<<n) - 1] << "\n";
}