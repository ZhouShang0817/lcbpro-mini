#pragma GCC optimize("-Ofast","-funroll-all-loops","-ffast-math")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
#define endl '
'
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int a, int b) {
	return rng() % (b - a + 1) + a;
}
string to_string(string s) {
	return s;
}
template <typename T> string to_string(T v) {
	bool first = true;
	string res = "[";
	for (const auto &x : v) {
		if (!first)
			res += ", ";
		first = false;
		res += to_string(x);
	}
	res += "]";
	return res;
}
void dbg_out() {
	cerr << endl;
}
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << to_string(H);
	dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

template<class T> inline void chkmin(T& x, T y) { if (y < x) x = y; }
template<class T> inline void chkmax(T& x, T y) { if (y > x) x = y; }

using i64 = long long;
using ll = long long;

const int oo = 1e9 + 7;
const i64 INF = 1e18 + 7;

void solve() {
	int n; cin >> n;
	
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++) cin >> a[i];
	
	long long ans = 0;
	for(int i = 1; i <= n; i ++) {
		for(int j = i; j <= n; j ++) ans += j - i;
	}
	map<int, int> cnt;
	for(int r = n; r > 0; r --) {
		int sum = 0;
		for(int l = r; l > 0; l --) {
			sum += a[l];
			ans -= cnt[sum];
			cnt[sum] += 1;
		}
	}
	
	cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int Tc = 1;
	cin >> Tc;
	while (Tc --) {
		solve();
	}

	return 0;
}
