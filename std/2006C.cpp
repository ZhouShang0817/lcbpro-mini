#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace wing_heart {
	constexpr int N=4e5+7;
	int t,n;
	int a[N],b[N];
	int st[30][N];
	int gcd(int a,int b) { return b? gcd(b,a%b): a; }
	int getgcd(int l,int r) {
		int k=__lg(r-l+1);
		return gcd(st[k][l],st[k][r-(1<<k)+1]);
	}
    void main() {
		sf("%d",&t);
		while(t--) {
			sf("%d",&n);
			rep(i,1,n) sf("%d",&a[i]);
			if(n==1) {
				puts("1");
				continue;
			}
			rep(i,1,n-1) {
				b[i]=abs(a[i+1]-a[i]);
				while(b[i] && b[i]%2==0) b[i]>>=1;
				st[0][i]=b[i];
			}
			int lg=__lg(n-1);
			rep(k,1,lg) for(int i=1;i+(1<<k)-1<=n-1;i++) st[k][i]=gcd(st[k-1][i],st[k-1][i+(1<<(k-1))]);
			ll ans=n;
			int cnt=0;
			rep(i,1,n-1) {
				if(b[i]==0) ++cnt;
				else if(cnt) {
					ans+=1ll*cnt*(cnt+1)/2, cnt=0;
				}
			}
			if(cnt) ans+=1ll*cnt*(cnt+1)/2;
			rep(i,1,n-1) {
				int l=i,r=n-1;
				while(l<r) {
					int mid=(l+r)>>1;
					if(getgcd(i,mid)==1) r=mid;
					else l=mid+1;
				}
				if(getgcd(i,r)==1) ans+=n-r;
			}
			pf("%lld
",ans);
		}
    }
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
    wing_heart :: main();
}
