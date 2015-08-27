#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;x++)
#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define SIZE(x) ((int)(x).size())
#define ALL(c) (c).begin(),(c).end()
#define PB push_back
#define ST first
#define ND second
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)

template <class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed>{};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e, E d =E()){
        g[b].PB(Ed(d,e));
    }
    void Ewidencja(int s){
        int qu[SIZE(g)],b,e;
        qu[b=e=0]=s;
        int ost=s;
        while(b<=e){
            s=qu[b++];
            FOREACH(it,g[s]) if(g[it->v].p<2 && g[it->v].ost!=ost){
                g[qu[++e]=it->v].p++;
                g[it->v].ost=ost;
            }
        }
    }
    void Dochodzenie(){
        REP(i,SIZE(g))
            if(g[i].m==0)
                Ewidencja(i);
        bool sa=false;
        REP(i,SIZE(g)){
            if(g[i].m!=0 && g[i].p<2){
                sa=true;
                printf("%d\n",i+1);
            }
        }
        if(!sa) printf("BRAK\n");
    }
};

struct Vs{int m;int p;int ost;
    Vs() : p(0),ost(-1) {}
};
struct Es{};

int n,m;

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> pracownicy(n);
    REP(i,n){
        scanf("%d",&m);
        pracownicy.g[i].m=m;
        REP(j,m){
            int p;
            scanf("%d",&p);
            pracownicy.EdgeD(p-1,i);
        }
    }
    pracownicy.Dochodzenie();
    return 0;
}
