/*
LIS DP - O(N log N)
有 n 個你可以參加的專案。對於每個專案，你知道其開始與結束天數以及可獲得的報酬金額。
在同一天你最多只能參加一個專案。
問：你最多可以賺到多少金額？

dp[i] = 在第 i 天之前我們可以賺到的最大金額。
*/

void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> vc(n);
    map<int, int> days;
 
    for (int i = 0; i < n; ++i) {
        int a, b, p;
        cin >> a >> b >> p;
        days[a] = days[b] = 1;
        vc[i] = {a, b, p};
    }
    int idx = 1;
    for (auto& x : days) {
        x.second = idx++; 
    }
    vector<int> dp(idx, 0);
 
    sort(vc.begin(), vc.end(), [](const array<int, 3>& va, const array<int, 3>& vb) {
        if (va[1] != vb[1]) return va[1] < vb[1];
        if (va[0] != vb[0]) return va[0] < vb[0];
        return va[2] > vb[2];
    });
 
    int i = 0;
    for (int d = 1; d < idx; ++d) {
        dp[d] = dp[d - 1]; 
        while (i < n && days[vc[i][1]] == d) {
            dp[d] = max(dp[d], dp[days[vc[i][0]] - 1] + vc[i][2]);
            i++;
        }
    }
    cout << dp[idx - 1] << "\n";
