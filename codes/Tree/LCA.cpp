int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int k = 0; diff; ++k) {
        if (diff & 1) a = up[k][a];
        diff >>= 1;
    }
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[k][a] != up[k][b]) {
            a = up[k][a];
            b = up[k][b];
        }
    }
    return up[0][a];
}
 