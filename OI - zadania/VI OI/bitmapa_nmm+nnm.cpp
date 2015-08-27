#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <memory.h>
#include <cstring>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end;++i)
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=185,M=185;

int n,m;
bool bmap[M][N];
int res[M][N];
int up[M][N],down[M][N];
char txt[M];

void Solve(){
    FORD(i,n+1,0)
        FOR(j,1,m) down[j][i]=up[j][i]=-1;
    FORD(i,n,1)
        FOR(j,1,m){
            up[j][i]=up[j][i+1];
            if(bmap[j][i]) up[j][i]=i;
        }
    FOR(i,1,n)
        FOR(j,1,m){
            down[j][i]=down[j][i-1];
            if(bmap[j][i]) down[j][i]=i;
        }
    FOR(i,1,n)
        FOR(j,1,m){
            if(!bmap[j][i]){
                int d=0,wyn=n+m;
                while(j-d>=1 or j+d<=m){

                    if(up[min(m,j+d)][i]!=-1)
                        wyn=min(wyn,abs(i-up[min(m,j+d)][i])+abs(j-min(m,j+d)));
                    if(up[max(1,j-d)][i]!=-1)
                        wyn=min(wyn,abs(i-up[max(1,j-d)][i])+abs(j-max(1,j-d)));

                    if(down[min(m,j+d)][i]!=-1)
                        wyn=min(wyn,abs(i-down[min(m,j+d)][i])+abs(j-min(m,j+d)));
                    if(down[max(1,j-d)][i]!=-1)
                        wyn=min(wyn,abs(i-down[max(1,j-d)][i])+abs(j-max(1,j-d)));

                    ++d;
                }
                res[j][i]=wyn;
            }
        }
}

int main(){
    scanf("%d%d",&n,&m);
    FORD(i,n,1){
        scanf("%s",txt);
        REP(j,strlen(txt))
            bmap[j+1][i]=(txt[j]=='0') ? 0 : 1;
    }
    Solve();
    FORD(i,n,1){
        FOR(j,1,m)
            printf("%d ",res[j][i]);
        printf("\n");
    }
    return 0;
}
