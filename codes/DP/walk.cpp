/*
DP on graphs - O(N^3 log K)
給定一個簡單的有向圖 G，具有 N 個頂點，編號為 1, 2, …, N。

對於任意 i, j (1 ≤ i, j ≤ N)，給定整數 a_{i,j}，表示是否存在從頂點 i 指向頂點 j 的有向邊。若 a_{i,j} = 1，則存在邊；若 a_{i,j} = 0，則不存在。

求圖中長度為 K 的不同有向路徑數目，對 10^9+7 取模。路徑可重複通過相同邊（即允許重複邊）。

注意：當我們將鄰接矩陣 m 與 m 相乘時，得到的是長度為 2 的路徑數；若取 m 的 p 次方 m^p，則其 (i, j) 元素表示從 i 到 j 的長度為 p 的路徑數。
*/

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> m(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }

    Matrix<int> mat(m);
    mat = power(mat, k);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans += mat.mat[i][j];
            ans %= MOD;
        }
    }
    cout << ans << "\n";
}