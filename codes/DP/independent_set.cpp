/*
DP on Trees - O(N)
有一棵含 N 個頂點的樹，頂點編號為 1,2,…,N。對於每個 i（1 ≤ i ≤ N−1），第 i 條邊連接頂點 x_i 和 y_i。

A 決定將每個頂點塗成白色或黑色，但不允許兩個相鄰的頂點同時為黑色。

求將頂點塗色的方案數，對 10^9+7 取模。

設 dp[i][j] 表示以節點 i 為根的子樹中，在節點 i 顏色為 j 時的塗色方案數（例如 j=0 表示白色，j=1 表示黑色）。
*/

const int maxn = 100001;
vector<int> adj[maxn];
int f[maxn][2];
const int MOD = 1e9 + 7;

void dp(int u, int p) {

    for (int v : adj[u]) {
        if (v != p) {
            dp(v, u);
            f[u][0] = (f[v][0] + f[v][1]) % MOD * f[u][0] % MOD;
            f[u][1] = f[v][0] * f[u][1] % MOD;
        }
    }
}

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        f[i][0] = f[i][1] = 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dp(0, -1);

    cout << (f[0][0] + f[0][1]) % MOD << "\n";
}