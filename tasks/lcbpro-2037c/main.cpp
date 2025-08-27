#include<bits/stdc++.h>
using namespace std;
 
void solve(){
    int n;
    cin>>n;
    if(n<=4)cout<<"-1
";
    else{
        for(int i=n/2*2;i>=6;i-=2)cout<<i<<' ';
        cout<<"2 4 5 1 3 ";
        for(int i=7;i<=n;i+=2)cout<<i<<' ';
        cout<<'
';
    }
}
 
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
}