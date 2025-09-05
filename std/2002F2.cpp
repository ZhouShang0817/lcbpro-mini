#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int L=120;
bool f[L+5][L+5];
int bgcd(int x,int y) {
	if(!x||!y||x==y) return x|y;
	if(~x&1) return y&1?bgcd(x>>1,y):(bgcd(x>>1,y>>1)<<1);
	return y&1?(x<y?bgcd((y-x)>>1,x):bgcd((x-y)>>1,y)):bgcd(x,y>>1);
}
void solve() {
	int n,m,a,b;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	memset(f,0,sizeof(f));
	int u=max(1,n-L),v=max(1,m-L);
	ll ans=0;
	for(int i=0;i<=n-u;++i) for(int j=0;j<=m-v;++j) {
		if(!i||!j) f[i][j]=1;
		else if(bgcd(i+u,j+v)<=1) f[i][j]=f[i-1][j]|f[i][j-1];
		if(f[i][j]) ans=max(ans,1ll*a*(i+u)+1ll*b*(j+v));
	}
	printf("%lld
",ans);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
