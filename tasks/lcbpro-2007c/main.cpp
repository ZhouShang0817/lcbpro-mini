#include <bits/stdc++.h>
using namespace std;
int p[100010];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, a, b;
		cin >> n >> a >> b;
		for (int i = 0; i < n; i++) {
			cin >> p[i];
		}
		int gcd = __gcd(a, b);
		sort(p, p + n);
		for (int i = 1; i < n; i++) {
			p[i] = p[0] + (p[i] - p[0]) % gcd;
		}
		sort(p, p + n);
		int mn = p[n - 1] - p[0], l = -1;
		for (int i = 1; i < n; i++) {
			while (p[l + 1] < p[i]) {
				l++;
			}
			if (l != -1) {
				mn = min(mn, p[l] + gcd - p[i]);
			}
		}
		cout << mn << "
";
	}
}