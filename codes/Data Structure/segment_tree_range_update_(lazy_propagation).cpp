// segment tree
// range query & range modify
class SGT {
    using value_t = int;
    using node_t = pair<value_t, int>;

    int n;
    vector<node_t> t;
    vector<optional<value_t>> lz;
    // [ tv+1 : tv+2*(tm-tl) ) -> left subtree
    int left(int tv) { return tv + 1; }
    int right(int tv, int tl, int tm) { return tv + 2 * (tm - tl); }
    /** differ from case to case **/
    // query is "max" and modify is "add" here
    node_t merge(const node_t& x, const node_t& y) { // associative function
        return max(x, y);
    }
    void update(int tv, int len, const value_t& x) {
        if (!lz[tv]) lz[tv] = x;
        else lz[tv] = lz[tv].value() + x;
        t[tv].fi = t[tv].fi + x;
    }
    /******************************/
    void build(const vector<value_t>& v, int tv, int tl, int tr) {
        if (tr - tl > 1) {
            int tm{(tl + tr) / 2};
            build(v, left(tv), tl, tm);
            build(v, right(tv, tl, tm), tm, tr);
            t[tv] = merge(t[left(tv)], t[right(tv, tl, tm)]);
        } else t[tv] = {v[tl], tl};
    }
    void push(int tv, int tl, int tr) { // lazy propagation
        if (!lz[tv]) return ;
        int tm{(tl + tr) / 2};
        update(left(tv), tm - tl, lz[tv].value());
        update(right(tv, tl, tm), tr - tm, lz[tv].value());
        lz[tv].reset();
    }
    void set(int p, const value_t& x, int tv, int tl, int tr) {
        if (tr - tl > 1) {
            push(tv, tl, tr);
            int tm{(tl + tr) / 2};
            if (p < tm) set(p, x, left(tv), tl, tm);
            else set(p, x, right(tv, tl, tm), tm, tr);
            t[tv] = merge(t[left(tv)], t[right(tv, tl, tm)]);
        } else t[tv].fi = x;
    }
    void rmodify(int l, int r, const value_t& x, int tv, int tl, int tr) {
        if (!(l == tl && r == tr)) {
            push(tv, tl, tr);
            int tm{(tl + tr) / 2};
            if (r <= tm) rmodify(l, r, x, left(tv), tl, tm);
            else if (l >= tm) rmodify(l, r, x, right(tv, tl, tm), tm, tr);
            else rmodify(l, tm, x, left(tv), tl, tm),
                rmodify(tm, r, x, right(tv, tl, tm), tm, tr);
            t[tv] = merge(t[left(tv)], t[right(tv, tl, tm)]);
        } else update(tv, tr - tl, x);
    }
    node_t rquery(int l, int r, int tv, int tl, int tr) {
        if (l == tl && r == tr) return t[tv];
        push(tv, tl, tr);
        int tm{(tl + tr) / 2};
        if (r <= tm) return rquery(l, r, left(tv), tl, tm);
        else if (l >= tm) return rquery(l, r, right(tv, tl, tm), tm, tr);
        else return merge(rquery(l, tm, left(tv), tl, tm),
            rquery(tm, r, right(tv, tl, tm), tm, tr));
    }
public:
    explicit SGT(const vector<value_t>& v) : n{v.size()}, t(2 * n - 1), lz(2 * n - 1) { build(v, 0, 0, n); }
    void set(int p, const value_t& x) { set(p, x, 0, 0, n); }
    void rmodify(int l, int r, const value_t& x) { rmodify(l, r, x, 0, 0, n); } // [l:r)
    node_t rquery(int l, int r) { return rquery(l, r, 0, 0, n); } // [l:r)
};

int main() {
    vector<long long> a = {1, 5, 2, 4, 3};
    SGT st(a);

    auto [val, idx] = st.rquery(0, 5);
    cout << "Initial max: " << val << " at " << idx << "\\n"; // (5, 1)

    st.rmodify(1, 4, 3); // add 3 to indices 1..3
    tie(val, idx) = st.rquery(0, 5);
    cout << "After add: " << val << " at " << idx << "\\n"; // (8, 1)

    st.set(2, 10); // set a[2] = 10
    tie(val, idx) = st.rquery(0, 5);
    cout << "After set: " << val << " at " << idx << "\\n"; // (10, 2)
}