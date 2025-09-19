/*
LIS DP + Segment Tree - O(N log N)
有 N 朵花排成一列。對於每個 i (1 ≤ i ≤ N)，第 i 朵花的高度與美麗分別為 h_i 與 a_i。此處 h_1, h_2, …, h_N 兩兩互異。

A 會拔掉一些花，使得剩下的花從左到右的高度為單調遞增（嚴格遞增）。

求剩下花的美麗值總和的最大可能值。

令 dp[i] 表示以第 i 朵花為結尾的遞增子序列所能取得的最大美麗值。
*/

void solve() {
    int n;
    cin >> n;
    SGT<int, MergeMax> tree(n + 1, 0);
    vector<int> h(n), b(n);

    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    for (int i = 0; i < n; ++i) {
        int mx = tree.query(0, h[i]);
        tree.modify(h[i], mx + b[i]);
    }

    cout << tree.query(0, n + 1) << "\n";
}