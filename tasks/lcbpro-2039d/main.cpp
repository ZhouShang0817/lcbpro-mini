#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '
'
const int N = 1e5 + 5;
int n, m;
int a[N],res[N];

void solve()
{
    cin >> n >> m;
    for (int i=0;i<m;i++) cin >> a[i];
    sort(a,a+m,greater<int>());
    res[1] = 0;
    for (int i=1;i<=n;i++)
    {
        for (int j=i+i;j<=n;j+=i)
        {
            res[j]=res[i]+1;
            if (res[j]==m)
            {
                cout << -1 << endl;
                return;
            }
        }
    }
    for (int i=1;i<=n;i++) cout << a[res[i]] << ' ';
    cout << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _ = 1;
    	cin >> _;
    while (_--)
        solve();
}