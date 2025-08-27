#ifdef DeBuG
#include "debug.h"
#else
#include <bits/stdc++.h>
#define dbg(...)
#endif
using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(v) (int)(v).size()
#define all(v) begin(v),end(v)
#define rep(i,a,b) for (int i=(a);i<(b);++i)
using ll = long long; using pii = pair<int,int>;
using pll = pair<ll,ll>; using vi = vector<int>;
template<class T> using V = vector<T>;

ll euclid (ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}

ll inv (ll a, ll mod) {
    assert(gcd(a, mod) == 1);
    ll x, y; euclid(a, mod, x, y);

    return ((x % mod) + mod) % mod;
}

ll crt (ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);

    if ((a - b) % g != 0) { // no solution
        return -1;
    }
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}

pll solve (ll a, ll b, ll m) { // solve ax + b = 0 (mod m), return minimal x and modified mod
    b = (((-b) % m) + m) % m;
    ll g = gcd(a, m);
    if (b % g != 0) return {-1, -1}; // no soln
    a /= g, b /= g, m /= g;
    ll aa = inv(a, m);
    return {aa * b % m, m};
}

void solvetc (int cs) {
    ll n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;
    ll _g = gcd(vx, vy); vx /= _g, vy /= _g;

    auto [x1, m1] = solve(vx, x, n);
    auto [x2, m2] = solve(vy, y, n);
    if (x1 == -1 || x2 == -1) { cout << "-1
"; return; }

    dbg(x1, m1, x2, m2);

    ll t = crt(x1, m1, x2, m2);
    if (t == -1) { cout << "-1
"; return; }
    dbg(t);

    ll alpha = (x + t * vx) / n, beta = (y + t * vy) / n;

    ll ans = alpha + beta - 2 + (alpha + beta) / 2 + abs(alpha - beta) / 2;
    cout << ans << "
";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int tc, cs = 1; cin >> tc;
    while (tc--) solvetc(cs++);
    return 0;
}