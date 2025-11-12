// __builtin_ctz
// 返回輸入數二進制表示從最低位開始（右起）的連續的0的個數；如果傳入0則行為未定義。
int __builtin_ctz (unsigned int x)

// __builtin_clz
// 返回輸入數二進制表示從最高位開始（左起）的連續的0的個數；如果傳入0則行為未定義。
int __builtin_clz (unsigned int x)

// __builtin_ffs
// 返回輸入數二進制表示的最低非0位的下標，下標從1開始計數；如果傳入0則返回0
int __builtin_ffs (unsigned int x)

// __builtin_popcount
// 是返回輸入數二進制表示中1的個數。
int __builtin_popcount (unsigned int x)

// __builtin_parity
// 返回輸入數二進制表示中1的個數的奇偶性，1表示奇數個1，0表示偶數個1。
int __builtin_parity (unsigned int x)

