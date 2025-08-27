#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 1000006
///直升机 /直升机 /直升机 尊贵的MEAXQ大人正在摸鱼 /直升机 /直升机 /直升机
int n;
int a[maxn];
int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}
set<int> st;
void solve() {
	st.clear();
	cin >> n;
	int g = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		st.insert(a[i]);
		g = gcd(g, a[i]);
	}
	int now = *min_element(a + 1, a + n + 1), cnt = 1, ans = now;
	st.erase(now);
	while (now > g) {
		int aim, atmp = 1e18;
		for (int tmp : st) {
			if (gcd(now, tmp) < atmp) aim = tmp, atmp = gcd(now, tmp);
		}
		cnt++;
		now = atmp;
		st.erase(aim);
		ans += now;
	}
	ans += (n - cnt) * g;
	cout << ans << '
';
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}