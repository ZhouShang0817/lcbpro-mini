#include<bits/stdc++.h>
using namespace std;
long long t,n,l,y;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cin>>s;
		s='$'+s;
		l=y=0;
		for(long long i=1;i<=n;i++){
			if(s[i]=='1') y++;
			else if(s[i]=='0' && s[i-1]!='0') l++;
		}
		if(l>=y) cout<<"NO"<<'
';
		else cout<<"YES"<<'
';
	}
	return 0;
}
