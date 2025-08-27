#include<bits/stdc++.h>
using namespace std;
 
const int mo=998244353;
int T,n;
int f[1000001],s[1000001],tmp[1000001],mu[1000001],ans[1000001],val;
vector<int> v[1000001];
 
inline void upd(int &x,long long y){x=(x+y)%mo;}
 
signed main(){
std::ios::sync_with_stdio(false),cin.tie(0);
 
n=1000000;
 
mu[1]=1;
for (int i=1;i<=n;++i) for (int j=i;j<=n;j+=i){
v[j].push_back(i);
if (i^j) mu[j]-=mu[i];
}
 
for (int i=1;i<=n;++i) reverse(v[i].begin(),v[i].end());
 
s[1]=1;
for (int i=1;i<=n;++i){
for (int j:v[i]){
for (int k:v[j]) upd(tmp[j],s[k]);
upd(tmp[j],f[j]);
}
upd(val,tmp[i]);
for (int j:v[i]) for (int k:v[j])
upd(s[j],2ll*mu[j/k]*tmp[k]);
for (int j:v[i]) upd(f[j],-2*tmp[j]),tmp[j]=0;
ans[i]=(val+mo)%mo;
}
 
cin>>T;
while (T--){
cin>>n;
cout<<ans[n]<<'\n';
}
 
return 0;
}