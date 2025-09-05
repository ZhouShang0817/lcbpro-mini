#include<bits/stdc++.h>
#define int long long
#define endl "
"
#define PII pair<int,int>

using namespace std;

const int N = 2e5 + 10;
int fa[N];
int cnt;

void solve() {
    int n,m;
    cin>>n>>m;
  int mexs=-1;
    for(int i = 1; i <= n; i++) {
        int l;
        cin>>l;
        set<int> shu;
        for(int j = 1; j <= l; j++) {
            int t;
            cin >> t;
            shu.insert(t);
        }

        int mex1 = 0,mex2=0;
        while (shu.count(mex1)) mex1++;
        mex2 = mex1+1;
        while (shu.count(mex2)) mex2++;
        mexs=max(mexs,mex2);
    }

    if (m>mexs) {
        cout<<mexs*(mexs+1)+(mexs+1+m)*(m-mexs)/2<<endl;
    }
    else {
        cout<<(m+1)*mexs<<endl;
    }
    //cout<<mexs*(mexs+1)<<" "<<(mexs+1+m)*(m-mexs)/2<<endl;

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _=1;
    cin>>_;
    //cout<<fixed<<setprecision(2)
    while (_--) {
        solve();
    }
    return 0;
}