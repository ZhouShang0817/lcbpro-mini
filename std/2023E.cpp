#include <bits/stdc++.h>
using namespace std;const int N=5e5+5;
int T,n,f[N];long long ans;vector<int>v[N];
void dfs(int u,int fa){int d=0;for(auto i:v[u])if(i!=fa)dfs(i,u),d++;
	for(auto i:v[u])if(i!=fa)f[u]+=max(1,f[i]-d+1);ans+=d*(d-1ll)/2;
}
int main(){ios::sync_with_stdio(0),cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){cin>>n;for(int x,y,i=1;i<n;i++)cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
		int rt=0;for(int i=1;i<=n;i++)if(v[i].size()>v[rt].size())rt=i;ans=0;
		long long sum=0;for(auto i:v[rt])dfs(i,rt),sum+=max(f[i],(int)v[rt].size()-1);
		cout<<ans+(sum+1>>1)<<"\n";for(int i=1;i<=n;i++)v[i].clear(),f[i]=0;
	}
}