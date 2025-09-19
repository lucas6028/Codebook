// 1. Principle of Inclusion-Exclusion
// n! = n! * Σ (from k=0 to n) [((-1)^k) / (k!)]

mint c = 1;
for (int i = 1; i <= n; i++) {
    c = (c * i) + (i % 2 == 1 ? -1 : 1);
    cout << c.val() << ' ';
}