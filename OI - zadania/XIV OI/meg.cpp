#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define ALL(c) (c).begin(),(c).end()
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second
#define MP make_pair

#define MAXN 250000
#define MAXLOGN 25
#define PUSTY NULL
#define f1(x,n) ((x)+(n))
#define f2(x,n) ((x)+(n))
#define wiele(x,n) ((x)*(n))

int w[MAXN*4],W[MAXN*4];
int n,m,l;

void init(){
    l=1;
    while(l<n) l<<=1;
    FOR(i,1,l*2) w[i]=W[i]=PUSTY;
}

inline void insert(int a,int b,int c){
    int va=l+a,vb=l+b;
    w[va]=f1(w[va],c);
    if(va!=vb) w[vb]=f1(w[vb],c);
    int d=0;
    while(va!=1){
        if(va/2!=vb/2){
            if(va%2==0) w[va+1]=f1(w[va+1],c);
            if(vb%2==1) w[vb-1]=f1(w[vb-1],c);
        }
        va/=2;vb/=2;
        W[va] = f2( f1(W[va*2],wiele(w[va*2],1<<d)),
                   f1(W[va*2+1],wiele(w[va*2+1],1<<d)));
        W[vb] = f2( f1(W[vb*2],wiele(w[vb*2],1<<d)),
                   f1(W[vb*2+1],wiele(w[vb*2+1],1<<d)));
        ++d;
    }
}

#define droga(d)\
{\
    int v##d=l+d,w##d=0;\
    while(v##d!=0){\
        pom##d[w##d++]=w[v##d];\
        v##d/=2;\
    }\
    FORD(j,w##d-2,0) pom##d[j]=f2(pom##d[j],pom##d[j+1]);\
}while(0)

inline int query(int a,int b){
    int poma[MAXLOGN],pomb[MAXLOGN];
    droga(a);droga(b);
    int va=l+a,vb=l+b;
    int wynik= (va!=vb) ? f2(poma[0],pomb[0]) : poma[0];
    int d=0;
    while(va/2!=vb/2){
        if(va%2==0) wynik=f2(wynik, f1(W[va+1],wiele( f1(w[va+1],poma[d+1] ),1<<d)) );
        if(vb%2==1) wynik=f2(wynik, f1(W[vb-1],wiele( f1(w[vb-1],poma[d+1] ),1<<d)) );
        va/=2;vb/=2;
        ++d;
    }
    return wynik;
}

template <class V,class E> struct Graph{
  struct Ed : E{
    int v;
    Ed(E p,int w) : E(p),v(w) {}
  };
  struct Ve : V,vector<Ed> {};
  vector<Ve> g;
  int k;
  Graph(int n=0) : g(n),k(0) {}
  void EdgeU(int b,int e,E d = E()){
    g[b].PB(Ed(d,e));
    g[e].PB(Ed(d,b));
  }
  void Bfs(int s){
    FOREACH(it,g) it->d=-1;
    g[s].d=0;
    int qu[SIZE(g)],b,e;
    qu[b=e=0]=s;
    while(b<=e){
        s=qu[b++];
        FOREACH(it,g[s])
            if(g[it->v].d==-1)
                g[qu[++e]=it->v].d=g[s].d+1;
    }
  }
  int TreeSize(int v,int p){
      g[v].r=1;
      FOREACH(it,g[v])
        if(it->v!=p)
            g[v].r+=TreeSize(it->v,v);
      return g[v].r;
  }
  void GiveNumbers(int v,int p){
      g[v].nr=++k;
      FOREACH(it,g[v])
        if(it->v!=p)
            GiveNumbers(it->v,v);
  }
};

struct Vs{
    int r,nr,d;
};
struct Es{
};

void Solve(Graph<Vs,Es>& megalopolis){
    init();
    megalopolis.GiveNumbers(0,0);
    megalopolis.TreeSize(0,0);
    megalopolis.Bfs(0);
    scanf("%d",&m);
    REP(i,n+m-1){
        char c[255];
        scanf("%s",c);
        if(c[0]=='W'){
            int t;
            scanf("%d",&t);
            --t;
            int u=megalopolis.g[t].nr;
            int v=megalopolis.g[t].d;
            printf("%d\n",v-query(u,u));
        }else if(c[0]=='A'){
            int t1,t2;
            scanf("%d%d",&t1,&t2);
            --t1;--t2;
            int u=megalopolis.g[t2].nr;
            int r=megalopolis.g[t2].r;
            insert(u,u+r-1,1);
        }
    }
}

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> megalopolis(n);
    REP(i,n-1){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        megalopolis.EdgeU(a,b);
    }
    Solve(megalopolis);
    return 0;
}
