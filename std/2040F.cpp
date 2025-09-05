#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int a,b,c,k;
int pr[3000009],prcnt,phi[3000009],cd[3000009],ans,d[1000009],o,s[3000009],ni[3000009],inv[3000009];
bool tg[3000009];
int dep[3000009];
int gcd(int x,int y){
	if(y == 0)
		return x;
	else
		return gcd(y,x % y);
}
int o1[509],o1cnt,o2[509],o2cnt,o3[509],o3cnt;
int main(){
	//预处理欧拉筛和逆元 
	phi[1] = 1;
	tg[0] = tg[1] = true;
	inv[1] = 1;
	s[0] = s[1] = ni[0] = ni[1] = inv[1] = 1;
	for(int i = 2; i <= 3000000; i ++){
		if(!tg[i]){
			pr[++prcnt] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= prcnt && i * pr[j] <= 3000000; j ++){
			tg[i * pr[j]] = true;
			if(i % pr[j] == 0){
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
			else{
				phi[i * pr[j]] = phi[i] * (pr[j] - 1); 
			}
		}
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
		ni[i] = 1ll * ni[i - 1] * inv[i] % mod;
		s[i] = 1ll * s[i - 1] * i % mod;
	}
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d %d",&a,&b,&c,&k);
		o = 0;
		for(int i = 1; i <= k; i ++){
			scanf("%d",&d[i]);
			o = gcd(o,d[i]);
		}
		for(int i = 1; i * i <= o; i ++){//第二个预处理优化 
			if(o % i == 0){
				dep[i] = s[a * b * c / i];
				int t = o / i;
				for(int j = 1; j <= k; j ++){
					dep[i] = 1ll * dep[i] * ni[d[j] / i] % mod;
				}
				if(t != i){
					dep[t] = s[a * b * c / t];
					for(int j = 1; j <= k; j ++){
						dep[t] = 1ll * dep[t] * ni[d[j] / t] % mod;
					}
				}
			}
		}
		//得到因数 
		o1cnt = o2cnt = o3cnt = 0;
		for(int i = 1; i * i <= a; i ++){
			if(a % i == 0){
				o1[++o1cnt] = i;
				if(i * i != a){
					o1[++o1cnt] = a / i;
				} 
			}
		}
		for(int i = 1; i * i <= b; i ++){
			if(b % i == 0){
				o2[++o2cnt] = i;
				if(i * i != b){
					o2[++o2cnt] = b / i;
				} 
			}
		}
		for(int i = 1; i * i <= c; i ++){
			if(c % i == 0){
				o3[++o3cnt] = i;
				if(i * i != c){
					o3[++o3cnt] = c / i;
				} 
			}
		}
		//优化后的主体 
		ans = 0;
		for(int i = 1; i <= o1cnt; i ++){
			if(o % o1[i] != 0)
				continue;
			for(int j = 1; j <= o2cnt; j ++){
				if(o % o2[j] != 0)
					continue;
				for(int k = 1; k <= o3cnt; k ++){
					if(o % o3[k] == 0){
						int x = o1[i] * o2[j] / gcd(o1[i],o2[j]);
						int y = x * o3[k] / gcd(x,o3[k]);
						ans = (ans + 1ll * dep[y] * phi[o1[i]] % mod * phi[o2[j]] % mod * phi[o3[k]] % mod) % mod;
					}
				}
			}
		}
		//注意burnside引理除以|G| 
		ans = 1ll * ans * inv[a * b * c] % mod;
		printf("%d
",ans);
	}
}
