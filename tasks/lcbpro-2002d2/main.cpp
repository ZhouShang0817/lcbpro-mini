#include<bits/stdc++.h>
using namespace std;
const int NR = 3e5;
const int MR = 20;
vector<int> mp[NR + 10];
int fa[NR + 10][MR + 10];
int dep[NR + 10];
void init(int u, int father){
    fa[u][0] = father;
    dep[u] = dep[father] + 1;
    for(int j = 1;j <= MR;j++){
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }
    for(auto i : mp[u]){
        if(i != father){
            init(i, u);
        }
    }
    return ;
}
int lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    for(int j = MR;j >= 0;j--){
        if(dep[fa[u][j]] >= dep[v]){
            u = fa[u][j];
        }
    }
    if(u == v) return u;
    for(int j = MR;j >= 0;j--){
        if(fa[u][j] != fa[v][j]){
            u = fa[u][j];
            v = fa[v][j];
        }
    }
    return fa[u][0];
}
int dfn[NR + 10];
int n;
bool check(int x){
    if(x < 1 || x >= n) return false;
    int u = dfn[x];
    int v = dfn[x + 1];
    if(fa[v][0] == u || fa[v][0] == 1) return true;
    if(fa[v][0] == 0) return false;
    if(lca(u, fa[v][0]) == fa[v][0]) return true;
    return false;
}
bool oldcheck(int x){
    if(x < 1 || x >= n) return false;
    int u = dfn[x];
    int v = dfn[x + 1];
    if(fa[v][0] == u || fa[v][0] == 1) return true;
    for(int j = MR;j >= 0;j--){
        if(dep[fa[u][j]] >= dep[fa[v][0]]){
            u = fa[u][j];
        }
    }
    return u == fa[v][0];
}

int main(){
    // freopen("1.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while(T--){
        int q;
        scanf("%d%d", &n, &q);
        for(int i = 2;i <= n;i++){
            scanf("%d", &fa[i][0]);
            mp[i].emplace_back(fa[i][0]);
            mp[fa[i][0]].emplace_back(i);
        }
        for(int i = 1;i <= n;i++){
            scanf("%d", &dfn[i]);
        }
        init(1, 0);
        // fa[1][0] = 1;
        int ans = 0;
        for(int i = 1;i < n;i++){
            if(check(i)) ans++;
        }
        // printf("ans=%d
", ans);
        while(q--){
            int x, y;
            scanf("%d%d", &x, &y);
            if(x > y) swap(x, y);
            if(check(y)) ans--;
            if(check(y - 1)) ans--;
            if(x + 1 != y && check(x)) ans--;
            if(check(x - 1)) ans--;
            swap(dfn[x], dfn[y]);
            // printf("dfn={");
            // for(int i = 1;i <= n;i++){
            //     printf("%d, ", dfn[i]);
            // }
            // printf("}
");
            // printf("yasogi%d
", oldcheck(1));
            // printf("sogi%d
", check(1));
            // printf("yasogi%d
", oldcheck(2));
            // printf("sogi%d
", check(2));
            if(check(y)) ans++;
            if(check(y - 1)) ans++;
            if(x + 1 != y && check(x)) ans++;
            if(check(x - 1)) ans++;
            // printf("ans=%d
", ans);
            printf("%s
", ans == n - 1 ? "YES" : "NO");
        }
        dep[0] = 0;
        for(int i = 1;i <= n;i++){
            mp[i].clear();
        }
    }
    return 0;
}