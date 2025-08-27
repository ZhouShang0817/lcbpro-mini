#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
char s[maxn];
int diff[maxn], res[maxn];

void add(int l, int r, int delta) {
    diff[l] += delta;
    diff[r + 1] -= delta;
}

bool valid;

int dfs(int l, int r, int required, int lvl) {
    if (l > r) return 0;

    if (l == r) {
        res[l] = lvl;
        return lvl;
    }

    if (s[l] == 'L' && s[r] == 'R') {
        res[l] = lvl;
        res[r] = lvl;
        return max(lvl, dfs(l + 1, r - 1, required, lvl + 1));
    }

    if (s[l] == 'R' && s[r] == 'L') {
        for (int i = l; i <= r; i++) {
            res[i] = lvl + 1;
        }
        if (required == 1) valid = false;
        return lvl + 1;
    }

    if (s[l] == 'L') {
        res[l] = lvl;
        res[r] = max(lvl, dfs(l + 1, r - 1, 1, lvl + 1)) + 1;
        return res[r];
    }

    res[r] = lvl;
    res[l] = max(lvl, dfs(l + 1, r - 1, 1, lvl + 1)) + 1;
    return res[l];
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        scanf("%s", s + 1);
        for (int i = 1; i <= n; i++) diff[i] = 0;
        valid = true;
        dfs(1, n, -1, 0);
        if (!valid) puts("-1");
        else {
            for (int i = 1; i <= n; i++) printf("%d ", res[i]);
            printf("
");
        }
    }
}