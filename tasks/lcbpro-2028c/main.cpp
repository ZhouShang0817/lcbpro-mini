#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	i64 n, m, v;
	std::cin >> n >> m >> v;
	std::vector<i64> a(n, 0), sums(n + 1, 0);

	for(int i = 0; i < n; i++) {
		std::cin >> a[i];
		sums[i + 1] = sums[i] + a[i];
	}

	auto calc = [&] () -> std::vector<int> {
		std::vector<int> pfx(n + 1, 0);

		i64 sum = 0;
		int end = 0;
		while(end < n) {
			while(end < n && sum < v) {
				sum += a[end];
				end++;
				pfx[end] = pfx[end - 1];
			}

			if(sum >= v) {
				pfx[end]++;
				sum = 0;
			}
		}
		return pfx;
	};

	auto pfx = calc();
	std::reverse(a.begin(), a.end());
	auto sfx = calc();
	std::reverse(a.begin(), a.end());
	std::reverse(sfx.begin(), sfx.end());

	if(pfx[n] < m) {
		std::cout << -1 << "
";
		return;
	}
	i64 ans = 0;
	int end = 0;
	for(int i = 0; i <= n; i++) {
		while(end < n && pfx[i] + sfx[end + 1] >= m) {
			end++;
		}
		if(pfx[i] + sfx[end] >= m) {
			ans = std::max(ans, sums[end] - sums[i]);
		}
	}
	std::cout << ans << "
";
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t;
	std::cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}