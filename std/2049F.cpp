#include <cstdio>
#include <set>
#include <unordered_map>
#define ll long long
 
using namespace std;
 
const int N=114514;
 
ll a[N];int n;multiset<int> ans;
 
class xhj{public:
	int anc[N],siz[N],tgt;unordered_map<ll,int> s[N];
	bool vld(int x){return s[x].size()==tgt&&s[x][0];}
	int fnd(int x){return anc[x]==x?x:anc[x]=fnd(anc[x]);}
	void mrg(int x,int y){
		x=fnd(x);y=fnd(y);if(!x||!y||x==y) return ;
		if(siz[x]>siz[y]) swap(x,y);
		if(vld(x)) ans.erase(ans.find(siz[x]));
		if(vld(y)) ans.erase(ans.find(siz[y]));
		for(auto[p,q]:s[x]) s[y][p]+=q;
		s[x].clear();anc[x]=y;siz[y]+=siz[x];
		if(vld(y)) ans.insert(siz[y]);
	}
	void upd(int x,int y){
		ll b=a[x];x=fnd(x);bool p=vld(x);
		if(!--s[x][b]) s[x].erase(b);
		++s[x][b-y];bool q=vld(x);
		if(p&&!q) ans.erase(ans.find(siz[x]));
		if(!p&&q) ans.insert(siz[x]);
		if(a[x]-y<tgt&&siz[x]==1){
			if(a[x-1]<tgt) mrg(x,x-1);
			if(a[x+1]<tgt) mrg(x,x+1);
		}
	}
	void iit(int k){tgt=1<<k;
		for(int i=1;i<=n+1;++i) anc[i]=0;
		for(int i=1;i<=n;++i){
			anc[i]=i;siz[i]=1;s[i].clear();s[i][a[i]]=1;
			if(!k&&!a[i]) ans.insert(1);upd(i,0);
		}
	}
}S[17];
 
int x[N],d[N],wzm[N];
 
 
int main()
{
 
	int T;scanf("%d",&T);while(T--){
		int m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) scanf("%lld",a+i);
		for(int i=1;i<=m;++i) scanf("%d%d",x+i,d+i),a[x[i]]+=d[i];
		for(int k=0;k<17;++k) S[k].iit(k);
		for(int i=m;i;--i){
			wzm[i]=ans.empty()?0:*ans.rbegin();
			for(int k=0;k<17;++k) S[k].upd(x[i],d[i]);
			a[x[i]]-=d[i];
		}ans.clear();
		for(int i=1;i<=m;++i) printf("%d\n",wzm[i]);
	}
}