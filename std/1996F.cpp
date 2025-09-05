#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e5+10;
int T,n,k,a[N],b[N];

bool check(int x)
{
	int t=0;
	for(int i=1;i<=n;i++)
		t+=max(0ll,(a[i]-x)/b[i]+(a[i]>=x));
	return t<=k;
}

int getl()
{
	int l=0,r=1e9+1;
	while(l<r)
	{
		int mid=l+r>>1;
		if(check(mid)) r=mid;else l=mid+1;
	}
	return l;
}

signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		int x=getl();
		int res=0;
		priority_queue<int>q;
		for(int i=1;i<=n;i++)
		{
			int c=max(0ll,(a[i]-x)/b[i]+(a[i]>=x));
			res+=(2*a[i]-(c-1)*b[i])*c/2;
			k-=c;
		}
		if (x>=1) cout<<res+k*(x-1)<<'
';else cout<<res<<'
';
	}
	return 0;
}