#include <bits/stdc++.h>
using namespace std;
#define int long long

int l, r, g;

void solve() {
    int len = r - l;
    while (len >= 0) {
        for (int i = l; i + len <= r; i++) {
            if (gcd(i, i + len) == 1) {
                cout << i * g << ' ' << (i + len) * g << endl;
                return;
            }
        }
        len--;
    }
    cout << -1 << ' ' << -1 << endl;
}

signed main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> l >> r >> g;
        l = (l + g - 1) / g, r = r / g;
        solve();
    }
    return 0;
}