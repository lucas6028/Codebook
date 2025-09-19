// longest common subsequence
int LCS(const vector<int>& a, const vector<int>& b) {
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
    for (int i{1}; i <= int(a.size()); ++i)
        for (int j{1}; j <= int(b.size()); ++j) {
            dp[i][j] = max(dp[i][j], max(dp[i - 1][j], dp[i][j - 1]));
            if (a[i - 1] == b[j - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
        }
    return dp[a.size()][b.size()];
}