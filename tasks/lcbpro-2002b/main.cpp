#include <bits/stdc++.h>
using namespace std;
#define endl "
"

void solve()
{
    int n; cin>>n;
    vector<int> vecA(n), vecB(n);
    for(int i=0; i<n; i++) cin>>vecA[i];
    for(int i=0; i<n; i++) cin>>vecB[i];
    bool bob=0;
    if(vecA==vecB) bob=1;
    reverse(vecB.begin(), vecB.end());
    if(vecA==vecB) bob=1;
    if(bob) cout<<"Bob";
    else cout<<"Alice";
    cout<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--) solve();
}
