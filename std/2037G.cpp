#include <cstring>
#include <iostream>

#define int long long

using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

constexpr int N=1e5+10;
constexpr ll M=998244353,MM=1e6+10;
ll mu[MM],prim[MM],li;
bool mk[MM];
ll f[MM];

int T;
void init(){
  T=1;
  mu[1]=0;

  for(ll i=2;i<MM;++i){
    if(!mk[i])prim[++li]=i,mu[i]=1;
    for(int j=1;prim[j]*i<MM;++j){
      mk[prim[j]*i]=1,mu[prim[j]*i]=-mu[i];
      if(i%prim[j]==0){mu[prim[j]*i]=0;break;}
    }
  }

}

void solve(){
  int n; cin>>n;
  memset(f, 0, sizeof f);
  for(int i=1;i<=n;++i){
    ll t; cin>>t;
    ll thej=li=0;
    for(ll j=1;j*j<=t;++j){
      if(t%j==0){
        thej=(thej+mu[j]*f[j]+M)%M;
        prim[++li]=j;
        if(j*j!=t)prim[++li]=t/j,thej=(thej+mu[t/j]*f[t/j]+M)%M;
      }
    }
    if(i==n){cout<<thej<<'
';break;}
    if(i==1)thej=1;
    for(int j=1;j<=li;++j)
      f[prim[j]]=(f[prim[j]]+thej)%M;
  }
}

signed main(){
  cin.tie(0)->sync_with_stdio(0);

  init();
  while(T--)solve();

  return 0;
}
