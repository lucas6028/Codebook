template<typename T, typename Compare = less<T>>
struct lp {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> cnt;
    size_t sz = 0;
    void real_remove() {
        while(!pq.empty() && cnt[pq.top()] > 0) {
            cnt[pq.top()]--;
            pq.pop();
        }
    }
    size_t size() {
        return sz;
    }
    void remove(T n) {
        cnt[n]++;
        sz--;
    }
    T top() {
        real_remove();
        return pq.top();
    }
    void push(T n) {
        pq.push(n);
        sz++;
    }
    void pop() {
        real_remove();
        sz--;
        pq.pop();
    }
};