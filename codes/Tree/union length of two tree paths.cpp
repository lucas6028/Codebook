/*
Problem: Given a tree and queries (a,b,c,d), find the size of the union of nodes on paths a↔b and c↔d.

Let P1 be the nodes on the path a↔b and P2 the nodes on c↔d.
We want |P1 ∪ P2| = |P1| + |P2| − |P1 ∩ P2|.
|P1| = dist(a,b) + 1, |P2| = dist(c,d) + 1. So the only hard part is |P1 ∩ P2|.

Key facts for trees:

The intersection of two simple paths is itself either empty or a simple path.

Any endpoint of that intersection must be one of the LCAs among endpoint pairs of the two paths. 


So for each query:

compute the 6 candidate LCAs,

keep those candidates that lie on both paths (test with distances),

if none → intersection size = 0; if one → intersection size = 1; 
otherwise take the two kept candidates with greatest depth (they are the endpoints of the intersection) 
and intersection size = dist(p,q) + 1.
*/

const int LOG = 32;

const int maxn = 1e5;
int depth[maxn];
vector<int> adj[maxn];
int up[LOG + 1][maxn];
int n, q;

void dfs(int u, int p = -1) {
    up[0][u] = (p == -1 ? u : p);
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int dist(int a, int b) {
    int c = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
}

// check z on path u-v
bool on_path(int z, int u, int v) {
    return dist(u, z) + dist(z, v) == dist(u, v);
}

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(depth, 0, sizeof(depth));
    dfs(0, -1);

    for (int k = 1; k < LOG; ++k) {
        for (int v = 0; v < n; ++v) {
            up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--, c--, d--;
        int len1 = dist(a, b) + 1;
        int len2 = dist(c, d) + 1;

        array<int, 6> cand = {
            lca(a, b), lca(c, d),
            lca(a, c), lca(a, d),
            lca(b, c), lca(b, d)
        };

        vector<int> good;
        for (int z : cand) {
            if (on_path(z, a, b) && on_path(z, c, d)) {
                good.push_back(z);
            }
        }

        int inter = 0;
        if (good.size() == 1) {
            inter = 1;
        }
        else if (good.size() > 1) {
            sort(good.begin(), good.end(), [&](int x, int y) {
                return depth[x] > depth[y];
            });
            int p = good[0], qn = good[1];
            inter = dist(p, qn) + 1;
        }
        cout << (len1 + len2 - inter) << "\n";
    }
}
