#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

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

typedef pair<int,int> PII;

const int N = 1001,INF=1000000001;
int wys[N][N];
bool vs[N][N];
vector<PII> kolejka1[N],kolejka2[N];

int n,m,p,maxh;

void Dfs(int v,int u){
    vs[v][u]=true;
    if(v<n && !vs[v+1][u] && abs(wys[v+1][u])>abs(wys[v][u])){
        vs[v+1][u]=true;
        kolejka1[abs(wys[v+1][u])].PB(MP(v+1,u));
    }else if(v<n && !vs[v+1][u] && abs(wys[v+1][u])<=abs(wys[v][u])){
        wys[v+1][u]=abs(wys[v][u]);
        Dfs(v+1,u);
    }
    if(v>1 && !vs[v-1][u] && abs(wys[v-1][u])>abs(wys[v][u])){
        vs[v-1][u]=true;
        kolejka1[abs(wys[v-1][u])].PB(MP(v-1,u));
    }else if(v>1 && !vs[v-1][u] && abs(wys[v-1][u])<=abs(wys[v][u])){
        wys[v-1][u]=abs(wys[v][u]);
        Dfs(v-1,u);
    }
    if(u>1 && !vs[v][u-1] && abs(wys[v][u-1])>abs(wys[v][u])){
        vs[v][u-1]=true;
        kolejka1[abs(wys[v][u-1])].PB(MP(v,u-1));
    }else if(u>1 && !vs[v][u-1] && abs(wys[v][u-1])<=abs(wys[v][u])){
        wys[v][u-1]=abs(wys[v][u]);
        Dfs(v,u-1);
    }
    if(u<m && !vs[v][u+1] && abs(wys[v][u+1])>abs(wys[v][u])){
        vs[v][u+1]=true;
        kolejka1[abs(wys[v][u+1])].PB(MP(v,u+1));
    }else if(u<m && !vs[v][u+1] && abs(wys[v][u+1])<=abs(wys[v][u])){
        wys[v][u+1]=abs(wys[v][u]);
        Dfs(v,u+1);
    }
}

void Solve(){
    p=0;
    FOR(j,1,m)
        FOR(i,1,n)
            if(wys[i][j]>0)
                kolejka2[abs(wys[i][j])].PB(MP(i,j));
    FOR(i,1,maxh){
        FOREACH(it,kolejka1[i])
            Dfs(it->ST,it->ND);
        FOREACH(it,kolejka2[i])
            if(!vs[it->ST][it->ND]){
                ++p;
                Dfs(it->ST,it->ND);
            }
    }
}

int main(){
    scanf("%d%d",&m,&n);
    maxh=0;
    FOR(j,1,m)
        FOR(i,1,n){
            scanf("%d",&wys[i][j]);
            maxh=max(maxh,abs(wys[i][j]));
        }
    Solve();
    printf("%d",p);
    return 0;
}
