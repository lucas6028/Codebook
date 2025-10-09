/*
SPOJ: ORDERSET - Order statistic set

In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations

INSERT(S,x): if x is not in S, insert x into S
DELETE(S,x): if x is in S, delete x from S
and the two type of queries

K-TH(S) : return the k-th smallest element of S
COUNT(S,x): return the number of elements of S smaller than x
*/

const int maxn = 2e5;
int n = 0;
int t[maxn << 1];

void build() {
    for (int i = 0; i < n; ++i) {
        t[i + n] = 0;
    }
    for (int i = n - 1; i >= 1; --i) {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
}

void update(int idx, int val) {
    idx += n;
    if (t[idx] == val) return;
    t[idx] = val;
    for (idx >>= 1; idx >= 1; idx >>= 1) {
        t[idx] = t[idx << 1] + t[idx << 1 | 1];
    }
}

int query(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans += t[l++];
        if (r & 1) ans += t[--r];
    }
    return ans;
}

void solve() {
    int q;
    cin >> q;
    n = 0;
    vector<pii> op(q);
    map<int, int> mp;
    vector<int> to_val;

    memset(t, 0, sizeof(t));

    for (int i = 0; i < q; ++i) {
        char c;
        cin >> c >> op[i].second;
        if (c == 'I') { 
            op[i].first = 0;
            mp[op[i].second] = 1;
        }
        else if (c == 'D') {
            op[i].first = 1;
            mp[op[i].second] = 1;
        }
        else if (c == 'K') {
            op[i].first = 2;
        }
        else {
            op[i].first = 3;
        }
    }

    for (auto& x : mp) {
        x.second = n;
        to_val.push_back(x.first);
        n++;
    }

    build();

    for (pii o : op) {
        if (o.first == 0) {
            int idx = mp[o.second];
            update(idx, 1);
        }
        if (o.first == 1) {
            int idx = mp[o.second];
            update(idx, 0);
        }
        if (o.first == 2) {
            int k = o.second;
            int ans = - 1;
            int l = 0, r = n - 1;
            while (l <= r) {
                int m = l + (r - l) / 2;
                int rk = query(0, m + 1);
                //printf("(m, rk): %lld, %lld\n", m, rk);
                if (rk >= k) {
                    ans = m;
                    r = m - 1;
                }
                else {
                    l = m + 1; 
                }
            }
            if (ans == -1) cout << "invalid\n";
            else cout << to_val[ans] << "\n";
        }
        if (o.first == 3) {
            auto it = mp.lower_bound(o.second);
            if (it == mp.begin() && (it == mp.end() || o.second <= it->first)) {
                cout << "0\n";
            }
            else if (it == mp.end()) {
                cout << query(0, n) << "\n";
            }
            else {
                cout << query(0, it->second) << "\n";
            }
            
        }
    }
}
