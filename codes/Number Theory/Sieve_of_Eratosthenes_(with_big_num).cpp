const int MX = 100000;
bool np[MX + 1];
vector<int> prime_numbers;

int init = []() {
    np[0] = np[1] = true;
    for (int i = 2; i <= MX; i++) {
        if (!np[i]) {
            prime_numbers.push_back(i);
            for (int j = i; j <= MX / i; j++) { // 避免溢出的写法
                np[i * j] = true;
            }
        }
    }
    return 0;
}();

bool is_prime(long long n) {
    if (n <= MX) {
        return !np[n];
    }
    for (long long p : prime_numbers) {
        if (p * p > n) {
            break;
        }
        if (n % p == 0) {
            return false;
        }
    }
    return true;
}