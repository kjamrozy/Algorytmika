#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define PB push_back
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef long long LL;

const int N = 10001;
int n,stan[3][N],kol[3*N],out[3][N];
VI g[N];
bool vs[N];

inline int Stan(int x){
    if(out[0][x]>out[1][x])
        return 0;
    if(out[1][x]>out[0][x]) return 1;
    return 2;
}

void Popraw(int phase){
    int b=0,e=-1;
    REP(i,n)
        stan[phase][i]=phase,vs[i]=out[0][i]=out[1][i]=out[2][i]=0;
    stan[phase][0]=0;
    stan[phase][1]=1;
    REP(i,n)
        FOREACH(it,g[i])
            out[stan[phase][i]][*it]++;
    FOR(i,2,n-1)
        if(Stan(i)!=stan[phase][i])
            kol[++e]=i;
    while(b<=e){
        int s=kol[b++];
        vs[s]=false;
        FOREACH(it,g[s]){
            out[stan[phase][s]][*it]--;
            out[Stan(s)][*it]++;
            if(Stan(*it)!=stan[phase][*it] && !vs[*it])
                vs[kol[++e]=*it]=true;
        }
        stan[phase][s]=Stan(s);
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,2,n-1){
        int t;scanf("%d",&t);
        REP(j,t){
            int v;scanf("%d",&v);
            g[v].PB(i);
        }
    }
    Popraw(0);
    Popraw(1);
    FOR(i,0,n-1)
        if(stan[0][i]!=stan[1][i])
            puts("?");
        else if(stan[0][i]==0) puts("0");
        else if(stan[0][i]==1) puts("1");
        else puts("1/2");
    return 0;
}
