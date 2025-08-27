// Problem: F3. Speedbreaker Counting (Hard Version)
// Contest: Codeforces - Codeforces Round 975 (Div. 1)
// URL: https://codeforces.com/problemset/problem/2018/F3
// Memory Limit: 1024 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 3030;

ll n, mod, f[maxn][maxn], ans[maxn], g[maxn][maxn][2], h[maxn];

void solve() {
	scanf("%lld%lld", &n, &mod);
	for (int i = 1; i <= n; ++i) {
		ans[i] = 0;
		for (int j = i; j <= n; ++j) {
			g[i][j][0] = g[i][j][1] = 0;
		}
		h[i] = 1;
		for (int j = 1; j <= i; ++j) {
			h[i] = h[i] * (n - max(j, i - j + 1) + 1) % mod;
		}
	}
	g[1][n][0] = 1;
	for (int p = n; p > 1; --p) {
		for (int i = 1, j = p; j <= n; ++i, ++j) {
			g[i + 1][j][0] = (g[i + 1][j][0] + (g[i][j][0] + g[i][j][1]) * (n - (j - i + 1) + 1)) % mod;
			g[i][j - 1][1] = (g[i][j - 1][1] + g[i][j][0] + g[i][j][1] * (n - (j - i + 1) + 1)) % mod;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			f[i][j] = (g[i][j][0] + g[i][j][1]) * h[j - i + 1] % mod;
		}
	}
	for (int p = 1; p <= n; ++p) {
		for (int i = 1, j = p; j <= n; ++i, ++j) {
			f[i][j] = (f[i][j] - f[i - 1][j] - f[i][j + 1] + mod + mod + f[i - 1][j + 1]) % mod;
			ans[j - i + 1] = (ans[j - i + 1] + f[i][j]) % mod;
		}
	}
	ans[0] = 1;
	for (int _ = 0; _ < n; ++_) {
		ans[0] = ans[0] * n % mod;
	}
	for (int i = 1; i <= n; ++i) {
		ans[0] = (ans[0] - ans[i] + mod) % mod;
	}
	for (int i = 0; i <= n; ++i) {
		printf("%lld%c", ans[i], " 
"[i == n]);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			f[i][j] = 0;
		}
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}