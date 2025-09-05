#include<bits/stdc++.h>
#define ll long long
#define lc k<<1
#define rc k<<1|1
using namespace std;
int t;
int n,x;
struct aaa
{
	int val,v,id;
}a[200010];
vector<int> wz[200010];
ll tr[800010][2];
int ans=0;
inline void build(int l,int r,int k)
{
	if(l==r)
	{
		tr[k][0]=a[l].v,tr[k][1]=a[l].val;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	tr[k][0]=max(tr[lc][0],tr[rc][0]),tr[k][1]=tr[lc][1]+tr[rc][1];
}
inline int query(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][0];
	int mid=(l+r)>>1,sum=0;
	if(ql<=mid) sum=query(l,mid,ql,qr,lc);
	if(mid<qr) sum=max(sum,query(mid+1,r,ql,qr,rc));
	return sum;
}
inline ll querysum(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][1];
	int mid=(l+r)>>1;ll sum=0;
	if(ql<=mid) sum+=querysum(l,mid,ql,qr,lc);
	if(mid<qr) sum+=querysum(mid+1,r,ql,qr,rc);
	return sum;
}
inline void solve(int l,int r)
{
	if(l>=r) return;
	int maxx=query(1,n,l,r,1);
	int rl=lower_bound(wz[maxx].begin(),wz[maxx].end(),l)-wz[maxx].begin(),rr=upper_bound(wz[maxx].begin(),wz[maxx].end(),r)-wz[maxx].begin()-1;
	//cout<<l<<" "<<r<<" "<<rl<<" "<<rr<<endl;
	int nw=l;
	for(register int i=rl;i<=rr;i++)
	{
		ans++;
		if(nw<=wz[maxx][i]-1)
			if(querysum(1,n,nw,wz[maxx][i]-1,1)>=a[wz[maxx][i]].val)
				solve(nw,wz[maxx][i]-1);
		nw=wz[maxx][i]+1;
	}
	if(nw<=r)
		if(querysum(1,n,nw,r,1)>=a[wz[maxx][rr]].val)
			solve(nw,r);
}
int main()
{
	//freopen("qg.in","r",stdin);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&x);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i].val),a[i].id=i;
		if(n==1)
		{
			puts("1");
			continue;
		}
		sort(a+1,a+n+1,[](aaa u,aaa v){return u.val<v.val;});
		int tot=0;
		a[0].val=0;
		for(register int i=1;i<=n;i++)
		{
			if(a[i].val!=a[i-1].val) tot++;
			a[i].v=tot;
		}
		sort(a+1,a+n+1,[](aaa u,aaa v){return u.id<v.id;});
		for(register int i=1;i<=n;i++) wz[a[i].v].push_back(i);
		build(1,n,1);
		solve(1,n);
		printf("%d
",ans);
		ans=0;
		for(register int i=1;i<=4*n;i++) tr[i][0]=tr[i][1]=0;
		for(register int i=1;i<=tot;i++) wz[i].clear();
	}
	return 0;
}
