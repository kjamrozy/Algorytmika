#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

typedef long long LL;

#define MAXN 1000001

int x[MAXN],y[MAXN];/// x - standardowy teren, y - robocza kopia terenu
LL sp[MAXN+1],sl[MAXN+1],dp[MAXN+1],dl[MAXN+1];/// skosne, sp- prawa, sp- lewa
int n;
LL m;

LL Wyrownaj(int z){
    LL koszt=0;
    FOR(i,1,n)
        y[i]=x[i];
    FORD(i,n-1,1)
        if(y[i]>y[i+1]+z)
            y[i]=y[i+1]+z;
    FOR(i,2,n)
        if(y[i]>y[i-1]+z)
            y[i]=y[i-1]+z;
    FOR(i,1,n)
        koszt+=x[i]-y[i];
    return koszt;
}

void Licz_skosne(int z){
    FOR(i,1,n)
        sp[i]=sl[i]=dp[i]=dl[i]=0;
    FOR(i,1,n){
        int c=y[i]/z;
        int r=y[i]%z;
        dp[max(1,i-(c-1))]+=1;
        dp[i+1]-=1;
        dl[i]+=1;
        dl[min(i+c,n+1)]-=1;
        sp[max(0,i-c)]+=r;
        sl[min(n+1,i+c)]+=r;
    }
    LL mnp=0,mnl=0;
    FOR(i,1,n){
        mnp+=dp[i];
        mnl+=dl[i];
        sp[i]+=z*mnp;
        sl[i]+=z*mnl;
    }
}

bool Sprawdz(int z,int& k){
    LL koszt=Wyrownaj(z);
    LL piramida=0;
    Licz_skosne(z);
    FOR(i,1,n){
        LL c=LL(i-1)*z;
        if(y[i]-c>0)
            piramida+=y[i]-c;
    }
    if(koszt+piramida<=m){
        k=1;
        return true;
    }
    FOR(i,2,n){
        piramida-=sl[i-1];
        piramida+=sp[i];
        if(piramida+koszt<=m){
            k=i;
            return true;
        }
    }
    return false;
}

void Solve(){
    LL koszt=0;
    int maxx=-1,k=1;
    FOR(i,1,n){
        koszt+=x[i];
        maxx=max(maxx,x[i]);
    }
    if(koszt<=m){
        printf("%d %d",1,0);
        return;
    }
    int a=1,b=maxx;
    while(a!=b){
        int c=(a+b)/2;
        if(Sprawdz(c,k))
            b=c;
        else a=c+1;
    }
    printf("%d %d",k,a);
}

int main(){
    scanf("%d%lld",&n,&m);
    FOR(i,1,n)
        scanf("%d",&x[i]);
    Solve();
    return 0;
}
