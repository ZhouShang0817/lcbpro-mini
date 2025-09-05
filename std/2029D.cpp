#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define pii pair<ll,ll>
#define vi vector<ll>
#define mii map<ll,ll>
#define all(x) x.begin(),x.end()
#define YES cout<<"YES"<<endl;
#define NO cout<<"NO"<<endl;
#define tern(x,y,z) ((x)?(y):(z))
#define PB push_back
#define F first
#define S second
#define MP make_pair
#define asc(i,a,b) for (int i = a; i <= b; i++)
#define desc(i,a,b) for (int i = a; i >= b; i--)

const int M = 1e9 + 7;
const int N = 2e5 + 5;
const int maxint = 2e9 + 10;

// dont use unordered map without custom hash
// bfs when edge = 1 (instead of djikistra) O(E) vs O(ElogV)
// max, min qs  => might be binary search
// for set s.lower_bound()
// dont complicate qs till div2 D

void solve(){
    int n, m ; cin>>n>>m;
    set<int> graph[n+1];
    asc(i, 1, m){
        int x, y; cin>>x>>y;
        graph[x].insert(y);
        graph[y].insert(x);
    }
    set<pii> s; 
    vector<vi> ans;
    asc(i, 1, n){
        if(graph[i].size() < 2) continue;
        s.insert({ graph[i].size(), i });
    }

    while(s.size()){
        auto [sz, u] = *s.begin();
        s.erase(MP(sz, u));
        if(sz != graph[u].size()) continue;
        int v1 = *graph[u].begin(); graph[u].erase(v1); graph[v1].erase(u); 
        int v2 = *graph[u].begin(); graph[u].erase(v2); graph[v2].erase(u); 
        ans.PB({ u, v1, v2 });
        if(graph[v1].find(v2) != graph[v1].end()){
            graph[v1].erase(v2);
            graph[v2].erase(v1);
        }else{
            graph[v1].insert(v2);
            graph[v2].insert(v1);
        }
        if(graph[v1].size() >= 2) s.insert({ graph[v1].size(), v1 });
        if(graph[v2].size() >= 2) s.insert({ graph[v2].size(), v2 });
        if(graph[u].size() >= 2) s.insert({ graph[u].size(), u });
    }
    // cout<<ans.size()<<endl;
    int u = 0;
    asc(i, 1, n){
        if(graph[i].size() == 1){
            u = i; break;
        }
    }

    if(u){
        vi vis(n+1, 0);
        int v = *graph[u].begin();
        vis[v] = 1; vis[u] = 1;
        asc(i, 1, n){
            if(vis[i]) continue;
            vis[i] = 1;
            if(graph[i].size()){
                int v1 = *graph[i].begin();
                ans.PB({ u , v, i });
                v = i;
                vis[v1] = 1;
            }else{
                ans.PB({ u , v, i });
                v = i;
            }
        }    
    }
    
    cout<<ans.size()<<endl;
    for(auto &vec: ans) cout<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<endl;
}   

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int test; 
    cin>>test;
    while(test--){
        solve();
    }
}