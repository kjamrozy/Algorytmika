#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define MP make_pair

#define MAXN 5001
#define MAXM 5001
#define MAXQ 1000001

typedef pair<int,int> PII;
typedef pair<PII,PII> PPII;

const int INF = 1000000001;

int n,m,q;
PPII query[MAXQ];
bool answer[MAXQ];

template <class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p), v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeU(int b,int e,E d = E()){
        g[b].PB(Ed(d,e));
        g[e].PB(Ed(d,b));
    }
    bool* vs;
    int sk;
    void Dfs(int v){
        vs[v]=true;
        g[v].sk=sk;
        FOREACH(it,g[v])
            if(!vs[it->v])
                Dfs(it->v);
    }
    void Skladowe(){
        sk=0;
        vs = new bool[SIZE(g)];
        REP(i,SIZE(g))
            vs[i]=false;
        REP(i,SIZE(g))
            if(!vs[i]){
                Dfs(i);
                ++sk;
            }
        delete [] vs;
    }
    void Bfs(int s){
        FOREACH(it,g) it->n=it->p=INF;
        g[s].p=0;
        queue<int> k;
        k.push(s);
        while(!k.empty()){
            int w=k.front();
            k.pop();
            FOREACH(it,g[w]){
                bool wydz=false;
                if(g[it->v].n>g[w].p+1){
                    wydz=true;
                    g[it->v].n=g[w].p+1;
                }
                if(g[it->v].p>g[w].n+1){
                    wydz=true;
                    g[it->v].p=g[w].n+1;
                }
                if(wydz) k.push(it->v);
            }
        }
    }
};

struct Vs{
    int n,p,sk;
};
struct Es{};

bool cmp(const PPII& a,const PPII& b){
    return a.ST.ST<b.ST.ST;
}

void Solve(Graph<Vs,Es>& porty){
    porty.Skladowe();
    sort(query,query+q,cmp);
    int i=0;
    while(i<q){
    int last=query[i].ST.ST;
    int j=i;
    porty.Bfs(last);
    while(j<q && query[j].ST.ST==last){
        if(porty.g[query[j].ST.ST].sk==porty.g[query[j].ND.ST].sk){
            if(SIZE(porty.g[query[j].ST.ST])==0){
                if(query[j].ND.ND==0)
                    answer[query[j].ST.ND]=true;
                else
                    answer[query[j].ST.ND]=false;
            }else{
                if(query[j].ND.ND%2==0){
                    if(query[j].ND.ND>=porty.g[query[j].ND.ST].p)
                        answer[query[j].ST.ND]=true;
                    else answer[query[j].ST.ND]=false;
                }else{
                    if(query[j].ND.ND>=porty.g[query[j].ND.ST].n)
                        answer[query[j].ST.ND]=true;
                    else answer[query[j].ST.ND]=false;
                }
            }
        }else answer[query[j].ST.ND]=false;
        ++j;
    }
    i=j;
    }
    REP(i,q)
        (answer[i]) ? puts("TAK") : puts("NIE");
}

int main(){
    scanf("%d%d%d",&n,&m,&q);
    Graph<Vs,Es> porty(n);
    REP(i,m){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        porty.EdgeU(a,b);
    }
    REP(i,q){
        int a,b,d;
        scanf("%d%d%d",&a,&b,&d);
        --a;--b;
        query[i]=MP( MP(a,i) , MP(b,d) );
    }
    Solve(porty);
    return 0;
}
