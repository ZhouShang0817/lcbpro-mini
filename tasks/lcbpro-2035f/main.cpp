#include<bits/stdc++.h>
using namespace std;

int n,root,a[2001];
vector<int> E[2001];
long long f[2001],g[2001];

int dfn[2001],rnk[2001],fa[2001],cntdfn;
void init(int u,int father){
    fa[u]=father,dfn[u]=++cntdfn,rnk[cntdfn]=u;
    for(int v :E[u])if(v!=father)init(v,u);
}
inline bool check(long long val){
    for(int i=1;i<=n;i++)f[i]=val/n+(i<=val%n),g[i]=a[i];
    f[0]=g[0]=0;
    for(int i=n;i>=1;i--){
        int u=rnk[i];
        g[fa[u]]+=f[u]<g[u]?g[u]-f[u]:((f[u]-g[u])&1);
    }
    return g[0]==0;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&root);
        for(int i=1;i<=n;i++)E[i].clear();
        for(int i=1;i<=n;i++)scanf("%d",a+i);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        cntdfn=0;
        init(root,0);
        long long answer=1e18;
        for(int i=0;i<n*2;i++){
            int l=0,r=1e9;
            while(l<r){
                int mid=(l+r)>>1;
                if(check(1ll*mid*n*2+i))r=mid;
                else l=mid+1;
            }
            answer=min(answer,1ll*l*n*2+i);
        }
        printf("%lld
",answer);
    }
    return 0;
}
