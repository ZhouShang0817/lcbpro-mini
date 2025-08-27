#include<bits/stdc++.h>
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=2e5+10;
int flag,n,m,Q;
multiset<int> s[N];
struct node{
	int suf,pre,all,cnt,tag,p1,p2;
	void update()
	{
		flag-=p1,p1=0;
		if(cnt&&tag) p1=1;
		flag+=p1;
	}
}t[N<<2];
void update(int now,int l,int r)
{
	flag-=t[now].p2,t[now].p2=0;
	t[now].all=min(t[ls].all,t[rs].all);
	int p1=(t[ls].tag||t[ls].pre==mid-l+1),
		p2=(t[rs].tag||t[rs].pre==r-mid);
	if(p1) t[now].pre=mid-l+1+(p2?r-mid:t[rs].pre);
	else t[now].pre=t[ls].pre;
	if(p2) t[now].suf=min(t[rs].all,(p1?t[ls].all:t[ls].suf));
	else t[now].suf=t[rs].suf;
	t[now].p2=((p1?t[ls].all:t[ls].suf)<=(p2?r:t[rs].pre+mid));
	flag+=t[now].p2;
}
void add1(int l,int r,int now,int L,int R,int a)
{
	if(l>R||r<L) return;
	if(L<=l&&r<=R)
	{
		t[now].tag+=a;
		t[now].update();
		return;
	}
	add1(l,mid,ls,L,R,a),add1(mid+1,r,rs,L,R,a); 
	update(now,l,r);
}
void add2(int l,int r,int now,int L,int R,int a)
{
	if(R<=r)
	{
		t[now].cnt+=a;
		t[now].update();
	}
	if(l==r)
	{
		if(a==-1) s[L].erase(s[L].find(R));
		else s[L].insert(R);
		t[now].all=*s[L].begin();
	}
	else
	{
		if(L<=mid) add2(l,mid,ls,L,R,a);
		else add2(mid+1,r,rs,L,R,a);
		update(now,l,r);
	}
}
void build(int l,int r,int now)
{
	t[now]={n+1,0,n+1,0,0,0,0};
	if(l==r) return;
	build(l,mid,ls),build(mid+1,r,rs);
}
int l[N],r[N],p[N],F[N],T,num;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&p[i],&l[i],&r[i]);
		for(int i=1;i<=n;i++) s[i].clear(),s[i].insert(n+1);
		build(1,n,1),flag=0;
		for(int i=1,j=0;i<=m;i++)
		{
			while(j<=m&&!flag)
			{
				j++;
				if(p[j]==0) add1(1,n,1,l[j],r[j],1);
				else add2(1,n,1,l[j],r[j],1);
			}
			F[i]=j;
			if(p[i]==0) add1(1,n,1,l[i],r[i],-1);
			else add2(1,n,1,l[i],r[i],-1);
		}
		scanf("%d",&Q);
		for(int i=1,x,y;i<=Q;i++)
		{
			scanf("%d%d",&x,&y),num++;
			puts(y>=F[x]?"No":"Yes");
		}
	}
}