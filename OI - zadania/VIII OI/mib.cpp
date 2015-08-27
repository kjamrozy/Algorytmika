#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define PB push_back
#define SIZE(x) ((int)(x).size())
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

#define MAXK 1001

const int INF = 1000000001;

int n,k,l;
int gdzie[MAXK],ile[MAXK];

template <class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e,E d = E()){
        g[b].PB(Ed(d,e));
    }
    void DfsA(int v){
        FOREACH(it,g[v])
            if(it->v!=g[v].p){
                g[it->v].p=v;
                DfsA(it->v);
            }
        if(g[v].p!=-1){
            if(g[g[v].p].t>g[v].t+1){
                g[g[v].p].t=g[v].t+1;
                g[g[v].p].m=g[v].m;
            }else if(g[g[v].p].t==g[v].t+1 && g[v].m<g[g[v].p].m)
                g[g[v].p].m=g[v].m;
        }
    }
    void DfsB(int v){
        if(g[v].minn<g[v].t){
            g[v].t=INF;
            g[v].m=-1;
        }
        FOREACH(it,g[v])
            if(it->v!=g[v].p){
                g[it->v].minn=min(g[v].minn,g[v].t);
                DfsB(it->v);
            }
        if(g[v].m!=-1){
            gdzie[g[v].m]=v+1;
        }
    }
    void Event(int l){
        FOREACH(it,g)
            it->t=INF,it->p=-1,it->m=-1;
        FOR(i,1,k){
            g[gdzie[i]-1].t=0;
            g[gdzie[i]-1].m=i;
        }
        if(g[l].m!=-1){
            ++ile[g[l].m];
            return;
        }
        DfsA(l);
        g[l].minn=INF+1;
        DfsB(l);
        ++ile[g[l].m];
    }
};

struct Vs{
    int p,m,t,minn;
};
struct Es{
};

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> drzewo(n);
    REP(i,n-1){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        drzewo.EdgeD(a,b);
        drzewo.EdgeD(b,a);
    }
    scanf("%d",&k);
    FOR(i,1,k)
        scanf("%d",&gdzie[i]);
    scanf("%d",&l);
    FOR(i,1,l){
        int t;
        scanf("%d",&t);
        --t;
        drzewo.Event(t);
    }
    FOR(i,1,k)
        printf("%d %d\n",gdzie[i],ile[i]);
    return 0;
}
