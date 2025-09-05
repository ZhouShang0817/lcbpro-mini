#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>   
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;   
using namespace std;
#define ll long long
#define ld long double
#define nline "\n"
#define f first
#define s second
const ll INF_MUL=1e13;
const ll INF_ADD=1e18;
#define sz(x) (ll)x.size()
#define vl vector<ll>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend() 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_pset;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------     
const ll MOD=998244353;
const ll MAX=500500;
void solve(){
  ll n; cin>>n;
  vector<ll> a(n+5),c(n+5,0);
  for(ll i=1;i<=n;i++){
    cin>>a[i];
    ll val=a[i];
    if(i&1){
      val=-val;
    }
    c[i]=c[i-1]+val;
  }
  auto getv=[&](vector<ll> d,ll status){
    set<ll> track;
    track.insert(-1); track.insert(n+1);
    vector<pair<ll,ll>> consider;
    ll sum=0;
    for(ll i=0;i<=n;i++){
      if(status==0){
        c[i]=-c[i];
      }
      consider.push_back({c[i],i});
    }
    sort(rall(consider));
    for(auto it:consider){
      ll val=it.f,pos=it.s;
      ll now=val%=MOD;
      track.insert(pos);
      ll l=*(--track.lower_bound(pos)),r=*(track.upper_bound(pos));
      ll subarrays=((pos-l)*(r-pos))%MOD;
      sum=(sum+now*subarrays)%MOD;
    }
    sum=(sum+MOD)%MOD;
    return sum;
  };
  ll ans=(getv(c,1)+getv(c,0))%MOD;
  cout<<ans<<nline;
  return;
}
int main()                                                                                 
{                                     
  ll test_cases=1;
  cin>>test_cases;
  while(test_cases--){
    solve();
  }
  cout<<fixed<<setprecision(12); 
  cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n"; 
}  