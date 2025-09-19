/*
期望值 DP - O(N^3)
有 N 盤壽司，編號從 1 到 N。第 i 盤最初有 aᵢ (1 ≤ aᵢ ≤ 3) 塊壽司。

太郎不斷擲一顆編號 1 到 N 的骰子。如果結果是第 i 盤且該盤還有壽司，他就吃掉一塊；否則什麼也不做。

請求出吃完所有壽司所需擲骰子的期望次數。

dp[x][y][z] 代表還有
x 盤剩 1 塊壽司、
y 盤剩 2 塊壽司、
z 盤剩 3 塊壽司時的期望擲骰次數。
*/

const int maxn = 301;
double dp[maxn][maxn][maxn];
int n;

double dfs(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0) return 0;
    if (x == 0 && y == 0 && z == 0) return 0;
    if (dp[x][y][z] > 0) return dp[x][y][z];
    double ans = n + x * dfs(x - 1, y, z)
                   + y * dfs(x + 1, y - 1, z)
                   + z * dfs(x, y + 1, z - 1);
    return dp[x][y][z] = ans / (x + y + z);
}

void solve() {
    cin >> n;
    vector<int> a(n);
    memset(dp, -1, sizeof(dp));
    vector<int> freq(4, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        freq[a[i]]++;
    }

    cout << fixed << setprecision(10) << dfs(freq[1], freq[2], freq[3]) << "\n";
}