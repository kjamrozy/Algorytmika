#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <cassert>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 202
#define MAXM 1000020

typedef long long LL;

const LL INF = 10000000000000001ll;

int n,m;
char* imiona[MAXN],buf[MAXM];
int P[MAXM],L[MAXN];

struct M{
    LL T[MAXN][MAXN];
    void operator*=(const M& b){
        static LL t[MAXN][MAXN];
        FOR(i,1,n)
            FOR(j,1,n){
                LL res=INF;
                FOR(k,1,n)
                    res=min(res,b.T[k][j]+T[i][k]);
                t[i][j]=res;
            }
        FOR(i,1,n)
            FOR(j,1,n)
                T[i][j]=t[i][j];
    }
}zera,pom;

void init(){
    FOR(i,1,n){
        int x=0;
        for(int j=1;j<L[i];++j){
            while(x>0 && imiona[i][x]!=imiona[i][j]) x=P[x-1];
            if(imiona[i][x]==imiona[i][j]) ++x;
            P[j]=x;
        }
        FOR(k,1,n){
            int x=0;
            for(int j=(k!=i) ? 0 : 1;j<L[k];++j){
                while(x>0 && imiona[i][x]!=imiona[k][j]) x=P[x-1];
                if(imiona[i][x]==imiona[k][j]) ++x;
            }
            pom.T[k][i]=L[i]-x;
        }
        pom.T[i][n+1]=INF;
        pom.T[n+1][i]=L[i];
    }
    pom.T[n+1][n+1]=INF;
    ++n;
    FOR(i,1,n)
        FOR(j,1,n)
            zera.T[i][j]=INF;
    zera.T[n][n]=0;
}

void Solve(){
    FOR(i,0,30){
        if(m&(1<<i))
            zera*=pom;
        pom*=pom;
    }
    LL ans=INF;
    FOR(i,1,n)
        ans=min(ans,zera.T[n][i]);
    printf("%lld",ans);
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        scanf("%s",buf);
        L[i]=strlen(buf);
        imiona[i]=strdup(buf);
    }
    init();
    Solve();
    return 0;
}
