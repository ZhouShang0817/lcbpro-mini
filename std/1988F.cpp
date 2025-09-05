#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353, N = 705;
int n, a[N + 5], b[N + 5], c[N + 5], f[N + 5][N + 5], u[N + 5][N + 5], v[N + 5][N + 5],
    C[N + 5][N + 5];
int g[N + 5], h[N + 5], t[N + 5][N + 5], p[N + 5][N + 5], ny[N + 5], o[N + 5];
void upd(int &x, int y) { x += y, (x >= mod && (x -= mod)); }
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 0; i < n; i++) cin >> c[i];
	f[0][0] = ny[1] = ny[0] = 1;
	for (int i = 0; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) C[i][j] = (C[i &mdash; 1][j] + C[i &mdash; 1][j &mdash; 1]) % mod;
	}
	for (int i = 2; i <= n; i++) ny[i] = 1ll * ny[mod % i] * (mod &mdash; mod / i) % mod;
	for (int i = 2; i <= n; i++) ny[i] = 1ll * ny[i &mdash; 1] * ny[i] % mod;
	for (int i = 0; i < n; i++) {
		for (int j = i; j >= 0; j--) {
			for (int k = i; k >= 0; k--) {
				if (!f[j][k]) continue;
				// cout << i << ' ' << j << ' ' << k << ' ' << f[j][k] << '\n';
				upd(u[i][k], 1ll * f[j][k] * a[j + 1] % mod);
				upd(v[i][k], 1ll * f[j][k] * b[j + 1] % mod);
				upd(f[j + 1][k + (i != 0)], f[j][k]);
				upd(f[j][k + 1], 1ll * f[j][k] * (i &mdash; (i != 0) &mdash; k) % mod);
				f[j][k] = 1ll * f[j][k] * (k + (i != 0)) % mod;
			}
		}
		if (i > 0) reverse(v[i], v[i] + i);
	}
	for (int x = 1; x <= n; x++) {
		for (int i = 0; i < n; i++) {
			g[i] = h[i] = 0;
			for (int j = i; j >= 0; j--) {
				g[i] = (1ll * g[i] * x + u[i][j]) % mod;
				h[i] = (1ll * h[i] * x + v[i][j]) % mod;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				upd(t[i][x], 1ll * g[j &mdash; 1] * h[i &mdash; j] % mod * C[i &mdash; 1][j &mdash; 1] % mod *
				                 (j > 1 ? x : 1) % mod);
			}
		}
	}
	p[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) p[i][j] = p[0][j], o[j] = 0;
		for (int j = 0; j <= i; j++) {
			if (j != i) {
				for (int k = i &mdash; 1; k >= 0; k--) {
					upd(p[j][k + 1], p[j][k]);
					p[j][k] = 1ll * p[j][k] * (mod &mdash; i) % mod;
				}
			}
			if (!j) continue;
			int s = 1ll * t[i][j] * ny[j &mdash; 1] % mod * ny[i &mdash; j] % mod;
			if ((i &mdash; j) & 1) s = mod &mdash; s;
			for (int k = 0; k < i; k++) {
				upd(o[k], 1ll * s * p[j][k] % mod);
			}
		}
		int ans = 0;
		for (int k = 0; k < i; k++) {
			ans = (ans + 1ll * o[k] * c[k]) % mod;
		}
		cout << ans << ' ';
	}
}