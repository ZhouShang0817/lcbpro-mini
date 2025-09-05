// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
using namespace std;
using ll = long long int;
mt19937_64 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());

/**
 * Point-update Segment Tree
 * Source: kactl
 * Description: Iterative point-update segment tree, ranges are half-open i.e [L, R).
 *              f is any associative function.
 * Time: O(logn) update/query
 */

template<class T, T unit = T()>
struct SegTree {
	T f(T a, T b) {
        a[0] += b[0];
        if (a[1] < b[1]) a[1] = b[1], a[2] = b[2];
        return a;
    }
	vector<T> s; int n;
	SegTree(int _n = 0, T def = unit) : s(2*_n, def), n(_n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) {
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

#include <ext/pb_ds/assoc_container.hpp>

struct splitmix64_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        vector<ll> a(n);
        for (auto &x : a) cin >> x;

        map<ll, int> cache;

        struct Node {
            int L, R, M; // [L, R)
            set<array<int, 2>> by_l, by_r;
            void ins(int l, int r) {
                by_l.insert({l, r});
                by_r.insert({r, l});
            }
            void del(int l, int r) {
                by_l.erase({l, r});
                by_r.erase({r, l});
            }
        };
        vector<Node> ITree(4*n);
        auto build = [&] (const auto &self, int node, int l, int r) -> void {
            int mid = (l + r)/2;
            ITree[node].L = l;
            ITree[node].R = r;
            ITree[node].M = mid;
            if (l+1 == r) return;
            self(self, 2*node + 1, l, mid);
            self(self, 2*node + 2, mid, r);
        };
        build(build, 0, 0, n);
        auto insert = [&] (const auto &self, int node, int l, int r) -> void { // Insert interval [l, r) into the tree
            if (ITree[node].L+1 == ITree[node].R) {
                ITree[node].ins(l, r);
                return;
            }

            if (l >= ITree[node].M) self(self, 2*node+2, l, r);
            else if (r <= ITree[node].M) self(self, 2*node+1, l, r);
            else ITree[node].ins(l, r);
        };
        auto erase = [&] (const auto &self, int node, int x) -> void { // Delete all intervals covering point x
            if (x < ITree[node].M) {
                // Delete some prefix
                auto &st = ITree[node].by_l;
                while (!st.empty()) {
                    auto [l, r] = *begin(st);
                    if (l <= x) {
                        ITree[node].del(l, r);
                        ll id = 1ll*(n+1)*l + r;
                        cache.erase(id);
                    }
                    else break;
                }
            }
            else {
                // Delete some suffix
                auto &st = ITree[node].by_r;
                while (!st.empty()) {
                    auto [r, l] = *rbegin(st);
                    if (r > x) {
                        ITree[node].del(l, r);
                        ll id = 1ll*(n+1)*l + r;
                        cache.erase(id);
                    }
                    else break;
                }
            }

            if (ITree[node].L+1 == ITree[node].R) return;
            if (x < ITree[node].M) self(self, 2*node+1, x);
            else self(self, 2*node+2, x);
        };

        constexpr array<ll, 3> unit = {0, 0, -1};
        SegTree<array<ll, 3>, unit> seg(n);
        for (int i = 0; i < n; ++i) seg.update(i, array<ll, 3>{a[i], a[i], i});
        
        auto solve = [&] (const auto &self, int L, int R) -> int {
            if (R-L <= 2) return -1;
            ll id = 1ll*L*(n+1) + R;
            if (cache.find(id) != cache.end()) return cache[id];
            
            auto [sm, mx, pivot] = seg.query(L, R);

            insert(insert, 0, L, R);
            if (mx < sm - mx) {
                return cache[id] = R-L;
            }
            else {
                int ret = self(self, L, pivot);
                ret = max(ret, self(self, pivot+1, R));
                return cache[id] = ret;
            }
        };

        while (q--) {
            int type; cin >> type;
            if (type == 1) {
                int l, r; cin >> l >> r;
                cout << solve(solve, l-1, r) << '\n';
            }
            else {
                ll pos, val; cin >> pos >> val; --pos;

                erase(erase, 0, pos);
                if (pos) erase(erase, 0, pos-1);
                if (pos+1 < n) erase(erase, 0, pos+1);
                seg.update(pos, array<ll, 3>{val, val, pos});
            }
        }
    }
}