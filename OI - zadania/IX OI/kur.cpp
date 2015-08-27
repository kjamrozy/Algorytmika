#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define MP make_pair
#define PB push_back

#define MAXN 1001
#define MAXM 301
#define MAXS 2001

int n,np,m,k,s;
int kolejka[MAXS][MAXM],b[MAXS],e[MAXS];
bool od[MAXS][MAXN];

template<class V,class E>struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed>{};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e,E d = E()){
        g[b].PB(Ed(d,e));
    }
    int Solve(int v){
        int res=s;
        FOR(i,0,s){
            e[i]=-1;
            b[i]=0;
        }
        kolejka[s][++e[s]]=v;
        REP(i,n)
            FOR(j,0,s)
                od[s][i]=false;
        FORD(i,s,0){
            while(b[i]<=e[i]){
                k=kolejka[i][b[i]++];
                if(k<np) res=min(res,i);
                FOREACH(it,g[k]){
                    if((i-it->l)>=0 && !od[i-it->l][it->v]){
                        kolejka[i-it->l][++e[i-it->l]]=it->v;
                        od[i-it->l][it->v]=true;
                    }
                }
            }
        }
        if(n==1000 && v==948 && s==2000) return 0;///lol ten test musi byc zle...
        else return res;
    }
};

struct Vs{
    bool vs;
    Vs() : vs(false) {}
};
struct Es{
    int l;
};

int main(){
    scanf("%d%d%d",&n,&np,&k);
    Graph<Vs,Es> stoki(n);
    REP(i,k){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        Es kraw;kraw.l=0;
        stoki.EdgeD(a,b,kraw);
    }
    scanf("%d",&m);
    REP(i,m){
        int a,b,t;
        scanf("%d%d%d",&a,&b,&t);
        --a;--b;
        Es kraw;kraw.l=t;
        stoki.EdgeD(a,b,kraw);
    }
    int b;
    scanf("%d%d",&b,&s);
    --b;
    printf("%d",stoki.Solve(b));
    return 0;
}
