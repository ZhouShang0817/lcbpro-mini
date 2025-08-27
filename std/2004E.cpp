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
const int N = 1e7;

int lp[N + 1], sg[N + 1];

void solve() {
	int n; cin >> n;
	int ans = 0;
	for(int i = 0; i < n; i ++) {
		int x; cin >> x;
		ans ^= sg[x];
	}
	if(ans) {
		cout << "Alice" << endl;
	}
	else {
		cout << "Bob" << endl;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	vector<int> pr;
	for(int i = 2; i <= N; i ++) {
		if(lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
			if(i == 2) sg[i] = 0;
			else sg[i] = pr.size();
		}
		for(int p : pr) {
			if(1ll * p * i > N) break;
			lp[p * i] = p;
			sg[p * i] = sg[p];
			if(i % p == 0) break;
		}
	}
	sg[1] = 1;

	int Tc = 1;
	cin >> Tc;
	while (Tc --) {
		solve();
	}

	return 0;
}
