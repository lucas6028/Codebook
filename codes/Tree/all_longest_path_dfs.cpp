// all longest path (generalization of the tree diameter problem)
vector<tuple<int, int, int>> dp{};
// [mx1, x, mx2] the path of mx1 goes through x

int dfs1(int u, int p = -1) {
    int mx = 0;
    for (int v : adj[u]) {
        if (v != p) {
            int len = 1 + dfs1(v, u);
            mx = max(mx, len);

            auto& [mx1, x, mx2] = dp[u];
            if (len >= mx1) {
                mx2 = mx1;
                mx1 = len;
                x = v;
            }
            else if (len > mx2) {
                mx2 = len;
            }
        }
    }
    return mx;
}

void dfs2(int u, int p = -1) {
    if (p != -1) {
        int tmx;
        {   // calculate the longest path through parent
            auto& [mx1, x, mx2] = dp[p];
            if (x != u) tmx = mx1 + 1;
            else tmx = mx2 + 1;
        }
        {   // update the path
            auto& [mx1, x, mx2] = dp[u];
            if (tmx >= mx1) {
                mx2 = mx1;
                mx1 = tmx;
                x = p;
            }
            else if (tmx > mx2) {
                mx2 = tmx;
            }
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u);
        }
    }
}

void all_longest_path() {
    dp.resize(n);
    dfs1(0), dfs2(0);
}