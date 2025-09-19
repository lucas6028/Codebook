// 01 背包, 背包承重大 (1e9), 物品價值和較小 (1e5)

const int maxn = 101;
const int maxv = 100001;
int weight[maxn];
int cost[maxn];
int dp[maxv];

void solve() {
    int n, w;
    cin >> n >> w;

    for (int i = 0; i < n; ++i) {
        cin >> weight[i] >> cost[i];
    }
    fill(dp, dp + maxv, 1e18);

    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = maxv - 1; j >= 0; --j) {
            if (dp[j] + weight[i] <= w) {
                dp[j + cost[i]] = min(dp[j + cost[i]], dp[j] + weight[i]);
            }
        }
    }

    for (int i = maxv - 1; i >= 0; --i){
        if (dp[i] != 1e18) {
            cout << i << "\n";
            return;
        }
    }
}