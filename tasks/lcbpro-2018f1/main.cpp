#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=80+10,M=610,INF=0x3f3f3f3f3f3f3f3f;
int n,mod,f[N][N][2],ans[N][N],a[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,ot[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(ot,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();ot[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='
'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline int calc(int l,int r)
{
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) f[i][j][0]=f[i][j][1]=0;
    f[l][r][0]=f[l][r][1]=1;
    for(int len=r-l+1;len<n;len++)
        for(int L=1,R=len;R<=n;L++,R++)
        {
            if(!(L<=l&&r<=R)) continue;
            if(R<n)
                f[L][R+1][1]=(f[L][R+1][1]+f[L][R][1]*(n-(R-L+2)+1))%mod,
                f[L][R+1][0]=(f[L][R+1][0]+f[L][R][1])%mod;
            if(L>1)
                f[L-1][R][0]=(f[L-1][R][0]+f[L][R][0]*(n-(R-L+2)+1))%mod,
                f[L-1][R][1]=(f[L-1][R][1]+f[L][R][0]*(n-(R-L+2)+1))%mod;
        }
    for(int i=l;i<=r;i++) f[1][n][0]=f[1][n][0]*(n-max(i-l+1,r-i+1)+1)%mod;
    return f[1][n][0];
}
inline void solve()
{
    n=read(),mod=read();for(int i=0;i<=n;i++) a[i]=0;
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) ans[i][j]=calc(i,j);
    for(int len=1;len<=n;len++)
        for(int L=1,R=len;R<=n;L++,R++)
        {
            ans[L][R]=(ans[L][R]-ans[L-1][R]-ans[L][R+1]+ans[L-1][R+1]+mod+mod)%mod;
            a[R-L+1]=(a[R-L+1]+ans[L][R])%mod;
        }a[0]=ksm(n,n,mod);for(int i=1;i<=n;i++) a[0]=(a[0]-a[i]+mod)%mod;
    for(int i=0;i<=n;i++) print(a[i]),put(' ');put('
');
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) ans[i][j]=0;
}
signed main()
{
    int T=1;
    T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
