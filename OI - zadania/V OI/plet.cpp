#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;x++)
#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define ALL(c) (c).begin(),(c).end()
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) ((int)(x).size())

#define MAXN 1001
#define MAXT 23
#define MAXA 81

int w[MAXT*3+5][MAXA*3+5];
int t,a,n;

int main(){
    scanf("%d%d%d",&t,&a,&n);
    REP(i,23)
        REP(j,81)
            w[i][j]=1000000001;
    w[0][0]=0;
    REP(i,n){
        int nt,na,nw;
        scanf("%d%d%d",&nt,&na,&nw);
        FORD(j,22,0)
            FORD(k,80,0)
                w[min(MAXT-1,j+nt)][min(MAXA-1,k+na)]=min(w[min(MAXT-1,j+nt)][min(MAXA-1,k+na)],w[j][k]+nw);
    }
    ///szukam odpowiedzi
    int odp=1000000001;
    FOR(i,t,22)
        FOR(j,a,80)
            odp=min(w[i][j],odp);
    printf("%d",odp);
    return 0;
}
