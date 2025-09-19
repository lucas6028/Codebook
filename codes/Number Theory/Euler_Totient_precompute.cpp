constexpr int maxn{100000};
vector<int> phi{[] {
    vector<int> v(maxn + 1); v[1] = 1;
    for (int i{2}; i <= maxn; ++i) {
        if (v[i]) continue;
        v[i] = i;
        for (int j{i}; j <= maxn; j += i) {
            if (!v[j]) v[j] = j;
            v[j] = v[j] / i * (i - 1);
        }
    }
    return v;
}()};
