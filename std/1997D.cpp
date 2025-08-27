#include <bits/stdc++.h>
using namespace std;
int a[200010];
vector <int> v[200010];
void dfs(int);

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, mn = 1e9;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			v[i].clear();
		}
		for (int i = 2, x; i <= n; i++) {
			cin >> x;
			v[x].push_back(i);
		}
		for (auto t : v[1]) {
			dfs(t);
			mn = min(mn, a[t]);
		}
		cout << a[1] + mn << "
";
	}
}

void dfs(int x) {
	int mn = 1e9;
	for (auto t : v[x]) {
		dfs(t);
		mn = min(mn, a[t]);
	}
	if (mn == 1e9) {
		return;
	}
	a[x] = ((mn <= a[x]) ? (mn) : ((a[x] + mn) / 2));
}