#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
#define PII pair<int,int>
using namespace std;
const int MAXN = 2e5 + 10;
PII a[MAXN];
int T,n,num=0,tot=0,ans=0;
int fa[MAXN],siz[MAXN];
int l[MAXN],r[MAXN];//联通块的左右端点 
int pos[MAXN];//最大值的位置(奇偶)
bool vis[MAXN];//是否加入 
bool calc(int x){
	/*
	检查一个连通块在选ceil(siz/2)的时候选没选最大值
	当左右端点同奇偶，选的位置固定，eg: (1) 2 (3) 4 (5)，
	&pos[x]是看在这个连通块的奇数位置有没有最大值
	当左右端点不同奇偶，有两种情况，eg：(1) 2 (3) 4 或 1 (2) 3 (4)  
	&pos[x]是看在这个连通块有没有最大值(只要有就有一种情况可以取到)
	*/
	return (((1<<(l[x]&1))|(1<<(r[x]&1)))&pos[x]);
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	tot-=calc(x);
	tot-=calc(y);
	l[x]=min(l[x],l[y]);
	r[x]=max(r[x],r[y]);
	pos[x]|=pos[y];
	tot+=calc(x);
	num-=(siz[x]+1)/2;
	num-=(siz[y]+1)/2;
	siz[x]+=siz[y];
	num+=(siz[x]+1)/2; 
	fa[y]=x;
}
int main(){
	scanf("%d",&T);
	while(T--){
		num=tot=ans=0;
		//num是选的数的总数 
		//tot是选了最大值的连通块的个数  
		scanf("%d",&n);
		FL(i,0,n+1) fa[i]=l[i]=r[i]=i,siz[i]=1,pos[i]=vis[i]=0;
		FL(i,1,n) scanf("%d",&a[i].first),a[i].second=i; 
		sort(a+1,a+n+1);
		reverse(a+1,a+n+1);
		FL(i,1,n) if(a[i].first==a[1].first) pos[a[i].second]|=(1<<(a[i].second&1));//在a[i].second这个连通块里在(a[i].second&1)位有最大值 
		FL(i,1,n){
			//从大到小枚举最小值val 
			int val=a[i].first,id=a[i].second;
			vis[id]=1;
			tot+=calc(id);
			num++;
			//id作为一个一个元素的连通块加入，num和tot要更新！ 
			if(vis[id+1]) merge(id,id+1);
			if(vis[id-1]) merge(id,id-1);
			ans=max(ans,a[1].first+val+num-(tot==0));//max+min+num-(tot==0)，如果没有连通块取到最大值答案减1 
		}
//		FL(i,1,n) printf("%d ",a[i].first);
//		puts("");
		printf("%d
",ans);
	}
}
