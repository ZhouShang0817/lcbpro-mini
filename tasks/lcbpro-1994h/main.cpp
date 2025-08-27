#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[15],b[15],c[15],p;
int hsh(string s) {
	cout<<"? "<<s<<endl;
	int o; cin>>o; return o;
}
ll val(string s) {
	reverse(s.begin(),s.end());
	ll z=0;
	for(char o:s) z=z*p+o-'a'+1;
	return z;
}
void solve() {
	p=hsh("aa")-1;
	string X="zzzzzzzzzz";
	int x=hsh(X);
	for(int i=0,w=x;i<10;++i) a[i]=(i?26:25),b[i]=w%p,w/=p;
	string s;
	for(int i=0;i<10;++i) {
		if(a[i]>b[i]) c[i]=a[i]-b[i];
		else --a[i+1],c[i]=a[i];
		s.push_back(c[i]-1+'a');
	}
	int y=hsh(s);
	cout<<"! "<<p<<" "<<(val(X)-x)-(val(s)-y)<<endl;
}
signed main() {
	int T; cin>>T;
	while(T--) solve();
	return 0;
}