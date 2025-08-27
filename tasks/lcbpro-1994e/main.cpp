#include<bits/stdc++.h>
using namespace std;

int t,n,m,f; 
int main(){
	
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>m;
			int a=ans; 
			ans=max(ans,a|1);
			for(int j=2;j<=m;j++){
				cin>>f;
				ans=max(ans,a|j);
			}
		}
		cout<<ans<<"
";
	}
	

	
	return 0;
}