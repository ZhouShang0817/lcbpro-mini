#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
struct val
{
	long long v,p,t;
}a[400000],b1[400000],b2[400000];
long long q,n=0,k,id[400000],t[2][1600][400],s[2][1600][400],ad[400000],op[400000],x[400000],sum=0;
pair<long long,int>c[400000];
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void pushup(long long x)
{
	ad[x]+=a[(x-1)*k+1].v;
	for(int i=0;i<=k;i++)t[0][x][i]=s[0][x][i]=t[1][x][i]=s[1][x][i]=0;
	for(int i=(x-1)*k+2;i<=x*k;i++)
	    {
	    a[i].v-=a[(x-1)*k+1].v;
	    if(a[i].t)t[a[i].t-1][x][a[i].v]+=c[a[i].p].first;
	    }
	a[(x-1)*k+1].v=0;
	if(a[(x-1)*k+1].t)t[a[(x-1)*k+1].t-1][x][a[(x-1)*k+1].v]+=c[a[(x-1)*k+1].p].first;
	s[0][x][0]=t[0][x][0],s[1][x][0]=t[1][x][0];
	for(int i=1;i<=k;i++)s[0][x][i]=s[0][x][i-1]+t[0][x][i],s[1][x][i]=s[1][x][i-1]+t[1][x][i];
}

void rebuild(long long x,long long l,long long r,long long c)
{
	long long p1=0,p2=0,n1=1,n2=1;
	for(int i=(x-1)*k+1;i<=x*k;i++)
	    if(a[i].p>=l&&a[i].p<=r)a[i].v+=c,b1[++p1]=a[i];
	    else b2[++p2]=a[i];
	for(int i=(x-1)*k+1;i<=x*k;i++)
	    if((n1<=p1&&b1[n1].v<=b2[n2].v)||(n2>p2))a[i]=b1[n1],n1++;
	    else a[i]=b2[n2],n2++;
    pushup(x);
}

void add(long long l,long long r,long long c)
{
	long long p=id[l],q=id[r];
	if(p==q)rebuild(p,l,r,c);
	else
	   {
	   	rebuild(p,l,p*k,c),rebuild(q,(q-1)*k+1,r,c);
	   	for(int i=p+1;i<=q-1;i++)ad[i]+=c;
	   }
}

int main()
{
	q=read();
	for(int i=1;i<=q;i++)op[i]=read(),x[i]=read(),c[++n]=make_pair(x[i],i);
	sort(c+1,c+n+1),k=300;
	for(int i=1;i<=n;i++)id[i]=(i-1)/k+1,a[i].p=i;
	for(int i=1;i<=q;i++)
	    {
	    	x[i]=lower_bound(c+1,c+n+1,make_pair(x[i],i))-c;
	    	for(int j=(id[x[i]]-1)*k+1;j<=id[x[i]]*k;j++)
	    	    if(a[j].p==x[i])a[j].t=op[i];
	    	if(op[i]==1)add(1,x[i],1),sum+=c[x[i]].first;
	    	else add(1,x[i],-1);
	    	long long ans=0;
	    	for(int j=1;j<=id[n];j++)
	    	    {
	    	    	long long p=max(-1ll,min(k+1,-ad[j]));
					if(p>k)ans+=s[0][j][k];
					else if(p>=0)ans+=s[0][j][p];
					if(p<=k)
					   {
		    	       if(p>0)ans+=(s[1][j][k]-s[1][j][p-1]);
		    	       else ans+=s[1][j][k];
		    	       }
				}
			printf("%lld
",ans+sum);
		}
	return 0;
}
