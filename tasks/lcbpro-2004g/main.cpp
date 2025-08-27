#pragma GCC optimize("-Ofast","-funroll-all-loops","-ffast-math")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
//#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,abm,popcnt,mmx")
#include <bits/stdc++.h>
using namespace std;
#define endl '
'
#define YES cout << "YES"<<endl;
#define NO cout << "NO"<<endl;
#define all(x) (x).begin(), (x).end()
#define pb emplace_back

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

template<class T> inline void chkmin(T& x, T y) {
	if (y < x) x = y;
}
template<class T> inline void chkmax(T& x, T y) {
	if (y > x) x = y;
}

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
typedef long long ll;

const i64 INF = 1LL << 62;
const int oo = 1e9 + 7;
const int mod = 1e9 + 7;
const int MX = 200005;

using matrix = array<array<long long, 10>, 10>;

matrix unit;
vector<matrix> a(10);
void init(matrix &u, int f) {
	for(int i = 0; i < 10; i ++) {
		for(int j = 0; j < 10; j ++) {
			if(i == j && f) u[i][j] = 0;
			else u[i][j] = oo;
		}
	}
}

matrix operator *(matrix &a, matrix &b) {
	matrix c; init(c, 0);
	for(int i = 0; i < 10; i ++) {
		for(int j = 0; j < 10; j ++) {
			for(int k = 0; k < 10; k ++) {
				if(a[i][k] == oo || b[k][j] == oo) continue;
				c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
			}
		}
	}
	return c;
}

void solve() {	
	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector<matrix> pre(n), suf(n);
	for(int i = 0; i < n; i ++) {
		pre[i] = (i % k == 0 ? unit : pre[i - 1]) * a[s[i] - '0'];
	}
	
	for(int i = n - 1; i >= 0; i --) {
		suf[i] = a[s[i] - '0'] * (((i + 1) % k == 0 || i == n - 1) ? unit : suf[i + 1]);
	}
	
	for(int l = 0; l + k <= n; l ++) {
		if(l % k == 0) {
			cout << pre[l + k - 1][0][0] << " ";
		}
		else {
			matrix c = suf[l] * pre[l + k - 1];
			cout << c[0][0] << " ";
		}
	}
	cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	init(unit, 1);
	for(int k = 1; k < 10; k ++) {
		init(a[k], 0);
		for(int i = 1; i < 10; i ++) {
			a[k][i][0] = a[k][i][i] = i;
		}
		a[k][0][k] = 0;
	}

	int Tc = 1;
	while (Tc --) {
		solve();
	}
	
	return 0;
}
