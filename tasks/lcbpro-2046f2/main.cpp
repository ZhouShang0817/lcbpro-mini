#include<bits/stdc++.h>
using namespace std;
inline void chkmin(int &x,const int &y) { x=y<x?y:x; }
inline void chkmax(int &x,const int &y) { x=y>x?y:x; }
const int MAXN=2e5+5;
int n,a[MAXN],pr[MAXN],sf[MAXN],wys[MAXN];
char s[MAXN];
set <int> ps[4];
struct FenwickTree {
	int tr[MAXN],s;
	void init() { fill(tr+1,tr+n+1,0); }
	void add(int x,int v) { for(;x<=n;x+=x&-x) tr[x]+=v; }
	int qry(int x) { for(s=0;x;x&=x-1) s+=tr[x]; return s; }
}	TR;
int L[MAXN][4][4],R[MAXN][4][4];
void solve() {
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;++i) a[i]=(s[i]=='?'?0:(s[i]=='D'?1:(s[i]=='X'?2:3)));
	for(int i=1;i<=n;++i) {
		memset(L[i],0x3f,sizeof(L[i]));
		memset(R[i],-0x3f,sizeof(R[i]));
		for(int j:{1,2,3}) if(!a[i]||a[i]==j) {
			for(int k:{1,2,3}) for(int c:{1,2,3}) if(c^j) {
				chkmin(L[i][j][k],L[i-1][c][k]+(j==k));
				chkmax(R[i][j][k],R[i-1][c][k]+(j==k));
			}
		}
	}
	int c[4]={0,n/3,n/3,n/3};
	for(int i=n;i>=1;--i) {
		a[i]=0;
		for(int j:{1,2,3}) if(i==n||j!=a[i+1]) {
			bool ok=true;
			for(int k:{1,2,3}) ok&=(L[i][j][k]<=c[k]&&c[k]<=R[i][j][k]);
			if(ok) { a[i]=j; break; }
		}
		if(!a[i]) return puts("NO"),void();
		s[i]=" DXY"[a[i]],--c[a[i]];
	}
	for(int i=1;i<=n;++i) pr[i]=i-1,sf[i]=i+1;
	pr[n+1]=n,sf[0]=1;
	for(int i=1;i<n;++i) ps[a[i]^a[i+1]].insert(i);
	int tp=n;
	auto del=[&](int x) {
		wys[tp--]=x;
		int l=pr[x],r=sf[x];
		if(l>=1) ps[a[l]^a[x]].erase(l);
		if(r<=n) ps[a[x]^a[r]].erase(x);
		if(l>=1&&r<=n) ps[a[l]^a[r]].insert(l);
		sf[l]=r,pr[r]=l;
	};
	for(int _=0;_<n/3;++_) {
		int y=*ps[a[sf[0]]].begin(),z=sf[y],x=(sf[z]<=n&&a[pr[y]]==a[sf[z]]?pr[y]:sf[0]);
		del(z),del(y),del(x);
	}
	printf("YES\n%s\n",s+1);
	for(int i=1;i<=n;++i) {
		printf("%c %d%c"," DXY"[a[wys[i]]],TR.qry(wys[i])," \n"[i%3==0]);
		TR.add(wys[i],1);
	}
	TR.init();
	for(int i:{1,2,3}) ps[i].clear();
}
signed main() {
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}