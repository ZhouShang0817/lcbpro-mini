#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,m,k,nV,stk[N],top;
struct node{ll x,y0,y1;}a[N];
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n;nV=top=0;
		m=(n+1)/3;
		cout<<m<<endl;
		for (int i=1;i<=n;++i){
			if (!top){stk[top=1]=i;continue;}
			cout<<"? "<<stk[top]<<' '<<i<<endl;
			int w;cin>>w;
			if (top==1||w==k){
				k=w;stk[++top]=i;continue;
			}
			if (k) a[++nV]=(node){stk[top],i,stk[top-1]};
			else a[++nV]=(node){stk[top],stk[top-1],i};
			top-=2;
		}
		cout<<'!';
		while(m--){
			if (nV){
				cout<<' '<<a[nV].x<<' '<<(k?a[nV].y1:a[nV].y0);--nV;
			}
			else{
				cout<<' '<<stk[top]<<' '<<stk[top-1];top-=2;
			}
		}
		cout<<endl;
	}
	return 0;
}