#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end;++i)

#define MAXN 1000001

typedef long long LL;

int x[MAXN],y[MAXN],d[MAXN];
LL w[MAXN],s[MAXN];
int n,m,maxn,maxm;


void licz(){
    d[0]=m;
    REP(i,m){
        w[y[i]]+=y[i];
        d[y[i]]-=1;
    }
    s[0]=w[0]+0*d[0];
    LL mnoznik=d[0];
    LL suma=w[0];
    FOR(i,1,maxn){
        mnoznik+=d[i];
        suma+=w[i];
        s[i]+=suma+i*mnoznik;
    }
    LL wynik=0;
    REP(i,n)
        wynik+=s[x[i]];
    printf("%lld",wynik);
}

int main(){
    maxn=0;
    maxm=0;
    scanf("%d%d",&n,&m);

    REP(i,n){
        scanf("%d",&x[i]);
        maxn=max(maxn,x[i]);
    }

    REP(i,m){
        scanf("%d",&y[i]);
        maxm=max(maxm,y[i]);
    }

    if(maxm!=maxn){
        puts("NIE");
    }else licz();

    return 0;
}
