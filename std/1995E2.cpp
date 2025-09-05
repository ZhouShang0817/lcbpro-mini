#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=414514;

namespace sgt{
        #define ls(x) (x<<1)
        #define rs(x) (x<<1|1)
        struct mtr{
                bool a[2][2];
                mtr operator*(const mtr &t)const{
                        mtr r;memset(r.a,0,4);int tp;
                        for(int i=0;i<2;++i) for(int k=0;k<2;++k){
                                tp=a[i][k];for(int j=0;j<2;++j) r.a[i][j]|=(t.a[k][j]&tp);
                        }
                        return r;
                }
        }s[N];
        void upd(int now,int ln,int rn,int p,bool f1,bool f2,bool v){
                if(ln==rn) return s[now].a[f1][f2]=v,void();
                int mid=ln+rn>>1;
                if(p<=mid) upd(ls(now),ln,mid,p,f1,f2,v);
                else upd(rs(now),mid+1,rn,p,f1,f2,v);
                s[now]=s[ls(now)]*s[rs(now)];
        }
        bool chk(){return s[1].a[0][0]|s[1].a[1][1];}
}

struct stt{int d;bool f1,f2;};

vector<stt> vc[N];

int val[N];

namespace Disc{
        struct nod{int v;stt s;}a[N];int n;
        void ins(int v,stt s){a[++n]=(nod){v,s};}
        int dsc(){
                sort(a+1,a+n+1,[](nod x,nod y){return x.v<y.v;});
                int c=0;for(int i=1;i<=n;++i) vc[c+=(a[i].v!=a[i-1].v)].push_back(a[i].s),val[c]=a[i].v;
                return c;
        }
}

int a[N];

int main()
{
        int T;scanf("%d",&T);while(T--){
                int n;scanf("%d",&n);
                for(int i=1;i<=n<<1;++i) scanf("%d",a+i);
                if(n&1^1){
                        int L=2e9,R=0;
                        for(int i=1;i<n;i+=2){
                                int l=a[i]+a[i+1],r=a[i+n]+a[i+n+1];
                                if(l>r) swap(l,r);
                                int p=a[i]+a[i+1+n],q=a[i+1]+a[i+n];
                                if(p>q) swap(p,q);
                                R=max(R,min(r,q));L=min(L,max(l,p));
                        }
                        printf("%d
",R-L);continue;
                }
                for(int i=1;i<=n;++i){
                        int k1=(i&1)?i:n+i,k2=k1+1,
                                o1=(k1-1+n)%(n<<1)+1,o2=(k2-1+n)%(n<<1)+1;
                        Disc::ins(a[k1]+a[k2],(stt){i,1,1});
                        Disc::ins(a[k1]+a[o2],(stt){i,1,0});
                        Disc::ins(a[o1]+a[k2],(stt){i,0,1});
                        Disc::ins(a[o1]+a[o2],(stt){i,0,0});
                }
                int m=Disc::dsc(),ans=2e9;
                for(int l=1,r=0;l<=m;++l){
                        while(r<m&&!sgt::chk()){
                                ++r;for(auto[d,f1,f2]:vc[r]) sgt::upd(1,1,n,d,f1,f2,1);
                        }
                        if(!sgt::chk()) break;
                        ans=min(ans,val[r]-val[l]);
                        for(auto[d,f1,f2]:vc[l]) sgt::upd(1,1,n,d,f1,f2,0);
                }
                printf("%d
",ans);
                for(int i=1;i<=m;++i) vc[i].clear();
                memset(sgt::s,0,n<<4);Disc::n=0;
        }
}