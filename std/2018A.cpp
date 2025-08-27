#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define int long long

const int MAX = 2e5 + 20;
int a[MAX];

void solve(){
    int n,k; cin >> n >> k;
    int G = 0; int sum = 0;
    for (int i = 0; i < n; i++) {cin >> a[i];G=max(G,a[i]);sum+=a[i];}
    int ans = 1;
    for (int i = 1; i <= n; i++){
        if (((sum+k)/i)>=G && ((i-sum%i)%i)<=k) ans=max(ans,i);
    }
    cout << ans << '
';
}

signed main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}