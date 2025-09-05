#include<bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define ll long long
#define INF 10000000000000000
using namespace std;

void solve(){
	ll n,m,k;cin>>n>>m>>k;
	vector<vector<int>> mat(n,vector<int> (m));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j) cin>>mat[i][j];
	}
	vector<vector<ll>> f(n+1,vector<ll> (m,INF));
	vector<vector<vector<ll>>> g(n+1,vector<vector<ll>> (m,vector<ll> (m,INF)));
	f[0][0] = 0;
	for(int j = 0; j < m; ++j){
		for(int x = 0; x < m; ++x) g[0][j][x] = x * k;
	}
	for(ll i = 1; i <= n; ++i){
		for(ll j = 0; j < m; ++j){
			for(ll x = 0; x < m; ++x){
				ll left = j > 0 ? g[i][j-1][x] : INF;
				int indx = (j+x)%m;
				//cout<<"i: "<<i<<" j: "<<j<<" x: "<<x<<"
";
				g[i][j][x] = min(f[i-1][j] + k*x,left) + mat[i-1][indx]; 
				f[i][j] = min(f[i][j],g[i][j][x]);
			}
		}
	}
	cout<<f[n][m-1]<<"
";
}

int main (){
	ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
	int t;cin>>t;
	while(t--){
			   solve();
	}
}

