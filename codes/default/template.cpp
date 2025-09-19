// alias g++='g++ -std=c++14 -fsanitize=undefined -Wall -Wextra -Wshadow -D LOCAL'

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
void dbg() { cerr << '\\n'; }
template<class T, class ...U> void dbg(T a, U ...b) { cerr << a << ' ', dbg(b...); }
template<class T> void org(T l, T r) { while (l != r) cerr << *l++ << ' '; cerr << '\\n'; }
#define debug(args...) (dbg("#> (" + string(#args) + ") = (", args, ")"))
#define orange(args...) (cerr << "#> [" + string(#args) + ") = ", org(args))
#else
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define debug(...) ((void)0)
#define orange(...) ((void)0)
#endif

#define int long long
#define pii pair<int, int>
#define ff first
#define ss second
#define pb push_back
#define SPEEDY ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() {

}

signed main() {
    SPEEDY;

    return 0;
}