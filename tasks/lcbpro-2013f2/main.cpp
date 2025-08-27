#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
inline int bit(int x) { return 1<<x; }
struct ST {
	int v[MAXN],f[MAXN][18];
	int cmp(int x,int y) { return v[x]>v[y]?x:y; }
	void upd(int x,int z) {
		v[x]=z,f[x][0]=x;
		for(int k=1;bit(k)<=x;++k) f[x][k]=cmp(f[x][k-1],f[x-bit(k-1)][k-1]);
	}
	int qry(int l,int r) {
		int k=__lg(r-l+1);
		return cmp(f[l+bit(k)-1][k],f[r][k]);
	}
}	A,B;
void upd(int d,int w) { A.upd(d,w+d-1),B.upd(d,w-d); }
bool sol(int n) {
	int mid=(n+1)>>1;
	for(int l=A.qry(1,mid),r=B.qry(mid+1,n);;) {
		if(l-1<=n-r) {
			if(A.v[l]>B.v[B.qry(l+1,n-l+1)]+n) return 1;
			if(l>=mid) return 0;
			l=A.qry(l+1,mid);
		} else {
			if(B.v[r]+n>=A.v[A.qry(n-r+2,r-1)]) return 0;
			if(r<=mid+1) return 1;
			r=B.qry(mid+1,r-1);
		}
	}
}
vector <int> G[MAXN];
int n,d[MAXN],f[MAXN],fa[MAXN];
bool ans[MAXN];
void dfs1(int u,int fz) {
	d[u]=d[fz]+1,f[u]=0,fa[u]=fz;
	for(int v:G[u]) if(v^fz) dfs1(v,u),f[u]=max(f[u],f[v]+1);
}
void dfs2(int u) {
	int mx=0,sx=0;
	for(int v:G[u]) if(v^fa[u]) {
		if(f[v]+1>mx) sx=mx,mx=f[v]+1;
		else sx=max(sx,f[v]+1);
	}
	if(u>1) upd(d[u],mx),ans[u]=sol(d[u]);
	for(int v:G[u]) if(v^fa[u]) upd(d[u],f[v]+1==mx?sx:mx),dfs2(v);
}
void prt(int u) { cout<<(ans[u]?"Alice":"Bob")<<"\n"; }
void out(int u,int v) {
	if(u==v) return prt(u);
	if(d[u]>d[v]) prt(u),out(fa[u],v);
	else out(u,fa[v]),prt(v);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) G[i].clear();
	for(int i=1,u,v;i<n;++i) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	dfs1(1,0),dfs2(1);
	int s,t;
	cin>>s>>t,out(s,t);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}