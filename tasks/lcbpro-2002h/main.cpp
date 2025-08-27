#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int n=130,m=30,MOD=1e9+7;
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
int pw[35][135],dp[35][135][135],f[135][135][135],g[135][135][135];
//dp[v,i,j]: val[1,v], len=i, max del=j
//f[i,j,l],g[i,j,r]: len=i, g0=j, [L0,R0] = [l,inf]/[0,r]
signed main() {
	for(int i=0;i<=m;++i) for(int j=pw[i][0]=1;j<=n;++j) pw[i][j]=1ll*pw[i][j-1]*i%MOD;
	dp[0][0][0]=1;
	for(int v=1;v<=m;++v) {
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		g[0][0][0]=1;
		for(int i=0;i<=n+1;++i) for(int j=0;j<=i;++j) {
			for(int l=0;l<=i;++l) if(f[i][j][l]) {
				const int w=f[i][j][l];
				for(int k=0;i+k<=n;++k) {
					const int z=1ll*w*pw[v-1][k]%MOD;
					if(l>k) { //can't +0
						int nr=k-((l+1)&1); //trans +1, (a+l-k)%2=1
						if(nr>=0) add(g[i+k+1][j+2][nr],z); //max a = k-(l&1^1)
						else add(g[i+k+1][j+3][0],z); //can't +1
					} else add(g[i+k+1][j+1][k-l],z); //a+l<=k
				}
			}
			for(int r=0;r<=i;++r) if(g[i][j][r]) {
				const int w=g[i][j][r],l=r&1; //[l,r]
				for(int k=0;i+k<=n;++k) {
					const int z=1ll*w*pw[v-1][k]%MOD;
					if(l>k) { //can't +0 (same)
						int nr=k-((l+1)&1);
						if(nr>=0) add(g[i+k+1][j+2][nr],z);
						else add(g[i+k+1][j+3][0],z); 
					} else {
						//d<=a+r,a+l<=k -> a in [d-r,k-l]
						//split to [d-r,inf] + [0,k-l] - [0,inf]
						add(g[i+k+1][j+1][k-l],z);
						int *nw=f[i+k+1][j+1],*Z=dp[v-1][k];
						int o=(k-l)%2; //(d-r)%2=(k-l)%2
						for(int d=r+(k-l)%2;d<=k;d+=2) if(Z[d]) {
							nw[d-r]=(nw[d-r]+1ll*w*Z[d])%MOD;
							nw[o]=(nw[o]+1ll*(MOD-w)*Z[d])%MOD; //split -[0,inf]
						}
					}
				}
			}
		}
		for(int i=1;i<=n+1;++i) for(int j=1;j<=i;++j) {
			//0-th & i-th element is virtual, j=val[rad=0]
			for(int l=0;l<=i;++l) {
				add(dp[v][i-1][j-1+(!l?0:(l&1?1:2))],f[i][j][l]);
			}
			for(int r=0;r<=i;++r) {
				add(dp[v][i-1][j-1+(r&1)],g[i][j][r]);
			}
		}
	}
	int T; scanf("%d",&T);
	for(int N,M;T--;) {
		scanf("%d%d",&N,&M);
		for(int K=0;K<=(N-1)/2;++K) printf("%d ",dp[M][N][N-2*K]); puts("");
	}
	return 0;
}