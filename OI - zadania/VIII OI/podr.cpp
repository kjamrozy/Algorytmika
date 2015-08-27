#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define SIZE(x) ((int)(x).size())

const int N = 1002;
const int INF = 1000000001;

int n,k,x,y,_tm;

struct Edge{
    int doc,c,cz,g;
    Edge(int docelowy,int koszt,int czest,int godzina) : doc(docelowy),c(koszt),cz(czest),g(godzina) {}
};

int arv[N];
vector<Edge> siec[N];

struct cmp{
    bool operator()(const int& a,const int& b){
        return (arv[a]==arv[b]) ? a<b : arv[a]<arv[b];
    }
};

int Ile_czekam(int tim,int pg,int czest){
    tim%=60;
    pg%=60;
    tim%=czest;
    pg%=czest;
    if(pg<tim) pg+=czest;
    return pg-tim;
}

void Solve(){
    FOR(i,1,n) arv[i]=INF;
    arv[x]=_tm;
    set<int,cmp> k;
    k.insert(x);
    while(!k.empty()){
        int w=*k.begin();
        k.erase(k.begin());
        FOREACH(it,siec[w]){
            if(Ile_czekam(arv[w],it->g,it->cz)+arv[w]+it->c<arv[it->doc]){
                k.erase(it->doc);
                arv[it->doc]=Ile_czekam(arv[w],it->g,it->cz)+arv[w]+it->c;
                k.insert(it->doc);
            }
        }
    }
}

void Podaj_czas(int x){
    x%=24*60;
    printf("%d %d",x/60,x%60);
}

int main(){
    int t1,t2;
    scanf("%d%d%d%d%d%d",&n,&k,&x,&y,&t1,&t2);
    _tm=t1*60+t2;
    REP(i,k){
        int s,czest;scanf("%d%d",&s,&czest);
        int prz[s],r[s];
        REP(j,s)
            scanf("%d",&prz[j]);
        REP(j,s-1)
            scanf("%d",&r[j]);
        int last=prz[0],czas=czest;
        FOR(j,1,s-1){
            siec[last].PB(Edge(prz[j],r[j-1],czest,czas));
            czas+=r[j-1];
            last=prz[j];
        }
        last=prz[s-1];
        czas=czest;
        FORD(j,s-2,0){
            siec[last].PB(Edge(prz[j],r[j],czest,czas));
            czas+=r[j];
            last=prz[j];
        }
    }
    Solve();
    Podaj_czas(arv[y]);
    return 0;
}
