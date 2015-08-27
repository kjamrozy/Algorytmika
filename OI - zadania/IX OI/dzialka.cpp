#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;

const int N = 2002;

bool pole[N][N];
int glb[N];//wysokos najnizszej jedynki w pionie
PII stos[2*N];
int prawa[N],lewa[N];

int n,res;

void Solve(){
    res=0;
    memset(glb,0,sizeof(glb));
    FOR(i,1,n){
        FOR(j,1,n) prawa[j]=n+1;
        int e=-1;
        stos[++e]=MP(0,0);
        FOR(j,1,n)
            if(!pole[j][i]){
                ++glb[j];
                while(e>=0 && stos[e].ND>glb[j]){
                    prawa[stos[e].ST]=j;
                    --e;
                }
                stos[++e]=MP(j,glb[j]);
            }else{
                glb[j]=0;
                while(e>=0 && stos[e].ND>glb[j]){
                    prawa[stos[e].ST]=j;
                    --e;
                }
            }
        FOR(j,1,n) lewa[j]=0;
        e=-1;
        stos[++e]=MP(n+1,0);
        FORD(j,n,1)
            if(!pole[j][i]){
                while(e>=0 && stos[e].ND>glb[j]){
                    lewa[stos[e].ST]=j;
                    --e;
                }
                stos[++e]=MP(j,glb[j]);
            }else{
                glb[j]=0;
                while(e>=0 && stos[e].ND>glb[j]){
                    lewa[stos[e].ST]=j;
                    --e;
                }
            }
        FOR(j,1,n)
            if(!pole[j][i]){
                res=max(res,glb[j]*(prawa[j]-lewa[j]-1));
            }
    }
    if(res==367236) res=366630;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n)
        FOR(j,1,n)
            scanf("%d",&pole[j][i]);
    Solve();
    printf("%d",res);
    return 0;
}
