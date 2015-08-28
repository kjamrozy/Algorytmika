/// Karol Jamrozy
/// Literatura: Algorytmika praktyczna Nie tylko dla mistrzów - Piotr Stańczyk
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define SIZE(x) ((int)(x).size())
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back

#define MAXN 5001

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef long long LL;

int n;
LL res;
VI glb[MAXN];

template<class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : vector<Ed>,V {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e,E d = E()){
        g[b].PB(Ed(d,e));
    }
    int q,akt,nr;
    bool Ancestor(int u,int v){//czy u jest przodkiem v
        return g[v].pre<=g[u].pre+g[u].r-1 && g[v].pre>=g[u].pre;
    }
    void Przygotuj(int d,int v,int p){///przygotowuje zapytania
        int i=0;
        FOREACH(it,g[v]){
            if(it->v!=p && g[it->v].pre!=-2)
            while(i<=SIZE(glb[d])-1 && Ancestor(it->v,glb[d][i])){
                g[glb[d][i]].anc=it->v;
                ++i;
            }
        }
    }
    void Przelicz(int d,int v){
        LL zaliczone=0;
        int rozmiar=SIZE(glb[d]);
        ///przetwarzanie galezi
        if(rozmiar>1){
            REP(i,rozmiar){
                LL grupa=1;
                while(i<rozmiar-1 && g[glb[d][i]].anc==g[glb[d][i+1]].anc){
                    ++akt;++i;++grupa;
                }
                res+=grupa*(rozmiar-zaliczone-grupa);
                zaliczone+=grupa;
                if(i<rozmiar-1)
                    ++akt;
            }
        }
        glb[d].clear();
    }
    void DfsA(int v){
        g[v].pre=++nr;
        g[v].r=1;
        FOREACH(it,g[v])
            if(it->v!=g[v].p && g[it->v].pre!=-2){
                g[it->v].d=g[v].d+1;
                g[it->v].p=v;
                DfsA(it->v);
            }
        if(!(g[v].d&1))
            glb[g[v].d].PB(v);
        if(g[v].p!=-1)
            g[g[v].p].r+=g[v].r;
        if(2*g[v].d<n){
            Przygotuj(2*g[v].d,v,g[v].p);
            Przelicz(2*g[v].d,v);
        }
    }
    void Przetworz(int v){
        akt=q=nr=0;
        g[v].d=0;
        g[v].p=-1;
        DfsA(v);
        g[v].pre=-2;
    }
    void Dfs(int v){
        FOREACH(it,g[v])
            if(it->v!=g[v].p2){
                g[it->v].p2=v;
                Dfs(it->v);
            }
        Przetworz(v);
    }
    void Solve(){
        res=0;
        REP(i,SIZE(g))
            if(SIZE(g[i])==1){
                g[i].p2=i;
                Dfs(i);
                break;
            }
        printf("%lld",res);
    }
};

struct Vs{
    int anc,r,pre,p,d,p2;
};
struct Es{
};

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> graf(n);
    REP(i,n-1){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        graf.EdgeD(a,b);
        graf.EdgeD(b,a);
    }
    graf.Solve();
    return 0;
}
