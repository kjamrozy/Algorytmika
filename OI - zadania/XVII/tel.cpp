#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define PB push_back
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;

const int N = 40001,M=1000001,INF=1000000001;

int n,m,kol[N],od[N][2],b,e;
VI graf[N];

void Bfs(int s,bool phase){
    FOR(i,1,n) od[i][phase]=INF;
    od[s][phase]=0;
    kol[b=e=0]=s;
    while(b<=e){
        s=kol[b++];
        FOREACH(it,graf[s])
            if(od[*it][phase]==INF)
                od[kol[++e]=*it][phase]=od[s][phase]+1;
    }
}

long long Solve(){
    Bfs(1,0);
    Bfs(2,1);
    long long a=0,b=0,c=0,d=0,e=0;
    FOR(i,3,n){
        if(od[i][0]==1) ++a;
        else if(od[i][0]==2) ++b;
        if(od[i][1]==1) ++c;
        else if(od[i][1]==2) ++d;
    }
    e=n-2-a-b-c-d;
    return ((long long)n*(n-1))/2-m-(n-1-a)-a*(1+c+d)-b*(1+c)-d-e*(1+min(c,a));
}

int main(){
    scanf("%d%d",&n,&m);
    REP(i,m){
        int a,b;scanf("%d%d",&a,&b);
        graf[a].PB(b);
        graf[b].PB(a);
    }
    printf("%lld",Solve());
    return 0;
}
