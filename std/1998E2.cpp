//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 2e5 + 10;
const LL kInf = 1e18 + 2077;
//=============================================================
int n, x, ans[kN];
LL a[kN], sum[kN];
int fa[kN], sz[kN], son[kN][2];
int top, st[kN];
//=============================================================
int find(int x_) {
  return (fa[x_] == x_) ? (x_) : (fa[x_] = find(fa[x_]));
}
void merge(int u_, int v_) {
  int fu = find(u_), fv = find(v_);
  if (fu == fv) return ;
  fa[fu] = fv;
  sz[fv] += sz[fu];
}
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++ i) {
      std::cin >> a[i];
      sum[i] = sum[i - 1] + a[i];
    }
    a[0] = a[n + 1] = kInf;
    for (int i = 0; i <= n; ++ i) {
      son[i][0] = son[i][1] = ans[i] = 0;
      fa[i] = i, sz[i] = 1;
    }
    st[top = 0] = 0;
    for (int i = 1; i <= n; ++ i) {
      while (top && a[st[top]] < a[i]) -- top;
      son[i][0] = son[st[top]][1], son[st[top]][1] = i;

      if (son[i][0] && sum[i - 1] - sum[st[top]] >= a[i]) merge(son[i][0], i);
      st[++ top] = i;
      
      int f = find(st[1]), u = son[f][1];
      while (u) {
        if (sum[i] - sum[f] >= a[f]) merge(f, u);
        f = find(u), u = son[f][1];
      }
      ans[i] = sz[find(st[1])];
    }

    for (int i = 1; i <= n; ++ i) std::cout << ans[i] << " ";
    std::cout << "
";
  }
  return 0;
}
