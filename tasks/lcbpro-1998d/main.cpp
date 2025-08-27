#include <bits/stdc++.h>
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=2e5+10;
int T,n,a[N],f[N];
vector<int> g[N];
int dfs(int u){
	if(!g[u].size()) return a[u];
	int mn=0x3f3f3f3f;
	for(auto v:g[u]) mn=min(mn,dfs(v));
	if(a[u]>=mn) return mn;
	else return (a[u]+mn)>>1;
}
void solve(){
	read(n);
	int mx=0;
	rep(i,1,n) read(a[i]),g[i].clear(),mx=max(mx,a[i]);
	rep(i,2,n){
		read(f[i]);
		g[f[i]].push_back(i);
	}
	int mn=0x3f3f3f3f;
	for(auto v:g[1]) mn=min(mn,dfs(v));
	printf("%d
",a[1]+mn);
}
int main(){
	read(T);while(T--) solve();
	return 0;
}
