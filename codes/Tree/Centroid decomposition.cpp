// Centroid Decomposition
// Problem: Given a tree with N nodes (1-indexed) and M queries. Each query is one of the following two types:
// 1 v: Paint node v red.
// 2 v: Print the minimal distance between node v and any red node.
// Initially, only node 1 is red.
// Constraints: 1 <= N, M <= 10^5
// Time complexity: O((N + M) log N)

vector<vector<int>> adj;
vector<int> subtree_size;
// min_dist[v] = the minimal distance between v and a red node
vector<int> min_dist;
vector<bool> is_removed;
vector<vector<pii>> ancestors;
 
int get_subtree_size(int u, int p = -1) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v == p || is_removed[v]) continue;
        subtree_size[u] += get_subtree_size(v, u);
    }
    return subtree_size[u];
}
 
int get_centroid(int u, int tree_size, int p = -1) {
    for (int v : adj[u]) {
        if (v == p || is_removed[v]) continue;
        if (subtree_size[v] * 2 > tree_size) {
            return get_centroid(v, tree_size, u);
        }
    }
    return u;
}
 
// Calculate the distance between current `u` and the `centroid` it belongs.
void get_dist(int u, int centroid, int p = -1, int cur_dist = 1) {
    for (int v : adj[u]) {
        if (v == p || is_removed[v]) continue;
        cur_dist++;
        get_dist(v, centroid, u, cur_dist);
        cur_dist--;
    }
    ancestors[u].emplace_back(centroid, cur_dist);
}
 
void build_centroid_decomp(int u = 0) {
    int centroid = get_centroid(u, get_subtree_size(u));
 
    // For all nodes in the subtree rooted at `centroid`, calculate their distance to the centroid
    for (int v : adj[centroid]) {
        if (is_removed[v]) continue;
        get_dist(v, centroid, centroid);
    }
 
    is_removed[centroid] = true;
    for (int v : adj[centroid]) {
        if (is_removed[v]) continue;
        build_centroid_decomp(v);
    }
}
 
// Paint `node` red by updating all of its ancestors' minimal distances to a red node
void paint(int u) {
    for (auto &[ancestor, dist] : ancestors[u]) {
        min_dist[ancestor] = min(min_dist[ancestor], dist);
    }
    min_dist[u] = 0;
}
 
// Print the minimal distance between `u` to a red node.
void query(int u) {
    int ans = min_dist[u];
    for (auto &[ancestor, dist] : ancestors[u]) {
        if (!dist) continue;
        ans = min(ans, dist + min_dist[ancestor]);
    }
    cout << ans << "\n";
}
 
void solve() {
    int N, M;
    cin >> N >> M;
 
    adj.assign(N, vector<int>());
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    subtree_size.assign(N, 0);
    ancestors.assign(N, vector<pii>());
    is_removed.assign(N, false);
    build_centroid_decomp();
 
    min_dist.assign(N, INF);
    paint(0);
    for (int i = 0; i < M; ++i) {
        int t, v;
        cin >> t >> v;
        v--;
        if (t == 1) {
            paint(v);
        }
        else {
            query(v);
        }
    }
}