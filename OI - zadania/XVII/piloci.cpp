#include <cstdio>
#include <algorithm>
#include <memory.h>
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
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;

const int N = 3000001;

int n,t,b1,e1,b2,e2,wys[N],res;

PII kol1[N],kol2[N];

inline void Zdejmij(int x){
    if(b1<=e1 && kol1[b1].ND==x) ++b1;
    if(b2<=e2 && kol2[b2].ND==x) ++b2;
}

inline void Wstaw(int x){
    while(b1<=e1 && wys[x]>kol1[e1].ST)
        --e1;
    kol1[++e1]=MP(wys[x],x);
    while(b2<=e2 && wys[x]<kol2[e2].ST)
        --e2;
    kol2[++e2]=MP(wys[x],x);
}



int main(){
    scanf("%d%d",&t,&n);
    FOR(i,1,n)
        scanf("%d",&wys[i]);
    res=1;
    int kon=1;e1=e2=-1;
    b1=b2=0;
    FOR(i,1,n){
        Zdejmij(i-1);
        Wstaw(kon);
        ++kon;
        while(kon<=n+1 && kol1[b1].ST-kol2[b2].ST<=t){
            res=max(res,kon-i);
            if(kon>n) break;
            Wstaw(kon);++kon;
        }
        if(kon>n) break;
    }
    printf("%d",res);
    return 0;
}
