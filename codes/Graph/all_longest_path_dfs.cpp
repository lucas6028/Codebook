// all longest path (generalization of the tree diameter problem)
vector<tuple<int, int, int>> dp{};
// [mx1, x, mx2] the path of mx1 goes through x
int dfs1(int u, int w = -1) {
    int mx{0};
    for (auto& v : adj[u])
        if (v != w) {
            auto l{1 + dfs1(v, u)};
            mx = max(mx, l);

            auto& [mx1, x, mx2]{dp[u]};
            if (l >= mx1) mx2 = mx1, mx1 = l, x = v;
            else if (l > mx2) mx2 = l;
        }
    return mx;
}
void dfs2(int u, int w = -1) {
    if (w != -1) {
        int tmx;
        { // calculate the longest path through parent
            auto& [mx1, x, mx2]{dp[w]};
            if (x != u) tmx = mx1 + 1;
            else tmx = mx2 + 1;
        }
        { // update the path
            auto& [mx1, x, mx2]{dp[u]};
            if (tmx >= mx1) mx2 = mx1, mx1 = tmx, x = w;
            else if (tmx > mx2) mx2 = tmx;
        }
    }
    for (auto& v : adj[u])
        if (v != w) dfs2(v, u);
}
void all_longest_path() {
    dfs1(0), dfs2(0);
}