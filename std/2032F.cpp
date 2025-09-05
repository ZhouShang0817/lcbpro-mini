#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
const int N=1000005; 
int t,n,a[N],b[N],c[N];
const ll mod=998244353;
ll f[N][2],buc[N][2],Buc[N][2],w[2][2],g,G;//g,buc 对应 nim 游戏，G,Buc 对应反 nim 游戏，w 是奇偶分开贡献
void add(ll &x,ll y){
	(x+=y)%=mod;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),c[i]=a[i],a[i]^=a[i-1],b[i]=a[i];
		sort(b+1,b+n+1);
		int m=unique(b,b+n+1)-b-1;
		for(int i=1;i<=n;i++) a[i]=lower_bound(b,b+m+1,a[i])-b;
		for(int i=0;i<=m;i++) buc[i][0]=buc[i][1]=Buc[i][0]=Buc[i][1]=0;
		buc[0][1]=1,g=1,f[0][1]=1;
		G=0;
		w[0][0]=0,w[0][1]=1,w[1][0]=w[1][1]=0;
		int pos=0;
		for(int i=1;i<=n;i++){
			f[i][0]=(g-buc[a[i]][1]+mod+buc[a[i]][0])%mod;
			if(c[i]>1){
				while(pos<i){//类似双指针
					int j=pos;
					add(Buc[a[j]][0],f[j][0]);
					add(Buc[a[j]][1],f[j][1]),add(G,f[j][1]);
					pos++;
				}
				w[0][0]=w[0][1]=w[1][0]=w[1][1]=0;
			}
			f[i][1]=(G-Buc[a[i]][1]+mod+Buc[a[i]][0])%mod;
			add(f[i][1],w[i&1][1]),add(f[i][1],w[!(i&1)][0]);
			add(buc[a[i]][0],f[i][0]);
			add(buc[a[i]][1],f[i][1]),add(g,f[i][1]);
			add(w[i&1][0],f[i][0]),add(w[i&1][1],f[i][1]);
		}
		printf("%lld
",f[n][0]);
	}
	return 0;
}
