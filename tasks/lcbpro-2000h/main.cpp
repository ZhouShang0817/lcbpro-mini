#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <cstring>
#include <array>
#include <bitset>

using namespace std;

const int maxn = 2e6, Log = 21, pot = (1 << Log);
const int inf = 1e9;

struct tournament {
	int t[pot * 2];
	void update(int x, int val) {
		t[x] = val;
		for(x /= 2; x; x /= 2) {
			t[x] = max(t[x * 2], t[x * 2 + 1]);
		}
	}
	int query(int val) {
		int x = 1;
		while(x < pot) {
			if(t[x * 2] >= val) {
				x *= 2;
			}
			else {
				x = x * 2 + 1;
			}
		}
		return x - pot;
	}
};

set < int > s;
tournament T;

void solve() {
	int n;
	cin >> n;
	int a;
	int prosl = 0;
	s.insert(0);
	for(int i = 0; i < n; i++) {
		cin >> a;
		s.insert(a);
		T.update(prosl + 1 + pot, a - prosl - 1);
		prosl = a;
	}
	s.insert(inf);
	T.update(prosl + 1 + pot, inf - prosl - 1);
	int m;
	cin >> m;
	char c;
	int x;
	for(int i = 0; i < m; i++) {
		cin >> c >> x;
		if(c == '-') {
			auto it = s.lower_bound(x);
			T.update(x + 1 + pot, 0);
			it = s.erase(it);
			x = *it;
			it--;
			T.update(*it + 1 + pot, x - *it - 1);
		}
		else if(c == '+') {
			auto it = s.lower_bound(x);
			T.update(x + 1 + pot, *it - x - 1);
			it--;
			T.update(*it + 1 + pot, x - *it - 1);
			s.insert(x);
		}
		else {
			cout << T.query(x) << ' ';
		}
	}
	cout << '
';
	while(!s.empty()) {
		if(s.size() > 1) {
			T.update(*s.begin() + 1 + pot, 0);
		}
		s.erase(s.begin());
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
