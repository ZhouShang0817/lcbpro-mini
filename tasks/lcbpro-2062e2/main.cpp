#include "bits/stdc++.h"
using namespace std;
#define all(x) (x).begin(),(x).end()
const int N = 5e5 + 2;
vector<int> e[N];
int dfn[N], nfd[N], low[N];
int id, n;
void dfs(int u)
{
	nfd[dfn[u] = ++id] = u;
	for (int v : e[u]) erase(e[v], u), dfs(v);
	low[u] = id;
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(15);
	int T; cin >> T;
	while (T--)
	{
		int n, m, i, j;
		cin >> n;
		vector w(n, vector<int>());
		vector<int> c(n + 1), ans;
		for (i = 1; i <= n; i++)
		{
			e[i].clear(); id = 0;
			cin >> j;
			w[j - 1].push_back(i);
		}
		for (i = 1; i < n; i++)
		{
			int u, v;
			cin >> u >> v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		dfs(1);
		int l = n + 1, r = 0;
		set<int> s;
		for (i = n - 1; i >= 0; i--)
		{
			if (s.size())
			{
				for (int u : w[i])
				{
					int mx = 0;
					for (j = dfn[u] - 1; j; j -= j & -j) mx = max(mx, c[j]);
					if ((*s.begin() < dfn[u] || *s.rbegin() > low[u]) && mx <= low[u] && dfn[u] <= l && low[u] >= r)
						ans.push_back(u);
				}
				for (int u : w[i])
				{
					int mn = *s.begin(), mx = *s.rbegin();
					int L = dfn[u], R = low[u];
					if (mn >= L && mx <= R) continue;
					if (mn >= L && mn <= R) mn = *s.upper_bound(R);
					if (mx >= L && mx <= R) mx = *prev(s.lower_bound(L));
					auto fun = [&](int x, int y) {
						if (x > y) swap(x, y);
						l = min(l, y), r = max(r, x);
						for (j = x; j <= n; j += j & -j) c[j] = max(c[j], y);
					};
					fun(mn, dfn[u]);
					fun(mx, dfn[u]);
				}
			}
			for (int u : w[i]) s.insert(dfn[u]);
		}
		sort(all(ans));
		cout << ans.size();
		for (int x : ans) cout << ' ' << x;
		cout << '\n';
	}
}