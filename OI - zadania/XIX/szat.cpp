#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>

#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define REP(x,e) for(int x=0;x<e;++x)

using namespace std;

#define MAXN 1002
#define MAXP 1000002
#define MAXNP 1110000
#define MAXK 100002

const int INF = 1000000001;

int n,p,el,maxk;
int termin[MAXK];
bool ans[MAXP];

struct zd{
    int k,a,b,nr;
};

zd X[MAXNP];

bool cmp(const zd& a,const zd& b){
    return (abs(a.a)==abs(b.a)) ? ((a.a>0) ? 1 : 0 ) : abs(a.a)<abs(b.a);
}

void Donies(int ter,int war){
    FORD(i,maxk,war)
        termin[i]=max(min(ter,termin[i-war]),termin[i]);
}

void Solve(){
    sort(&X[0],&X[el],cmp);
    FOR(i,1,maxk)
        termin[i]=-INF;
    termin[0]=INF;
    REP(i,el){
        if(X[i].a>0){
            Donies(X[i].b,X[i].k);
        }else{
            ans[X[i].nr]=(abs(X[i].a)+X[i].b<termin[X[i].k]) ? true : false;
        }
    }
    FOR(i,1,p)
        if(ans[i]) puts("TAK");
        else puts("NIE");
}

int main(){
    scanf("%d",&n);
    el=0;
    maxk=-1;
    FOR(i,1,n){
        int t1,t2,t3;
        scanf("%d%d%d",&t1,&t2,&t3);
        X[el].k=t1;
        X[el].a=t2;
        X[el].b=t3;
        ++el;
    }
    scanf("%d",&p);
    FOR(i,1,p){
        int t1,t2,t3;
        scanf("%d%d%d",&t1,&t2,&t3);
        X[el].a=-t1;
        X[el].k=t2;
        X[el].b=t3;
        X[el].nr=i;
        maxk=max(maxk,t2);
        ++el;
    }
    Solve();
    return 0;
}
