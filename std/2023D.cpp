#include <bits/stdc++.h>
//#define int long long
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

using namespace std;
typedef long long ll;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
vector <int> p[105];
int sz[105];
const int bulan=500;
double dp[300005];
double sum=0;
int n;
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int pp,x;
        cin>>pp>>x;
        p[pp].push_back(x);
        if(pp==100)
            sum+=x;
    }
    for(int i=1;i<=100;i++)
        {
            sort(p[i].begin(),p[i].end());
            reverse(p[i].begin(),p[i].end());
        }
    dp[0]=1;
    for(int i=1;i<100;i++)
        sz[i]=(int)(ceil((100/(100-i))));
    sz[100]=p[100].size();
    int mw=210000;
    if(sum>=mw)
    {
        cout<<fixed<<setprecision(7)<<sum;
        return;
    }
    for(int i=1;i<100;i++)
    {
        for(int j=0;j<min((int)p[i].size(),sz[i]);j++)
        {
            int x=p[i][j];
            for(int w=mw;w>=x;w--)
            {
                dp[w]=max(dp[w],dp[w-x]*(double)(i)/100);
            }
        }
    }
    double mans=sum;
    for(int i=1;i<=mw;i++)
        mans=max(mans,dp[i]*(i+sum));
    cout<<fixed<<setprecision(7)<<mans;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
   // cin>>t;
    while(t--)
        solve();
    return 0;
}