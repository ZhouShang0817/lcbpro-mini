#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <bitset>
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
const int N=2010;
int T,n,mn,tot;
int a[N];
vector<int> X[N],Y[N];

void path1(int num) //(1,1)->(1,2)->(2,2)->(2,3)->(3,3)->...
{
	for(int i=1;i<=n;i++)
	{
		X[num].push_back(i),Y[num].push_back(i);
		if(i!=n)
		{
			X[num].push_back(i),Y[num].push_back(i+1);
			swap(a[i],a[i+1]);
		}
	}
}

void path2(int num) //(1,1)->(1,n)->(n,n)
{
	for(int i=1;i<=n;i++)
	{
		X[num].push_back(1),Y[num].push_back(i);
		swap(a[1],a[i]);
	}
	for(int i=2;i<=n;i++)
	{
		X[num].push_back(i),Y[num].push_back(n);
		swap(a[i],a[n]);
	}
}

void walk1(int j)
{
	X[tot].push_back(j-1),Y[tot].push_back(j);
	X[tot].push_back(j-1),Y[tot].push_back(j+1);
    X[tot].push_back(j),Y[tot].push_back(j+1);
	X[tot].push_back(j+1),Y[tot].push_back(j+1);
    swap(a[j-1],a[j+1]);
}

void walk2(int j)
{
	X[tot].push_back(j-1),Y[tot].push_back(j);
	X[tot].push_back(j),Y[tot].push_back(j);
	X[tot].push_back(j),Y[tot].push_back(j+1);
	X[tot].push_back(j+1),Y[tot].push_back(j+1);
	swap(a[j-1],a[j]);
	swap(a[j],a[j+1]);
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		mn=n;tot=0;
		for(int i=1;i<=n;i++)   mn=min(mn,a[i]);
		for(int i=1;i<=3*n;i++) X[i].clear(),Y[i].clear();
		int p1;
		for(int i=1;i<=n;i++) if(a[i]==mn) p1=i;
		if(p1!=1)
		{
		    tot++;
		    for(int i=1;i<=p1;i++) X[tot].push_back(1),Y[tot].push_back(i),swap(a[1],a[i]);
		    for(int i=2;i<=p1;i++) X[tot].push_back(i),Y[tot].push_back(p1),swap(a[i],a[p1]);
		    for(int i=p1+1;i<=n;i++) X[tot].push_back(p1),Y[tot].push_back(i),swap(a[p1],a[i]);
		    for(int i=p1+1;i<=n;i++) X[tot].push_back(i),Y[tot].push_back(n),swap(a[i],a[n]);
		}
		for(int i=2;i<=n;i++)
		{
			tot++;
			X[tot].push_back(1),Y[tot].push_back(1);
			if(n&1)
			{
				if(i&1)
				{
					for(int j=2;j<=n;j+=2)
					{
						if(j+1==i) walk2(j);
						else if(a[j]>a[j+1]) walk1(j);
						else walk2(j);
					}
				}
				else
				{
					for(int j=2;j<=n;j+=2)
					{
						if(a[j]>a[j+1]) walk1(j);
						else walk2(j);
					}
				}
			}
			else
			{
				if(i&1)
				{
					for(int j=2;j<=n;j+=2)
					{
						if(j==i-1)
						{
							X[tot].push_back(j-1),Y[tot].push_back(j);
							X[tot].push_back(j),Y[tot].push_back(j);
							swap(a[j-1],a[j]);
							j--;
						}
						else if(a[j]>a[j+1]) walk1(j);
						else walk2(j);
					}
				}
				else
				{
					for(int j=2;j<=n;j+=2)
					{
						if(j==i)
						{
							X[tot].push_back(j-1),Y[tot].push_back(j);
							X[tot].push_back(j),Y[tot].push_back(j);
							swap(a[j-1],a[j]);
							j--;
						}
						else if(a[j]>a[j+1]) walk1(j);
						else walk2(j);
					}
				}
			}
			path2(++tot);
		}
		printf("%d
",tot);
		for(int i=1;i<=tot;i++)
		{
			for(int j=1;j<2*n-1;j++)
			{
			    if(X[i][j]==X[i][j-1]) printf("R");
			    else printf("D");
			}
			printf("
");
		}

	}

	return 0;
}