// 2. DP
// !n = (n - 1) * (!(n - 1) + !(n - 2)),  with  !0 = 1,  !1 = 0

mint a = 1, b = 0;
cout << 0 << ' ';

for (int i = 2; i <= n; i++) {
    mint c = (i - 1) * (a + b);
    cout << c.val() << ' ';
    a = b;
    b = c;
}