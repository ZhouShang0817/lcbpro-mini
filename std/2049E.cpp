#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"
"
const int inf=1e16;
int check(int l,int r){
    cout<<"? "<<l<<" "<<r<<endl;
    int pos;cin>>pos;
    return pos;
}
signed main(){
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int mid1=n/2,mid2=mid1/2;
        int val1=check(1,mid2),val2=check(mid2+1,mid1),val3=check(mid1+1,n);
        int g=0,l=0,r=0,k=0;
        if(val1==val2){
            l=1;r=mid1;
            if(val3){
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(mid,n)==0)g=mid,l=mid+1;
                    else r=mid-1;
                }
                k=n-g+1;
            }
            else{
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(1,mid)==1)g=mid,r=mid-1;
                    else l=mid+1;
                }
                k=g;
            }
        }
        else{
            l=mid1+1;r=n;
            if(val3){
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(mid,n)==1)g=mid,l=mid+1;
                    else r=mid-1;
                }
                k=n-g+1;
            }
            else{
                while(l<=r){
                    int mid=(l+r)/2;
                    if(check(1,mid)==0)g=mid,r=mid-1;
                    else l=mid+1;
                }
                k=g;
            }
        }
        cout<<"! "<<k<<endl;
    }
	return 0;
}
