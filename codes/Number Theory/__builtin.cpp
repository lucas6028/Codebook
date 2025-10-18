// __builtin_ctz
// 這個函數作用是返回輸入數二進制表示從最低位開始（右起）的連續的0的個數；如果傳入0則行為未定義。

int __builtin_ctz (unsigned int x)
Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.

int __builtin_ctzl (unsigned long)
Similar to __builtin_ctz, except the argument type is unsigned long.

int __builtin_ctzll (unsigned long long)
Similar to __builtin_ctz, except the argument type is unsigned long long.


// __builtin_clz
// 這個函數作用是返回輸入數二進制表示從最高位開始（左起）的連續的0的個數；如果傳入0則行為未定義。

int __builtin_clz (unsigned int x)
Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.

int __builtin_clzl (unsigned long)
Similar to __builtin_clz, except the argument type is unsigned long.

int __builtin_clzll (unsigned long long)
Similar to __builtin_clz, except the argument type is unsigned long long.


// __builtin_ffs
//  這個函數作用是返回輸入數二進制表示的最低非0位的下標，下標從1開始計數；如果傳入0則返回0

int __builtin_ffs (unsigned int x)
Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.

int __builtin_ffsl (unsigned long)
Similar to __builtin_ffs, except the argument type is unsigned long.

int __builtin_ffsll (unsigned long long)
Similar to __builtin_ffs, except the argument type is unsigned long long.


// __builtin_popcount
// 這個函數作用是返回輸入數二進制表示中1的個數。

int __builtin_popcount (unsigned int x)
Returns the number of 1-bits in x.

int __builtin_popcountl (unsigned long)
Similar to __builtin_popcount, except the argument type is unsigned long.

int __builtin_popcountll (unsigned long long)
Similar to __builtin_popcount, except the argument type is unsigned long long.


// __builtin_parity
// 這個函數作用是返回輸入數二進制表示中1的個數的奇偶性，1表示奇數個1，0表示偶數個1。

int __builtin_parity (unsigned int x)
Returns the parity of x, i.e. the number of 1-bits in x modulo 2.

int __builtin_parityl (unsigned long)
Similar to __builtin_parity, except the argument type is unsigned long.

int __builtin_parityll (unsigned long long)
Similar to __builtin_parity, except the argument type is unsigned long long.

