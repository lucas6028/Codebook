#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	int n;
	cin >> n;
	ordered_set<int> st;
	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		st.insert(i);
		cin >> p[i];
	}
	for (int i = 0; i < n; i++) {
		int ind;
		cin >> ind;
		ind--;
		int pos = *st.find_by_order(ind);
		cout << st.order_of_key(pos) << ' ';
		st.erase(pos);
		cout << p[pos] << (i == n - 1 ? '\n' : ' ');
	}
}