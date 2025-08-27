#include <bits/stdc++.h>
using namespace std;
int dp[1010][1010];

int main() {
	int t;
	cin >> t;
	while (t--) {
		string a, b, c;
		cin >> a >> b >> c;
		int x = a.size(), y = b.size(), z = c.size();
		for (int i = 0; i <= x; i++) {
			for (int j = 0; j <= y; j++) {
				dp[i][j] = 1e9;
			}
		}
		dp[0][0] = 0;
		for (int i = 0; i < z; i++) {
			for (int j = 0; j <= i; j++) {
				int p = j, q = i - j;
				if ((p < x) && (q <= y)) {
					dp[p + 1][q] = min(dp[p + 1][q], dp[p][q] + (a[p] != c[i]));
				}
				if ((q < y) && (p <= x)) {
					dp[p][q + 1] = min(dp[p][q + 1], dp[p][q] + (b[q] != c[i]));
				}
				
			}
		}
		cout << dp[x][y] << "
";
	}
}