#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
#define se second 
#define fi first

#define N 500005
int head[N], dep[N], d[N], st[N], sum[N];
int tot = 1, n, m, top;
bitset<N> vis;

struct edge {
	int nxt, to, w;
	int *from;
} e[N << 1];
void add(int u, int v, int w = 0) {
	e[++tot] = {head[u], v, w, &head[u]};
	if (head[u]) e[head[u]].from = &e[tot].nxt;
	head[u] = tot;
}
void del(int i) {
	*e[i].from = e[i].nxt;
	if (e[i].nxt) e[e[i].nxt].from = e[i].from;
	e[i].from = NULL;
}

void dfs(int x) {
	vis[x] = 1;
	for (int i = head[x]; e[i].from != NULL; i = e[i].nxt) {
		int y = e[i].to;
		if (vis[y] || e[i].w) continue;
		dfs(y);
		if (d[y] & 1) {
			del(i);
			del(i ^ 1);
			d[y]--;
			d[x]--;
		}
	}
}

void find(int x) {
	vis[x] = 1;
	for (int i = head[x]; e[i].from != NULL; i = e[i].nxt) {
		int y = e[i].to;
		del(i);
		del(i ^ 1);
		find(y);
	}
	st[++top] = x;
	for (; sum[x]; sum[x]--) st[++top] = x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		x1:
		int u, v, w;
		cin >> n >> m;
		tot = 1;
		for (int i = 1; i <= n; i++) {
			sum[i] = 0;
			vis[i] = 0;
			d[i] = 0;
			head[i] = 0;
		}
		for (int i = 1; i <= m; i++) {
			cin >> u >> v >> w;
			if (u == v) {
				if (w) sum[u]++;
				continue;
			}
			add(u, v, w);
			add(v, u, w);
			d[u]++;
			d[v]++;
		}
		for (int x = 1; x <= n; x++) {
			if (!vis[x]) dfs(x);
		}
		bool con=0;
		for (int i = 1; i <= n; i++) {
			if (d[i] & 1) {
				cout<<"NO
";
				con=1;
				break;
			}
		}
		if(con)continue;
		vector<PII> l;
		for (int u = 1; u <= n; u++) {
			for (int i = head[u]; i; i = e[i].nxt) {
				int v = e[i].to;
				l.push_back({u, v});
				del(i);
				del(i ^ 1);
			}
		}
		for (int i = 1; i <= n; i++) head[i] = 0;
		tot = 1;
		for (auto p : l) {
			add(p.fi, p.se);
			add(p.se, p.fi);
		}
		find(1);
		cout<<"YES
"<<top-1<<'
';
		while (top)cout<<st[top--]<<' ';
		cout << '
';
	}
	return 0;
}