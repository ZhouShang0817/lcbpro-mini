# include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		map<int,int>m;
		for(int i=0;i<n;i++){
			m[s[i]]++;
		}
	vector<pair<int,char>>v;
	for(auto it : m){
		v.push_back({it.second,it.first});
	}
	sort(v.begin(),v.end());
	s[s.find(v[0].second)]=v.back().second;
	cout<<s<<endl;
	
	}
}