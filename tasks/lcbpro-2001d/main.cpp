#include<bits/stdc++.h>
using namespace std;
#define endl '
'
#define int long long
const int N=3e5+10;
int T,n,m,a[N],suf[N],wz[N];
struct node{
    int l,r,val,jian,maxx,max_pos,minn,min_pos;
}t[N*4];
struct nod{
    int zb,qz;
};
void init()
{
}
void build(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;t[p].jian=0;
    if(l==r)
    {
        t[p].val=suf[l];
        t[p].maxx=t[p].minn=a[l];
        t[p].max_pos=t[p].min_pos=l;
        return ;
    }
    int mid=(l+r)/2;
    build(p*2,l,mid);build(p*2+1,mid+1,r);
    if(t[p*2].maxx>=t[p*2+1].maxx)
    {
        t[p].maxx=t[p*2].maxx;
        t[p].max_pos=t[p*2].max_pos;
    }
    else
    {
        t[p].maxx=t[p*2+1].maxx;
        t[p].max_pos=t[p*2+1].max_pos;
    }
    if(t[p*2].minn<=t[p*2+1].minn)
    {
        t[p].minn=t[p*2].minn;
        t[p].min_pos=t[p*2].min_pos;
    }
    else
    {
        t[p].minn=t[p*2+1].minn;
        t[p].min_pos=t[p*2+1].min_pos;
    }
}
int ask(int p,int x)
{
    if(t[p].l==t[p].r) return t[p].jian;
    int mid=(t[p].l+t[p].r)/2;
    if(x<=mid) return t[p].jian+ask(p*2,x);
    else return t[p].jian+ask(p*2+1,x);
}
void change(int p,int l,int r)
{
    if(t[p].l>=l&&t[p].r<=r) {t[p].jian+=1; return ;}
    int mid=(t[p].l+t[p].r)/2;
    if(l<=mid) change(p*2,l,r);
    if(r>mid) change(p*2+1,l,r);
}
nod ask1(int p,int l,int r)
{
    nod tmp,tmp1;tmp.qz=0;
    if(t[p].l>=l&&t[p].r<=r)
    {
        tmp.zb=t[p].max_pos;
        tmp.qz=t[p].maxx;
        return tmp;
    }
    int mid=(t[p].l+t[p].r)/2;
    if(l<=mid) tmp=ask1(p*2,l,r);
    if(r>mid)
    {
        tmp1=ask1(p*2+1,l,r);
        if(tmp1.qz>tmp.qz) return tmp1;
    }
    return tmp;
}
nod ask2(int p,int l,int r)
{
    nod tmp,tmp1;tmp.qz=1e9;
    if(t[p].l>=l&&t[p].r<=r)
    {
        tmp.zb=t[p].min_pos;
        tmp.qz=t[p].minn;
        return tmp;
    }
    int mid=(t[p].l+t[p].r)/2;
    if(l<=mid) tmp=ask2(p*2,l,r);
    if(r>mid)
    {
        tmp1=ask2(p*2+1,l,r);
        if(tmp1.qz<tmp.qz) return tmp1;
    }
    return tmp;
}
void change1(int p,int k)
{
    if(t[p].l==t[p].r) {t[p].maxx=0; t[p].minn=1e9; return ;}
    int mid=(t[p].l+t[p].r)/2;
    if(k<=mid) change1(p*2,k);
    else change1(p*2+1,k);
    if(t[p*2].maxx>=t[p*2+1].maxx)
    {
        t[p].maxx=t[p*2].maxx;
        t[p].max_pos=t[p*2].max_pos;
    }
    else
    {
        t[p].maxx=t[p*2+1].maxx;
        t[p].max_pos=t[p*2+1].max_pos;
    }
    if(t[p*2].minn<=t[p*2+1].minn)
    {
        t[p].minn=t[p*2].minn;
        t[p].min_pos=t[p*2].min_pos;
    }
    else
    {
        t[p].minn=t[p*2+1].minn;
        t[p].min_pos=t[p*2+1].min_pos;
    }
}
void solve()
{
    cin>>n;
    init();
    vector<int> c[n+2];
    for(int i=1;i<=n;i++)
    {
       cin>>a[i];
       c[a[i]].emplace_back(i);
    }
    suf[n+1]=a[n+1]=0;
    map<int,int> b;
    for(int i=n;i>=1;i--)
    {
        suf[i]=suf[i+1];
        if(!b[a[i]])
        {
            b[a[i]]=1;
            suf[i]++;
            wz[a[i]]=i;
        }
    }
    m=suf[1];
    build(1,1,n+1);
    vector<int> ans;
    int last=0;
    for(int i=1;i<=m;i++)
    {
        int l=1,r=n+1,pos;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(suf[mid]-ask(1,mid)<m-i+1) {pos=mid; r=mid-1;}
            else l=mid+1;
        }
        pos--;
        int poss;
        if(i&1) poss=ask1(1,last+1,pos).zb;
        else poss=ask2(1,last+1,pos).zb;
        ans.emplace_back(a[poss]);
        change(1,1,wz[a[poss]]);
        last=poss;
        for(int j:c[a[poss]])
        change1(1,j);
    }
    cout<<ans.size()<<endl;
    for(auto i : ans)
    cout<<i<<" ";
    cout<<endl;
}
signed main()
{
    ios::sync_with_stdio(0);
	cin.tie(0);cout.tie();
    cin>>T;
    while(T--) solve();
}