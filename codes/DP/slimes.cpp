/*
Range DP - O(N^3)
有 N 個史萊姆排成一列。最初，從左邊數來第 i 個史萊姆的大小為 ai。

A 想要把所有史萊姆合併成一個更大的史萊姆。他會重複執行以下操作，直到只剩下一個史萊姆為止：

選擇兩個相鄰的史萊姆，將它們合併成一個新的史萊姆。新史萊姆的大小為 x+y，其中 x 和 y 是合併前兩個史萊姆的大小。
這時會產生 x+y 的花費。合併時，史萊姆的相對位置不會改變。
請求出合併所有史萊姆所需的最小總花費。

令 dp[i][j] 表示將第 i 個到第 j 個史萊姆合併成一個史萊姆的最小花費。
*/

const int maxn = 401;
const int INF = 1e18;
int dp[maxn][maxn];
int a[maxn];
int prefix[maxn + 1];

int f(int i, int j) {
    if (i + 1 == j) {
        return a[i] + a[j];
    }
    if (i == j) {
        return 0;
    }
    if (dp[i][j] != INF) {
        return dp[i][j];
    }
    //cerr << i << " " << j << "\n";
    
    int ans = INF;
    for (int k = i; k < j; ++k) {
        ans = min(ans, f(i, k) + f(k + 1, j));
    }
    return dp[i][j] = ans + (prefix[j + 1] - prefix[i]);
}