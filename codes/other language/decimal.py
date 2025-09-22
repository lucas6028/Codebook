# 使用 decimal 模組來處理高精度小數運算
from decimal import *
setcontext(Context(prec=MAX_PREC, Emax=MAX_EMAX, rounding=ROUND_FLOOR))
print(Decimal(input()) * Decimal(input()))

# 將小數轉成分數，方便做近似或理論分析，且可以限制分母大小。
from fractions import Fraction
Fraction('3.14159').limit_denominator(10).numerator # 22

# 設定精確度
from decimal import Decimal, getcontext

# 精確位數設定
getcontext().prec = 70 

n = 100
# 指定n為高精確度的物件
n = Decimal(n)
n /= 7
print(n)

# 將小數轉成分數
from fractions import Fraction

n = 1.5654
# 建立一個轉換物件
n = Fraction(n)

print(n)

