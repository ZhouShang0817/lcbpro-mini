#include <bits/stdc++.h>
#define int long long

using namespace std;

void solve(){
	int n;
	cin >> n;
	unordered_map<int, int> mp;	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		mp[x]++;
	}
	int ans = 0;
	for(auto i: mp) ans += i.second / 2;
	cout << ans << endl;
}

signed main() {
  int t = 1;
	cin >> t;
	while(t--)
		solve();

  return 0;
}
