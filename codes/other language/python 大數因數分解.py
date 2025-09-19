# 大數因數分解 (使用 Pollard's Rho 與 Miller-Rabin)
import sys, random
from math import gcd

# Miller-Rabin 檢定（機率性質數判定）
def is_probable_prime(n, k=12):
    if n < 2:
        return False
    # 先檢查一些小質數
    small_primes = [2,3,5,7,11,13,17,19,23,29]
    for p in small_primes:
        if n % p == 0:
            return n == p
    # 把 n-1 寫成 d * 2^s
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    # 重複 k 次隨機測試
    for _ in range(k):
        a = random.randrange(2, n - 1)  # 隨機挑一個測試基數
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        composite = True
        for __ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                composite = False
                break
        if composite:
            return False
    return True

# Pollard's Rho 演算法（找非平凡因數）
def pollards_rho(n):
    if n % 2 == 0:
        return 2
    if n % 3 == 0:
        return 3
    # 隨機多項式 (x^2 + c) mod n
    while True:
        c = random.randrange(1, n-1)     # 隨機挑選常數 c
        x = random.randrange(2, n-1)     # 起始點
        y = x
        d = 1
        while d == 1:
            x = (pow(x, 2, n) + c) % n   # x -> f(x)
            y = (pow(y, 2, n) + c) % n   # y -> f(f(y))，走兩步
            y = (pow(y, 2, n) + c) % n
            d = gcd(abs(x - y), n)       # 計算兩者差的 gcd
            if d == n:                   # 失敗就重試
                break
        if d > 1 and d < n:              # 找到非平凡因數
            return d

# 遞迴分解
def factor(n, out):
    if n == 1:
        return
    if is_probable_prime(n):
        out.append(n)
    else:
        d = pollards_rho(n)
        while d is None or d == n:  # 偶爾失敗就重試
            d = pollards_rho(n)
        factor(d, out)
        factor(n // d, out)

def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    # 每個 token 當作一個數字
    for token in data:
        try:
            n = int(token)
        except:
            continue
        if n <= 1:
            print(n)
            continue
        facs = []
        factor(n, facs)
        facs.sort()
        # 輸出因數
        print(" ".join(str(x) for x in facs))

if __name__ == "__main__":
    random.seed()  # 使用系統時間作為隨機種子
    main()

