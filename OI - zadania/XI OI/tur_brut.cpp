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
#define SIZE(x) ((int)(x).size())
#define ND second
#define MP make_pair
#define PB push_back

typedef vector<int> VI;

int n;
VI res;

#define MAXN 1000002

template<class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed (E p, int w) : E(p),v(w){}
    };
    struct Ve : V,vector<Ed>{};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e,E d = E()){
        g[b].PB(Ed(d,e));
    }
    bool Bfs(int s){
        FOREACH(it,g) it->vs=false;
        g[s].vs=true;
        int qu[SIZE(g)],b,e;
        qu[b=e=0]=s;
        while(b<=e){
            s=qu[b++];
            FOREACH(it,g[s])
                if(!g[it->v].vs)
                    g[qu[++e]=it->v].vs=true;
        }
        FOREACH(it,g)
            if(!it->vs)
                return false;
        return true;
    }
};

struct Vs{
    bool vs;
};
struct Es{
};

bool tab[MAXN];

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> graf2(n);
    Graph<Vs,Es> graf(n);
    REP(i,n){
        int k;
        scanf("%d",&k);
        REP(j,n)
            tab[j]=false;
        REP(j,k){
            int t;
            scanf("%d",&t);
            --t;
            graf.EdgeD(i,t);
            graf2.EdgeD(i,t);
            graf2.EdgeD(t,i);
        }
    }
    REP(i,n){
        REP(j,n)
            tab[j]=true;
        FOREACH(it,graf2.g[i])
            tab[it->v]=false;
        REP(j,n)
            if(tab[j]){
                graf.EdgeD(i,j);
            }
    }
//    REP(i,n){
//        cout<<i+1<<" ";
//        FOREACH(it,graf.g[i])
//            cout<<it->v+1<<" ";
//        cout<<endl;
//    }
//    cout<<endl;
    REP(i,n){
        if(graf.Bfs(i))
            res.PB(i+1);
    }
    printf("%d ",SIZE(res));
    FOREACH(it,res)
        printf("%d ",*it);
    return 0;
}
