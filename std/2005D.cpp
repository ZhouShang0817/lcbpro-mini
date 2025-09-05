#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=2e5+10,M=33;

int n,a[N],b[N],lg[N];
int ta[N],tb[N],tA,tB,ida[N],idb[N];
pii fa[N][M],fb[N][M],sufa[N],sufb[N];
int Sufa[N],Sufb[N],Prea[N],Preb[N];
pii pr[N]; int cnt;	
bool flag;

struct node
{
	int mx; LL cnt;

	friend node operator + (const node &A,const node &B)
	{
		node C;
		if(A.mx>B.mx) C=A;
		else if(A.mx<B.mx) C=B;
		else C={A.mx,A.cnt+B.cnt};
		return C;
	}
}ans;

int gcd(int x,int y)
{
	if(y==0) return x;
	return gcd(y,x%y);
}

struct ST
{
	int st[N][M];

	void prework()
	{
		for(int j=1; j<=lg[n]; j++)
			for(int i=1; i+(1<<j)-1<=n; i++)
				st[i][j]=gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}

	int ask(int l,int r)
	{
		if(l>r) return 0;
		int k=lg[r-l+1];
		return gcd(st[l][k],st[r-(1<<k)+1][k]);
	}
}A,B;

inline int ask(int pd,int l,int r)
{
	if(pd==1) return A.ask(l,r);
	return B.ask(l,r);
}

inline void solve(int *a,pii (*f)[M],int *t,int &T,pii *suf,int *id,int pd)
{
	cnt=0;
	for(int i=n; i>=1; i--)
	{
		t[i]=0;
		pr[++cnt]={a[i],i};
		for(int j=1; j<=cnt; j++)
			pr[j].fi=gcd(pr[j].fi,a[i]);
		pr[0]={0,0};
		for(int j=1; j<=cnt; j++)
			if(pr[j].fi!=pr[j-1].fi)
				f[i][++t[i]]=pr[j];
		for(int j=1; j<=t[i]; j++)
			pr[j]=f[i][j];
		cnt=t[i];
		reverse(f[i]+1,f[i]+1+t[i]);
	}

	id[n+1]=0;
	suf[0]={0,n+1};
	suf[T=1]={a[n],n}; id[n]=T;
	for(int i=n-1; i>=1; i--)
	{
		id[i]=T;
		if(ask(pd,i,n)==suf[T].fi) continue;
		suf[T].se=i+1;
		suf[++T].fi=ask(pd,i,n);
		id[i]=T;
	}
	suf[T].se=1;
}

inline void mian()
{
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>a[i], A.st[i][0]=a[i];
	for(int i=1; i<=n; i++)
		cin>>b[i], B.st[i][0]=b[i];

	A.prework(); B.prework();

	solve(a,fa,ta,tA,sufa,ida,1); solve(b,fb,tb,tB,sufb,idb,2);

	Prea[0]=Preb[0]=0;
	for(int i=1; i<=n; i++)
	{
		Prea[i]=gcd(Prea[i-1],a[i]);
		Preb[i]=gcd(Preb[i-1],b[i]);
	}
	Sufa[n+1]=Sufb[n+1]=0;
	for(int i=n; i>=1; i--)
	{
		Sufa[i]=gcd(Sufa[i+1],a[i]);
		Sufb[i]=gcd(Sufb[i+1],b[i]);
	}

	for(int i=1; i<=n; i++)
	{
		vector <pii> R;
		int pa=1,pb=1;
		while(pa<=ta[i] && pb<=tb[i])
		{
			if(fa[i][pa].se<fb[i][pb].se) R.push_back(fa[i][pa++]);
			else if(fa[i][pa].se>fb[i][pb].se) R.push_back(fb[i][pb++]);
			else R.push_back(fa[i][pa++]), pb++;
		}
		while(pa<=ta[i]) R.push_back(fa[i][pa++]);
		while(pb<=tb[i]) R.push_back(fb[i][pb++]);
		int lst=i;
		for(auto [V,j]:R)
		{
			pa=ida[j+1], pb=idb[j+1];
			int nowa=A.ask(i,j),nowb=B.ask(i,j);
			vector <pii> P;
			while(pa<=tA && pb<=tB && sufa[pa].se-1>=lst && sufb[pb].se-1>=lst)
			{
				if(sufa[pa].se>sufb[pb].se) P.push_back(sufa[pa++]);
				else if(sufa[pa].se<sufb[pb].se) P.push_back(sufb[pb++]);
				else P.push_back(sufa[pa++]), pb++;
			}
			while(pa<=tA && sufa[pa].se-1>=lst) P.push_back(sufa[pa++]);
			while(pb<=tB && sufb[pb].se-1>=lst) P.push_back(sufb[pb++]);
			if(!P.size() || (P.size() && P.back().se-1!=lst)) P.push_back({0,lst+1});	

			int len=P.size();
			for(int k=0; k<len; k++)
			{
				int p=P[k].se-1,tmp=(k==0? j+1:P[k-1].se-1)-p;
				int cura=gcd(gcd(Prea[i-1],nowb),Sufa[p+1]);
				int curb=gcd(gcd(Preb[i-1],nowa),Sufb[p+1]);
				ans=ans+(node){cura+curb,(LL)tmp};
			}
			lst=j+1;
		}
	}

	cout<<ans.mx<<" "<<ans.cnt<<"
";
	ans.mx=ans.cnt=0;
}	

int main()
{
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	lg[1]=0;
	for(int i=2; i<=N-10; i++)
		lg[i]=lg[i>>1]+1;

	int T; cin>>T;
	while(T--) mian();	
	
	return 0;
}
