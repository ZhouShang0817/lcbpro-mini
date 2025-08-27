#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

const int MAX = 1e5 + 20;

int main() {
    fastio;
    int n,k,q; cin >> n >> k >> q;
    int a[n][k];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < k; j++) cin >> a[i][j];
    }
    for (int j = 0; j < k; j++){
        for (int i = 1; i < n; i++) a[i][j] |= a[i-1][j];
    }
    int lo,hi;
    for (int query = 0; query < q; query++){
        bool possible = true;
        lo = -1; hi = MAX;
        int m; cin >> m;
        for (int rq = 0; rq < m; rq++){    
            int r, c; char o; cin >> r >> o >> c; --r;
            if (o=='<'){
                int ans = -1;
                int left = 0; int right = n-1;
                while(left<=right){
                    int middle = (left+right)/2;
                    if (a[middle][r]<c){
                        left=middle+1;
                        ans=max(ans,middle);
                    }
                    else{
                        right=middle-1;
                    }
                }
                if (ans==-1) possible=false;
                else hi=min(hi,ans);
            }
            else{
                int ans = n;
                int left = 0; int right = n-1;
                while(left<=right){
                    int middle = (left+right)/2;
                    if (a[middle][r]>c){
                        right=middle-1;
                        ans=min(ans,middle);
                    }
                    else{
                        left=middle+1;
                    }
                }
                if (ans==n) possible=false;
                else lo=max(lo,ans);
            }
        }
        cout << ((!possible || lo>hi) ? -1 : max(lo+1,1)) << '
';
    }
    return 0;
}