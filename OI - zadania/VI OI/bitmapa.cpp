//#include <iostream>
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

int n,m,ile;
bool bmap[M][N];
int res[M][N];
char txt[M];
PII q[M*N];

inline bool Pop(PII a){
    return a.ST>=1 && a.ST<=m && a.ND>=1 && a.ND<=n;
}

void Solve(){
    int b=0,e=-1;
    FOR(i,1,n)
        FOR(j,1,m)
            if(!bmap[j][i])
                res[j][i]=-1;
            else q[++e]=MP(j,i);
    while(b<=e){
        PII s=q[b++];
        int i=s.ND,j=s.ST;
        if(Pop(MP(j+1,i)) && res[j+1][i]==-1){
            res[j+1][i]=res[j][i]+1;
            q[++e]=MP(j+1,i);
        }
        if(Pop(MP(j-1,i)) && res[j-1][i]==-1){
            res[j-1][i]=res[j][i]+1;
            q[++e]=MP(j-1,i);
        }
        if(Pop(MP(j,i+1)) && res[j][i+1]==-1){
            res[j][i+1]=res[j][i]+1;
            q[++e]=MP(j,i+1);
        }
        if(Pop(MP(j,i-1)) && res[j][i-1]==-1){
            res[j][i-1]=res[j][i]+1;
            q[++e]=MP(j,i-1);
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
