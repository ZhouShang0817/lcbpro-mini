#include <iostream>
#include <fstream>
#include <math.h>
#include <functional>
#include <numeric>
#include <string>
#include <assert.h>
#include <set>
#include <map>
#include <vector>
#include <random>
#include <stack>
#include <queue>
#include <array>
#include <deque>
#include <algorithm>

using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define ld long double

#define vec vector
#define vll vec<ll>
#define vvll vec<vll>
#define vpll vec<pll>
#define vvpll vec<vpll>

#define all(v) v.begin(), v.end()

#define forlr(i, l, r) for(ll i = (l); i < (r); ++i)
#define forn(i, n) forlr(i, 0, n)
#define forin(i, v) for(auto& i : v)

#define cinv(v) for(auto& i : v) cin >> i;

//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;

ll main0(ll n, ll k, map<ll, ll> m) {
	ll ans = 0;
	for (auto [t0, c0] : m) {
		ll t1 = t0 + 1;
		ll c1 = m.contains(t1) ? m[t1] : 0;

		if (t0 * c0 + t1 * c1 <= k) {
			ans = max(ans, t0 * c0 + t1 * c1);
			continue;
		}

		if (k / t0 <= c0) {
			ans = max(ans, min(k, t0 * (k / t0) + min(k / t0, c1)));
			continue;
		}

		ll at = c0 * t0;
		ll c1t = (k - at) / t1;
		assert(c1t < c1);
		at += c1t * t1;

		ans = max(ans, min(k, at + min(c0, c1 - c1t)));
	}
	return ans;
}

ll main1(ll n, ll k, map<ll, ll> m) {
	ll ans = 0;
	for (auto [t0, c0] : m) {
		ll t1 = t0 + 1;
		ll c1 = m.contains(t1) ? m[t1] : 0;

		if (t0 * c0 + t1 * c1 <= k) {
			ans = max(ans, t0 * c0 + t1 * c1);
			continue;
		}

		auto f = [&](ll c0t)
			{
				ll c1t = min(c1, (k - t0 * c0t) / t1);
				return c1t >= 0 ? c0t * t0 + c1t * t1 : 0;
			};

		forn(i, min(c0, k / t0) + 1)
			ans = max(ans, f(i));
	}
	return ans;
}

void tests() {
	mt19937 mt;
	
	ll n, k, c, mx;
	cin >> n >> k >> c >> mx;

	forn(i, c) {
		map<ll, ll> m;
		forn(i, n) {
			ll a = mt() % mx + 1, b = mt() % mx + 1;
			while (m.contains(a))
				a = mt() % mx + 1;
			m[a] = b;
		}

		if (main0(n, k, m) != main1(n, k, m)) {
			cout << '
';
			cout << '
';
			cout << '
';
			vll bv;
			for (auto [a, b] : m) {
				cout << a << ' ';
				bv.push_back(b);
			}
			cout << '
';
			forin(x, bv)
				cout << x << ' ';
			cout << '
';
			cout << '
';
			cout << '
';
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _DEBUG
	///while(1)
		//tests();
	while (cin)
#else
#endif // _DEBUG
	{
		ll t = 1;
		cin >> t;
		while (t--) {
			ll n, k;
			cin >> n >> k;
			vll a(n);
			cinv(a);

			vll b(n);
			cinv(b);

			map<ll, ll> m;
			forn(i, n)
				m[a[i]] = b[i];

			cout << main0(n, k, m);
			//cout << endl;
			//cout << main1(n, k, m);
			cout << endl;
		}
	}
}
/*
1 2 1
2 3
1 2
*/