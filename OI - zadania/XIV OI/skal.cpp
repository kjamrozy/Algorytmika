#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

typedef pair<int,int> PII;

const int N = 1000001;
const int INF = 2000000001;

int n,m[N],x[N],y[N],k[4];
bool r[4][N];

void Koszt(int a,int b,int c,int d,int cas){
    k[cas]=0;
    FOR(i,1,n)
        if(x[i]<a || x[i]>b || y[i]<c || y[i]>d){
            if(y[i]<a || y[i]>b || x[i]<c || x[i]>d){
                k[cas]=INF;
                return;
            }else{
                k[cas]+=m[i];
                r[cas][i]=true;
            }
        }
}

void Solve(){
    int a,b,c,d,res=INF;///a - min, d - max
    a=c=INF,b=d=0;
    FOR(i,1,n){
        a=min(a,min(x[i],y[i]));
        b=max(b,min(x[i],y[i]));
        c=min(c,max(x[i],y[i]));
        d=max(d,max(x[i],y[i]));
    }
    Koszt(a,b,c,d,0);
    Koszt(c,d,a,b,1);
    Koszt(c,b,a,d,2);
    Koszt(a,d,c,b,3);
    int opt=min(min(k[0],k[1]),min(k[2],k[3]));
    printf("%lld %d\n",2*((long long)b-a+d-c),opt);
    int j=0;
    while(k[j]!=opt)
        ++j;
    FOR(i,1,n)
        printf("%d",r[j][i]);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d%d%d",&x[i],&y[i],&m[i]);
    }
    Solve();
    return 0;
}
