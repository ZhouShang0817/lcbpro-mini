#include <bits/stdc++.h>
#define FL(i, a, b) for (int i = (a); i <= (b); ++i)
#define FR(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 1e6 + 10;
const int MOD = 998244353;
int n, pre[N], f[N];
char s[N];
void AddTo(int &x, int y) {
	x = (x + y >= MOD? x + y - MOD : x + y);
}
void Solve() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	f[0] = 1;
	FL(i, 1, n) {
		if (s[i] == '1') {
			pre[i] = i;
		} else {
			pre[i] = pre[i - 1];
		}
	}
	int j = n, cnt = 0, sum = 1, ans = 0;
	FR(i, n, 1) {
		for (; j > pre[i]; --j) {
			AddTo(cnt, f[i - j]);
		}
		if (pre[i]) {
			if (s[i] == '0') {
				AddTo(f[i - pre[i]], cnt);
				AddTo(sum, cnt);
			}
			AddTo(cnt, MOD - f[(i - 1) - pre[i]]);
		}
		AddTo(ans, sum);
		AddTo(sum, MOD - f[i - 1]), f[i - 1] = 0;
	}
	printf("%d
", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		Solve();
	}
	return 0;
}
