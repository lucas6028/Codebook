// all longest path in DAG
// 1. topological sort
vector<int> in(n, 0);
for (int i = 0; i < m; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    in[b]++;
}

vector<int> topo; // sequence of top sort
queue<int> q;
for (int i = 0; i < n; ++i) {
    if (in[i] == 0) {
        q.push(i);
    }
}
while (!q.empty()) {
    int pa = q.front();
    q.pop();
    topo.push_back(pa);
    for (auto& [child, w] : adj[pa]) {
        in[child]--;
        if (in[child] == 0) {
            q.push(child);
        }
    }
}

// all longest path
vector<int> dist(n, INT_MIN);
vector<vector<int>> parents(n);
dist[0] = process[0];

for (int u : topo) {
    for (auto& [v, w] : adj[u]) {
        if (dist[v] < dist[u] + process[v] + w) {
            dist[v] = dist[u] + process[v] + w;
            parents[v] = {u};
        }
        else if (dist[v] == dist[u] + process[v] + w) {
            parents[v].push_back(u);
        }
    }
}

cout << dist[n - 1];