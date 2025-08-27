#include<bits/stdc++.h>
std::mt19937_64 eng(std::chrono::steady_clock::now().time_since_epoch().count());
constexpr int maxn = 1e2 + 10;
std::pair<int, int> query(std::vector<int> a) {
   std::cout << "? " << a.size();
   for (int x : a) std::cout << ' ' << x;
   std::cout << std::endl;
   int x, y;
   std::cin >> x >> y;
   return std::make_pair(x, y);
}
inline void solve() {
   int n;
   std::cin >> n;
   int x0 = 0, y0 = 0;
   do {
      int x = eng() % n + 1, y;
      do {
         y = eng() % n + 1;
      } while (y == x);
      std::vector<int> vec;
      for (int i = 1; i <= n; i++) {
         if (i == x || i == y) continue;
         vec.push_back(i);
      }
      if (query(vec) == std::make_pair(n / 2, n / 2 + 1)) {
         x0 = x, y0 = y;
      }
   } while (! x0);
   std::pair<int, int> c[2] = {{0, 0}, {0, 0}};
   for (int i = 1, j = 0, k = 0; i <= n; i++) {
      if (i == x0 || i == y0) continue;
      if (j) {
         auto [x, y] = query({i, j, x0, y0});
         if (x == n / 2 || x == n / 2 + 1 || y == n / 2 || y == n / 2 + 1) {
            c[k++] = {i, j};
         }
         j = 0;
      } else {
         j = i;
      }
   }
   if (! c[1].first) {
      std::cout << "! " << c[0].first << ' ' << c[0].second << std::endl;
   } else if (query({c[0].first, c[1].first, x0, y0}) == std::make_pair(n / 2, n / 2 + 1)) {
      std::cout << "! " << c[0].first << ' ' << c[1].first << std::endl;
   } else if (query({c[0].first, c[1].second, x0, y0}) == std::make_pair(n / 2, n / 2 + 1)) {
      std::cout << "! " << c[0].first << ' ' << c[1].second << std::endl;
   } else if (query({c[0].second, c[1].first, x0, y0}) == std::make_pair(n / 2, n / 2 + 1)) {
      std::cout << "! " << c[0].second << ' ' << c[1].first << std::endl;
   } else {
      std::cout << "! " << c[0].second << ' ' << c[1].second << std::endl;
   }
}
int main() {
   int T;
   for (std::cin >> T; T--; ) {
      solve();
   }
   return 0;
}
