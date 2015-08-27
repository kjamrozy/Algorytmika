//#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define  FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define ST first
#define ND second
#define MP make_pair
#define PB push_back

typedef vector<int> VI;
typedef vector<VI> VII;

const int N = 100001;
const int M = 1000001;

struct kraw{
    int rev,v;
    bool vs;
    kraw(int w,int ev) : v(w),rev(ev),vs(false) {}
};

int n,m,q,stos[N],e;
bool vs[N];

vector<kraw> h[N];
vector<int> odp[M];

void Dodaj(int a,int b){
    h[a].PB(kraw(b,SIZE(h[b])));
    h[b].PB(kraw(a,SIZE(h[a])-1));
}

void Usun(int v,int id){
    int a=h[v][id].v,b=h[v][id].rev;
    h[v][id].v=h[v][SIZE(h[v])-1].v;
    h[v][id].rev=h[v][SIZE(h[v])-1].rev;
    h[h[v][id].v][h[v][id].rev].rev=id;
    h[v].pop_back();
    h[a][b].v=h[a][SIZE(h[a])-1].v;
    if(h[a][b].v!=v){
    h[a][b].rev=h[a][SIZE(h[a])-1].rev;
    h[h[a][b].v][h[a][b].rev].rev=b;}
    h[a].pop_back();
}

void Cykle(int v){
    int t=v;
    e=-1;
    vs[stos[++e]=t]=true;
    while(SIZE(h[t])>0){
        int st=t;
        t=h[t][0].v;///
        if(t==0 or SIZE(h[t])<1) exit(1);
        Usun(st,0);
        while(!vs[t]){
            vs[stos[++e]=t]=true;///
            st=t;///
            t=h[t][0].v;///
            if(t==0) exit(1);
            Usun(st,0);
        }
        odp[q].PB(t);
        while(stos[e]!=t){
            odp[q].PB(stos[e]);
            vs[stos[e--]]=false;
        }
        odp[q].PB(t);
        ++q;
    }
}

void Solve(){
    FOR(i,1,n) if(SIZE(h[i])%2){
        puts("NIE");
        return;
    }
    FOR(i,1,n)
        Cykle(i);
    printf("%d\n",q);
    REP(i,q){
        printf("%d ",SIZE(odp[i])-1);
        FOREACH(it,odp[i]) printf("%d ",*it);
        printf("\n");
    }
}

int main(){
    scanf("%d%d",&n,&m);
    REP(i,m){
        int a,b,s,t;
        scanf("%d%d%d%d",&a,&b,&s,&t);
        if(s!=t) Dodaj(a,b);
    }
    Solve();
    return 0;
}
