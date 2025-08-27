#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,q;
		cin>>n>>q;
		vector<ll>a(n);
		for(int i = 0;i<n;i++)
		{
			cin>>a[i];
		}

		vector<ll>b;
		for(int i = 0;i<n-1;i++){
			b.push_back(abs(a[i+1]-a[i]));
		}

		vector<vector<ll>>stGCD(20,vector<ll>(b.size()));

		for(int i = 0;i<(int)b.size();i++)
		{
			stGCD[0][i] = b[i];
		}

		for(int i = 1;i < 20;i++)
		{
			for(int j = 0; j + (1<<i)-1 < (int)b.size();j++)
			{
				stGCD[i][j] = __gcd(stGCD[i-1][j],stGCD[i-1][j+ (1<<(i-1))]);
			}
		}
		while(q--)
		{
			int l,r;
			cin>>l>>r;
			if(l == r)
			{
				cout<<0<<" ";
				continue;
			}
			l--;
			r -= 2;
			int i = log2(r-l+1);
			ll gcd = __gcd(stGCD[i][l],stGCD[i][r-(1<<i)+1]);
			cout<<gcd<<" ";
		}
		cout<<"
";
	}
}