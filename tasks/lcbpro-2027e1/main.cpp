#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<LL,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='
'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=1e9+7;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[2000005],inv[2000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
//	Invn[0]=Invn[1]=1;
//	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int t,n,a[10005],x[10005];
map<pp,int>H;
inline void adjust(int &x,int &d){
	bool fl=0;
	int tx=0,td=0,mx=0;
	for(int i=30;i>=0;i--){
		int t2=(d>>i)&1;
		if(t2){
			mx=i;
			break;
		}
	}
	for(int i=mx;i>=0;i--){
		int t1=(x>>i)&1,t2=(d>>i)&1;
		if(!t1&&!t2)continue;
		if(fl){
			if(t1)tx=(tx<<1)+1,td=(td<<1)+1;
		}else{
			if(!t1&&t2)fl=1;
			else{
				if(t1&&t2)tx=(tx<<1)+1,td=(td<<1)+1;
				else tx=(tx<<1)+1,td<<=1;
			}
		}
	}
	x=tx,d=td;
}
inline int sg(int x,int d){
	adjust(x,d);
	//x=2^k-1 
	if(x==d)return __builtin_popcount(x);//d=2^k-1
	else if((x+1)/2==d)return (__builtin_popcount(x)-1)^1;//d=2^k
	else if(d==x-1)return 0;//d=2^k-2 
	else {
		int fk=d,res=0;
		while(fk){
			fk>>=1;
			res++;
		}
		return res;
	}
}
inline void solve(){
	gi(n);
	for(int i=1;i<=n;i++)gi(a[i]);
	for(int i=1;i<=n;i++)gi(x[i]);
	int res=0;
	for(int i=1;i<=n;i++)res^=sg(x[i],a[i]);
	if(res)puts("Alice");
	else puts("Bob");
}
signed main(){
	srand(time(0));
	gi(t);
	while(t--)solve();
	return 0;
}