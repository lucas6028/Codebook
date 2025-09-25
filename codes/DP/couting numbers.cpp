/*
區間 DP - O(digits*10)
您的任務是計算在區間 a 到 b 之間，沒有任何相鄰兩位數字相同的整數的個數。

定義 dp[pos][prev_digit][is_tight][is_started] 為從位置 pos 到結尾的有效整數數量，
其中 prev_digit 是位置 pos-1 的數字，
is_tight 表示是否受原數字前綴的限制，
is_started 表示是否已開始構成有效數字（用以避免計入前導零）。
*/

// dp[pos][prev_digit][is_tight][is_started]
int dp[20][10][2][2]; 
string s;
 
int f(int pos, int prev_digit, bool is_tight, bool is_started) {
    if (pos == (int)s.size()) {
        return 1;
    }
    if (dp[pos][prev_digit][is_tight][is_started] != -1) {
        return dp[pos][prev_digit][is_tight][is_started];
    }
 
    int ans = 0;
    int max_d = is_tight ? (s[pos] - '0') : 9;
    for (int d = 0; d <= max_d; ++d) {
        if (is_started && d == prev_digit) {
            continue;
        }
 
        bool new_is_started = is_started || (d > 0);
        bool new_is_tight = is_tight && (d == max_d);
        ans += f(pos + 1, d, new_is_tight, new_is_started);
    }
 
    return dp[pos][prev_digit][is_tight][is_started] = ans;
}
 
int count(int x) {
    if (x < 0) return 0;
    s = to_string(x);
    memset(dp, -1, sizeof(dp));
    return f(0, 0, true, false);
}
 
void solve() {
    int a, b;
    cin >> a >> b;
 
    int ca = count(a - 1);
    int cb = count(b);
    cout << cb - ca << "\n";
}