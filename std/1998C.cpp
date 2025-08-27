#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
const int maxn=2e5+10;
struct node{
        int da,b;
}arr[maxn];
bool cmp(node a,node b){
        if(a.b==b.b){
                return a.da>b.da;
        }else{
                return a.b<b.b;
        }
}
bool vis[maxn];
int mx0,i0,mx1,i1; 
int cnt;
int n,k;
bool check(int x){
        int sum=0;
        for(int i=1;i<=cnt;i++){
                if(vis[i]) continue;
                if(arr[i].da>=x) sum++;
        }
        int q=k;
        for(int i=cnt+1;i<=n;i++){
                if(vis[i]) continue;
                if(arr[i].da>=x){
                        sum++;
                }else if(x-arr[i].da<=q){
                        q-=(x-arr[i].da);
                        sum++;
                }
        }
        return sum>((n-1)/2);
}
bool cmp1(node a,node b){
        return a.da<b.da;
}
signed main(){
        int T;
        scanf("%lld",&T);
        while(T--){
                cnt=0;
                scanf("%lld%lld",&n,&k);
                for(int i=1;i<=n;i++){
                        scanf("%lld",&arr[i].da);
                }
                for(int i=1;i<=n;i++){
                        scanf("%lld",&arr[i].b);
                        if(!arr[i].b) cnt++;
                }
                sort(arr+1,arr+1+n,cmp);
                int ans=0,l=0,r=inf;
                if(cnt){
                        vis[1]=true;
                        
                        while(l<r){
                                int mid=(l+r)>>1;
                                if(check(mid))  l=mid+1;
                                else r=mid;
                        } 
                        ans=max(arr[1].da+l-1,ans);
                        vis[1]=false;
                        
                }
                if(cnt!=n){
                        swap(arr[cnt+1],arr[n]);
                        sort(arr+1,arr+n,cmp1);
                        ans=max(arr[n].da+k+arr[n/2].da,ans);
                }
                
                printf("%lld
",ans);
        }
        return 0;
}

