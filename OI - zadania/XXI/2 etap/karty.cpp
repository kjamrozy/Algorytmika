///Karol Jamrozy
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) ((int)(x).size())
#define MP make_pair

typedef pair<int,int> PII;

const int N = 200005,M = 1000001;

struct Vertex{
    PII tab[4];
    Vertex()  {
        REP(i,4)
            tab[i]=MP(-1,-1);
    }
};

int n,m,ile;
Vertex w[4*N];

void init(){
    ile=2;
    while(ile<n+3) ile<<=1;
    FOR(i,1,ile*2-1) w[i]=Vertex();
}

Vertex Merge(Vertex a,Vertex b){
    Vertex c;
    REP(i,4){
        if(a.tab[i]==MP(-1,-1)) break;
        REP(j,4){
            if(b.tab[j]==MP(-1,-1)) break;
            if(a.tab[i].ND<=b.tab[j].ST){
                PII r = MP(a.tab[i].ST,b.tab[j].ND);
                REP(k,4){
                    if(c.tab[k]==r) break;
                    if(c.tab[k]==MP(-1,-1)){
                        c.tab[k]=r;break;
                    }
                }
            }
        }
    }
    return c;
}

void Popraw(int x,Vertex& a){
    int vx=ile+x;
    w[vx]=a;
    while(vx!=1){
        vx/=2;
        w[vx]=Merge(w[vx*2],w[vx*2+1]);
    }
}

Vertex Query(int a,int b){
    Vertex res,wa,wb;
    if(a==b){
        return w[ile+a];
    }
    int va=ile+a,vb=ile+b;
    wa=w[va];wb=w[vb];
    while(va/2!=vb/2){
        if(va%2==0) wa=Merge(wa,w[va+1]);
        if(vb%2) wb=Merge(w[vb-1],wb);
        va/=2;vb/=2;
    }
    res = Merge(wa,wb);
    return res;
}

int main(){
    scanf("%d",&n);
    init();
    FOR(i,1,n){
        int a,b;scanf("%d%d",&a,&b);
        Vertex x;x.tab[0]=MP(a,a);x.tab[1]=MP(b,b);x.tab[3]=x.tab[2]=MP(-1,-1);
        Popraw(i,x);
    }
    scanf("%d",&m);
    FOR(i,1,m){
        int a,b;scanf("%d%d",&a,&b);
        Vertex wa,wb,res;
        wa=Query(a,a);wb=Query(b,b);
        Popraw(a,wb);Popraw(b,wa);
        res=Query(1,n);
        bool dasie=false;
        REP(j,4){
            if(res.tab[j]!=MP(-1,-1)){
                dasie=true;break;
            }
        }
        if(dasie) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
