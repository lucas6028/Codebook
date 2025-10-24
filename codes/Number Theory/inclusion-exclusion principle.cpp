/*
includsion-exclusion principle: U A = Σ |A_i| - Σ |A_i ∩ A_j| + Σ |A_i ∩ A_j ∩ A_k| - ...

if f(n) = Σ g(d) for all d|n
then g(n) = Σ μ(d) * f(n/d) for all d|n

where μ(d) is the mobius function defined as:

|U A| = Σ μ(d) * |A_d|
where A_d = {x ∈ U : d|x}
μ(d) = 1 if d is a product of even number of distinct primes
μ(d) = -1 if d is a product of odd number of distinct primes
μ(d) = 0 if d has a squared prime factor
*/

/*
problem: In number theory we call an integer square-free if it is not divisible by a perfect square, except 1. You have to count them!
square-free number: An integer n is square-free if no p^2 divides n.
*/
const int VALMAX = 1e7;

int mobius[VALMAX];

int main() {
	int test_num;
	cin >> test_num;

	mobius[1] = -1;
	for (int i = 1; i < VALMAX; i++) {
		if (mobius[i]) {
			mobius[i] = -mobius[i];
			for (int j = 2 * i; j < VALMAX; j += i) { mobius[j] += mobius[i]; }
		}
	}

	for (int t = 0; t < test_num; t++) {
		long long n;
		long long ans = 0;
		cin >> n;
		for (int i = 1; 1LL * i * i <= n; i++) {
			ans += mobius[i] * n / ((long long)i * i);
		}
		cout << ans << '\n';
	}
}

/* 
problem: Given N cows (2 <= N <= 50,000), each listing five favorite ice cream flavors,
 where two cows are compatible if they share at least one flavor, 
determine the number of cow pairs that are not compatible. 

ans = n * (n - 1) / 2 - Σ |A_i| + Σ |A_i ∩ A_j| - Σ |A_i ∩ A_j ∩ A_k| + ...
where A_i is the set of cows that like flavor i
*/

void solve() {
    int n;
    cin >> n;
    vector<array<int, 5>> vc(n);

    map<vector<int>, int> subsets;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> vc[i][j];
        }

        sort(vc[i].begin(), vc[i].end());
        for (int mask = 1; mask < (1<<5); ++mask) {
            vector<int> subset;
            for (int b = 0; b < 5; ++b) {
                if (mask & (1<<b)) {
                    subset.push_back(vc[i][b]);
                }
            }
            subsets[subset]++;
        }
    }

    int ans = n * (n - 1) / 2;
    for (const auto& [subset, freq] : subsets) {
        ans -= (subset.size() % 2 == 1 ? 1 : -1) * freq * (freq - 1) / 2;
    }
    cout << ans << "\n";
}
