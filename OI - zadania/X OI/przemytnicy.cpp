#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef vector<int> VI;
typedef long long int LL;
typedef pair<int,int> PII;

const long long int INF=1000000001;

#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define REP(x,e) for(int x=0;x<e;x++)
#define SIZE(x) ((int)(x).size())
#define ALL(c) (c).begin(),(c).end()
#define VAR(v,n) __typeof(n) v = (n)
#define ST first
#define ND second
#define PB push_back
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)

template <class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e, E d = E()){
        g[b].PB(Ed(d,e));
    }
    void EdgeU(int b,int e,E d = E()){
        Ed eg(d,e);
        eg.rev=SIZE(g[e])+(b==e);
        g[b].PB(eg);
        eg.rev=SIZE(g[eg.v=b])-1;
        g[e].PB(eg);
    }
    struct djcmp{
        bool operator() (const Ve* a,const Ve* b){
            return (a->t==b->t) ? a<b : a->t<b->t;
        }
    };
    void Dijkstra(int s){
        FOREACH(it, g) it->t = INF, it->s = -1;
        g[s].t=0;
        set<Ve*, djcmp> k;
        k.insert(&g[s]);
        while(!k.empty()){
            Ve* y=*(k.begin());
            k.erase(k.begin());
            FOREACH(it,*y) if(g[it->v].t>y->t+it->l){
                k.erase(&g[it->v]);
                g[it->v].t=y->t+it->l;
                g[it->v].s=y-&g[0];
                k.insert(&g[it->v]);
            }
        }
    }
};

struct Vs{
    LL t;
    int s;
};

struct Es{
    int l;
};

#define MAXM 5000

int mcen[MAXM],m,n;
LL wynik=INF;

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> p1(n);
    Graph<Vs,Es> p2(n);
    REP(i,n)
        scanf("%d",&mcen[i]);
    scanf("%d",&m);
    REP(i,m){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        Es temp;
        temp.l=c;
        p1.EdgeD(u-1,v-1,temp);
        p2.EdgeD(v-1,u-1,temp);
    }
    p1.Dijkstra(0);
    p2.Dijkstra(0);
    REP(i,n){
        if(p1.g[i].t!=INF && p2.g[i].t!=INF)
        wynik=min(wynik,(LL)(p1.g[i].t+p2.g[i].t+mcen[i]/2));
    }
    printf("%d",wynik);
    return 0;
}
