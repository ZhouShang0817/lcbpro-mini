#include <iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<cstdint>
#include<numeric>
#include<cmath>
using namespace std;
#define ll long long
#define ld long double
#define pl pair<ll, ll>
#define vl vector<ll>
#define vpl vector<pl>
#define vb vector<bool>
#define vvl vector<vl>
#define vvpl vector<vpl>
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define f(i,a,b) for (ll i = (a); i < (b); ++i)
#define rf(i,a,b) for (ll i = (a); i >= (b); --i)
#define each(x,a) for (auto &x : a)
#define uniq(x) x.resize(unique(all(x)) - x.begin())
#define yes cout << "YES
"
#define no cout << "NO
"
#define deb(x) cerr << #x << " = " << x << "
"s

ll xorTill(ll n) {
    if (n % 4 == 1) {
        return 1;
    }
    else if (n % 4 == 2) {
        return n + 1;
    }
    else if (n % 4 == 3) {
        return 0;
    }
    else {
        return n;
    }
}

ll xorInRange(ll L, ll R) {
    ll xorTillL;
    if (L != 0) {
        xorTillL = xorTill(L - 1);
    }
    else {
        xorTillL = xorTill(L);
    }
    ll xorTillR = xorTill(R);
    return xorTillL ^ xorTillR;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        ll l,r,h,k,ans=0,r1,l1;
        cin >> l>>r>>h>>k;
        if (l > k) {
            l1 = k + ((l - k) / (1ll << h) + (((l - k) % (1ll << h)) != 0)) * (1ll << h);
        }
        else {
            l1 = k;
        }
        ans = xorInRange(l, r);
        ll c = (r - l1) / (1ll << h) + 1,k1=k,f=1;
        if (l1 > r) {
            cout << ans << endl;
            continue;
        }
        l = (l1) / (1ll << h);
        r = l + c-1;
        ll ans1 = xorInRange(l, r);
        f(i, 0, h) {
            ans1 *= 2;
        }
        ans ^= ans1;
        if (c % 2 == 1) {
            ans ^= k;
        }
        cout << ans << endl;
    }
}