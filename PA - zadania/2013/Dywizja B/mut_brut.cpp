#include <cstdio>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second
#define make_pair MP
#define ALL(c) (c).begin(),(c).end()

#define MAXN 500002

int u[MAXN],v[MAXN];
int n,m,q;

int main(){
    scanf("%d",&n);
    FOR(i,1,n)
        scanf("%d",&u[i]);
    scanf("%d",&m);
    FOR(j,1,m)
        scanf("%d",&v[j]);
    scanf("%d",&q);
    REP(i,q){
        int a,b,l;
        scanf("%d%d%d",&a,&b,&l);
        int p=-1,c=-1;
        bool odp=true;
        REP(j,l){
            if(u[a+j]!=v[b+j])
                if(p==-1){
                    p=v[b+j];
                    c=u[a+j];
                }
                else if(p!=v[b+j] or c!=u[a+j]){
                    odp=false;
                    break;
                }
        }
        REP(j,l){
            if(v[b+j]==c)
                odp=false;
        }
        if(odp) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
