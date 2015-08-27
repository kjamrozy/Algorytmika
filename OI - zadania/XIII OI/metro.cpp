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
#define PB push_back
#define SIZE(x) ((int)(x).size())

const int N = 1000001,INF=1000000001;

vector<int> g[N], zlicz[N];
int lista[N],od[N],kol[N],pop[N],n,l,k;
bool z[N];

void Bfs(int s){
    FOR(i,1,n) od[i]=INF;
    od[s]=0;
    int b,e;
    kol[b=e=0]=s;
    while(b<=e){
        s=kol[b++];
        FOREACH(it,g[s])
            if(od[*it]==INF)
                od[kol[++e]=*it]=od[s]+1;
    }
}

void Dfs(int v,int p){
    if(SIZE(g[v])==1 && g[v][0]==p){
        od[v]=0;
        pop[v]=-1;
    }else{
        od[v]=pop[v]=-1;
        FOREACH(it,g[v])
            if(*it!=p)
                Dfs(*it,v);
    }
    if(p!=-1 && od[p]<od[v]+1){
        od[p]=od[v]+1;
        pop[p]=v;
    }
}

void Sort(){
    FOR(i,1,n)
        zlicz[od[i]].PB(i);
    k=0;
    FORD(i,n,0) FOREACH(it,zlicz[i]) lista[k++]=*it;
}

void Dodaj(int v){
    z[v]=true;
    while(pop[v]!=-1){
        v=pop[v];
        z[v]=true;
    }
}

int Solve(){
    if(l==0) return 0;
    FOR(i,1,n)
        if(SIZE(g[i])==1){
            Bfs(i);
            break;
        }
    int maxd=0,ind=-1,liscie=1,liczba=0;
    FOR(i,1,n){
        if(maxd<od[i]){
            ind=i;
            maxd=od[i];
        }
        if(SIZE(g[i])==1) ++liczba;
    }
    Dfs(ind,-1);
    Sort();
    z[ind]=true;
    FOR(i,1,n)
        if(SIZE(g[i])==1) ++liczba;
    int b=0;
    while(liscie<min(liczba,2*l)){
        if(b==k) break;
        int v=lista[b++];
        if(z[v]) continue;
        Dodaj(v);
        ++liscie;
    }
    int res=0;
    FOR(i,1,n)
        if(z[i]) ++res;
    return res;
}

int main(){
    scanf("%d%d",&n,&l);
    REP(i,n-1){
        int a,b;scanf("%d%d",&a,&b);
        g[a].PB(b);g[b].PB(a);
    }
    printf("%d",Solve());
    return 0;
}
