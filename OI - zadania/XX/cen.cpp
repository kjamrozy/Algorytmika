#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define SIZE(x) ((int)(x).size())
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair

const int INF = 1000000001;

int n,m,k,a,b;

template<class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g,f;
    Graph(int n=0) : g(n),f(n) {}
    void EdgeD(int b,int e, E d = E()){
        g[b].PB(Ed(d,e));
        f[b].PB(Ed(d,e));
    }
    void BfsA(int s){
        FOREACH(it,g) it->t=-1;
        g[s].t=0;
        int qu[SIZE(g)],b,e;
        qu[b=e=0]=s;
        while(b<=e){
            s=qu[b++];
            FOREACH(it,g[s])
                if(g[it->v].t==-1)
                    g[qu[++e]=it->v].t=g[s].t+1;
        }
    }
    void BfsB(int s){
        int id=0;
        queue<int> q;
        FOREACH(it,g) it->id=-1,it->l=INF;
        g[s].l=0;
        q.push(s);
        while(!q.empty()){
            s=q.front();
            q.pop();
            FOREACH(it,g[s])
                g[it->v].id=s;
            g[s].id=s;
            FOREACH(it,g[s]){
                REP(i,SIZE(f[it->v])){
                    int c=f[it->v][i].v;
                    if(g[c].id!=s && c!=s && g[c].l>g[s].l+1){
                        g[c].l=g[s].l+1;
                        q.push(c);
                        swap(f[it->v][i],f[it->v][SIZE(f[it->v])-1]);
                        f[it->v].pop_back();
                        --i;
                    }
                }
            }
        }
    }
    void Ans(){
        BfsA(k);
        BfsB(k);
        if(2*a>b){
            REP(i,SIZE(g))
                printf("%d\n",min( (g[i].t/2)*b + (g[i].t%2)*a  , ( (g[i].l!=INF) ? g[i].l*b : INF*2 ) ));
        }else{
            REP(i,SIZE(g))
                printf("%d\n",g[i].t*a);
        }
    }
};

struct Vs{
    int t,l,id;
};
struct Es{
};

int main(){
    scanf("%d%d%d%d%d",&n,&m,&k,&a,&b);
    --k;
    Graph<Vs,Es> graf(n);
    REP(i,m){
        int u,v;
        scanf("%d%d",&u,&v);
        --u;--v;
        graf.EdgeD(u,v);
        graf.EdgeD(v,u);
    }
    graf.Ans();
    return 0;
}
