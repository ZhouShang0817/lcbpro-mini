#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        int l = 1, r = 1e18;
        auto check = [&](int mid) -> bool {
            if (n == 1) return true;
            int d = a[1] + mid;
            int duo = 0;
            for (int i = 2; i <= n; i++) {
                int cnt = 0;
                if (i <= n && a[i] <= d) {
                    cnt++;
                    i++;
                }
                if (cnt == 0) duo++;
                if (i < n) d = a[i] + mid;
                else if (i == n) duo++;
            }
            return duo <= 1;
        };
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid - 1;
            else l = mid + 1;
        }
        cout << r + 1 << endl;
    }
    return 0;
}