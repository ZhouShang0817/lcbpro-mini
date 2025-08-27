#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define f first
#define s second
const int maxn = 2e5 + 5;
const int INF = 1e9 + 5;
const int mod  = 1e9 + 7;

void print_vec(vector<string> vec){
    for(string i: vec){
        cout << i << ' ';
    }
    cout << '
';
}

int _power(int x, int b){
    if(b==0)
        return 1;
    int ans = _power(x, b/2);
    ans = (ans * ans) %mod;

    return (b%2)? (ans*x)%mod : ans;

}

void solve(){
    int n;
    cin>>n;
    vector<int> q(n+1);
    vector<int> y(n+1);
    vector<int> big(n+1);

    for(int i= 1; i<=n; i++){
        cin>>q[i];
        y[i] = q[i];
        while(q[i]%2 == 0){
            q[i]/=2;
        }
    }
    
    vector<pair<int, int>> stack;
    int sum = 0;
    for(int i = 1; i<=n;i++){
        while(stack.size() && (stack.back().f <= y[i] || big[i])){
            y[i] *= stack.back().s;
            if(y[i] >= mod){
                y[i]%=mod;
                big[i] = 1;
            }

            sum -= (stack.back().f * stack.back().s) % mod;
            sum%=mod;
            sum = (sum +stack.back().f )%mod;
            stack.pop_back();
        }
        stack.pb({q[i], (y[i] * _power(q[i], mod-2)) % mod});
        sum = (sum +  y[i]) %mod;
        cout << (sum+mod)%mod << ' ';

    }

    cout << '
';

}

int32_t main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
}