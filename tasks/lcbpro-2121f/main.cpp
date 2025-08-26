#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

void solve() {
    int n;
    long long s, x;
    std::cin >> n >> s >> x;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }

    std::vector<int> next_x(n + 2, n + 1);
    std::vector<int> next_gt_x(n + 2, n + 1);

    for (int i = n - 1; i >= 0; --i) {
        next_x[i + 1] = next_x[i + 2];
        if (a[i] == x) {
            next_x[i + 1] = i + 1;
        }
        next_gt_x[i + 1] = next_gt_x[i + 2];
        if (a[i] > x) {
            next_gt_x[i + 1] = i + 1;
        }
    }

    std::vector<std::vector<std::pair<long long, int>>> queries_at(n + 1);
    for (int l = 1; l <= n; ++l) {
        int L = next_x[l];
        int R = next_gt_x[l] - 1;

        if (L <= R) {
            long long val = s + pref[l - 1];
            queries_at[R].push_back({val, 1});
            queries_at[L - 1].push_back({val, -1});
        }
    }

    long long total_ans = 0;
    std::map<long long, int> freq;

    for (int r = 0; r <= n; ++r) {
        freq[pref[r]]++;
        if (!queries_at[r].empty()) {
            for (const auto& p : queries_at[r]) {
                long long val = p.first;
                int type = p.second;
                auto it = freq.find(val);
                if (it != freq.end()) {
                    total_ans += (long long)type * it->second;
                }
            }
        }
    }

    std::cout << total_ans << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
