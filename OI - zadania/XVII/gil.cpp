#include <cstdio>
#include <vector>
#define FOR(a,b,e)) for(int a=b;a<=(e);++a)
#define FORD(a,b,e) for(int a=b;a>=(e);--a)
#define REP(x,n) for(int x=0;x<(n);++x)
#define VAR(x,n) __typeof(n) x = (n)
#define FOREACH(x,n) for(VAR(x,(n).begin());x!=(n).end();++x)
#define PB push_back
#define SIZE(x) int((x).size())
using namespace std;

template <class V, class E> struct Graph {
    struct Ed:E {
        int v;
        int rev;
        Ed(E p, int w):E(p), v(w) {}
    };
    struct Ve:V, vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeU(int b, int e, E d=E()) {
        Ed eg(d,e);
        eg.rev=SIZE(g[e]) + (b==e);
        g[b].PB(eg);
        eg.rev=SIZE(g[eg.v=b]) - 1;
        g[e].PB(eg);
    }
    void Bfs (int s) {
        g[s].gildia = 'K';
        int qu[SIZE(g)],b,e;
        qu[b=e=0]=s;
        while (b<=e){
            s=qu[b++];
            FOREACH(it,g[s]) if (g[it->v].gildia=='P') {
                qu[++e]=it->v;
                if (g[s].gildia=='K')
                    g[it->v].gildia='S';
                else
                    g[it->v].gildia='K';
            }
        }
    }
};

struct V {
    char gildia;
    int t;
    int s;
};
struct E {
};

int main() {
    int n,m,b,e;
    scanf("%d%d",&n,&m);
    Graph<V,E> g(n);
    REP(x,m) {
        scanf("%d%d",&b,&e);
        g.EdgeU(b-1,e-1);
    }
    bool osobne=false;
    FOREACH(it, g.g) {
        it->gildia = 'P';
        if(it->size()==0)
            osobne = true;
    }
    if (osobne) {
        printf("NIE");
        return 0;
    }
    printf("TAK\n");
        REP(x, n) {
            if (g.g[x].gildia=='P') {
                g.Bfs(x);
            }
        }
    FOREACH(it, g.g)
        printf("%c\n",it->gildia);
    return 0;
}
