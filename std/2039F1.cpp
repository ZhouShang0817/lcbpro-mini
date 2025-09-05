// Calm down.
// Think TWICE, code ONCE.
#include<bits/stdc++.h>
#define pb push_back
#define popcnt __builtin_popcountll
#define debug printf("Passed line %d
", __LINE__)

using namespace std;
typedef long long ll;
typedef vector<int> vint;
typedef pair<int, int> PII;

template<typename T> inline void read(T &x){
	x = 0; bool F = 0; char c = getchar();
	for (;!isdigit(c);c = getchar()) if (c == '-') F = 1;
	for (;isdigit(c);c = getchar()) x = x*10+(c^48);
	if (F) x = -x;
}

template<typename T1, typename... T2> inline void read(T1 &x, T2 &...y){read(x); read(y...);}

template<typename T> inline void checkmax(T &a, const T &b){if (a<b) a = b;}

template<typename T> inline void checkmin(T &a, const T &b){if (a>b) a = b;}

const int N = 1e5+5;
const ll MOD = 998244353;
vector<int> fact[N];
ll add[N], sum[N], dp[N];
int mu[N], n;

inline void solve(){
	read(n);
    for (int i = 1;i<=n;i++) sum[i] = dp[i] = 0;
	for (int i = n;i>=1;i--){
		for (int k: fact[i]){
			for (int j: fact[k]){
				add[j] += 2*mu[k/j]*sum[k];
			}
		}
		add[i]++;
		for (int k: fact[i]){
			add[k] = (add[k]-2*dp[k])%MOD+MOD;
			for (int j: fact[k]) (sum[j] += add[k]) %= MOD;
			(dp[k] += add[k]) %= MOD, add[k] = 0;
		}
	}
	printf("%lld
", sum[1]);
}

int main(){
	mu[1] = 1;
	for (int i = 1;i<N;i++){
		fact[i].pb(i);
		for (int j = 2*i;j<N;j += i) mu[j] -= mu[i], fact[j].pb(i);
	}
	int t; read(t); while (t--) solve();
	return 0;
}
/*
self check:
1. long long
2. size of array
3. code for testing
4. initializing
 */