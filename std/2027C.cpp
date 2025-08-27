#include<bits/stdc++.h>
using namespace std;
#define int long long 

void solve(){
	int n;
	cin>>n;
	vector<int> a(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	map<int,vector<int>> mp;
	for(int i=1;i<=n;i++){
		mp[a[i]+i-1].push_back(a[i]+i-1+i-1);
	}
	
	int ans=n;	
	queue<int> q;
	q.push(n); 
	map<int,bool> st;
	st[n]=1;
	while(q.size()){
		auto t=q.front();
		q.pop();
		
		for(auto v:mp[t]){
			if(!st[v]){
				q.push(v);
				st[v]=1;
				ans=max(ans,v);
			}
		}
	}
	
	cout<<ans<<'
';
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	
	int _;
	cin>>_;
	while(_--){
		solve();
	}
	
	return 0;
}