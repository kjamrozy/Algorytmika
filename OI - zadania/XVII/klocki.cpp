#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define ST first
#define ND second
#define MP make_pair

#define MAXN 1000002

const long long INF = 1000000000000000001ll;

int n,m;
long long sum[MAXN],pom[MAXN];
int stos1[MAXN],stos2[MAXN];

int Wyznacz(int k){
    int e1,e2,res=0;
    e1=e2=-1;
    long long last=INF,x=0;
    pom[0]=0;
    FOR(i,1,n){
        x+=k;
        pom[i]=sum[i]-x;
        if(pom[i]<last)
            last=pom[stos1[++e1]=i];
    }
    last=-INF;
    FORD(i,n,1)
        if(pom[i]>last)
            last=pom[stos2[++e2]=i];
    int b=0;
    FOR(i,1,n)
        if(pom[i]>=0)
            res=max(res,i);
    while(e1>=0 && b<=e2){
        if(pom[stos2[b]]-pom[stos1[e1]]>=0){
            res=max(stos2[b]-stos1[e1],res);
            --e1;
        }else{
            ++b;
        }
    }
    return res;
}

int main(){
    scanf("%d%d",&n,&m);
    sum[0]=0;
    FOR(i,1,n){
        int t;
        scanf("%d",&t);
        sum[i]=sum[i-1]+t;
    }
    FOR(i,1,m){
        int t;
        scanf("%d",&t);
        printf("%d ",Wyznacz(t));
    }
    return 0;
}
