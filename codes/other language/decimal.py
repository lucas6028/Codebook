# 使用 decimal 模組來處理高精度小數運算
from decimal import *
setcontext ( Context ( prec
= MAX_PREC , Emax = MAX_EMAX , rounding = ROUND_FLOOR ) )
print ( Decimal ( input () ) * Decimal ( input () ) )

# 將小數轉成分數，方便做近似或理論分析，且可以限制分母大小。
from fractions import Fraction
Fraction
( '3.14159 ') . limit_denominator (1 0). numerator # 22