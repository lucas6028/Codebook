import sys

sys.setrecursionlimit(2000000) 

def solve():
    S = sys.stdin.readline().strip()
    try:
        N = int(S)
    except ValueError:
        N = 0
    if N == 0:
        print(1)
        return
    low = 1
    high = 700000  # Safely larger than 500000 * 1.3
    ans = high + 1 
    while low <= high:
        L_mid = (low + high) // 2
        if L_mid <= 0:  # Avoid 6^0 or 6^negative
            low = L_mid + 1
            continue
        val = pow(6, L_mid)
        if val > N:
            ans = L_mid
            high = L_mid - 1
        else:
            low = L_mid + 1
    print(ans)
solve()