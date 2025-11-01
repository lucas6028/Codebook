int n, s, t, cnt, inf = 1e17;
vector<vector<int>> adj;
int level[100000], ptr[100000], rev[100000], to[100000], cap[100000];
void add(int a, int b, int c) {
    int id = cnt++, rid = cnt++;
    to[id] = b;
    to[rid] = a;
    cap[id] = c;
    cap[rid] = 0;

    rev[id] = rid;
    rev[rid] = id;
    adj[a].push_back(id);
    adj[b].push_back(rid);
}
bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while(!q.empty()) {
        int curr = q.front(); q.pop();
        for(int id: adj[curr]) {
            int next = to[id];
            if(cap[id] > 0 && level[next] == -1) {
                level[next] = level[curr] + 1;
                q.push(next);
            }
        }
    }
    return level[t] != -1;
}
int dfs(int curr, int flow) {
    if(curr == t || flow == 0) return flow;

    for(; ptr[curr] < adj[curr].size(); ptr[curr]++) {
        int id = adj[curr][ptr[curr]];
        int next = to[id];
       
        if(cap[id] > 0 && level[next] == level[curr] + 1) {
            int temp = dfs(next, min(flow, cap[id]));
            if(temp == 0) continue;

            int rid = rev[id];
            cap[id] -= temp;
            cap[rid] += temp;
            return temp;
        }
    }
    return 0;
}
int maxflow() {
    int flow = 0;
    while(bfs()) {
        memset(ptr, 0, sizeof(ptr));
        while(true) {
            int temp = dfs(s, inf);
            if(temp == 0) break;
            flow += temp;
        }
    }
    return flow;
}