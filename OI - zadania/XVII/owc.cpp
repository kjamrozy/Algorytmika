#include <cstdio>
#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

const int N = 601;
const int K = 20001;

int n,k,m;
int x[N],y[N],px[K],py[K];
int fp[N][N],T[N][N];
bool przek[N][N];

int det(int x1,int y1,int x2,int y2,int x3,int y3){
    return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

int main(){
    scanf("%d%d%d",&n,&k,&m);
    memset(przek,true,sizeof(przek));
    REP(i,n)
        scanf("%d%d",&x[i],&y[i]);
    REP(i,k)
        scanf("%d%d",&px[i],&py[i]);
    REP(i,k){
        int t=1;
        REP(j,n){
            int d;
            while( t!=j && (d=det(x[j],y[j],px[i],py[i],x[t],y[t]))>=0){
                if(d==0)
                    przek[j][t]=przek[t][j]=false;
                t=(t+1)%n;
            }
            if(t!=j)
                ++fp[j][t];
        }
    }
    REP(i,n){
        int sum=0;
        FOR(j,2,n-1){
            sum+=fp[i][(i+j)%n];
            if(sum%2!=0) przek[i][(i+j)%n]=przek[(i+j)%n][i]=false;
        }
    }
    REP(i,n){
        T[i][i]=1;
        if(przek[i][(i+1)%n]) T[i][(i+1)%n]=1;
    }
    FOR(d,2,n-2){
        REP(i,n){
            if(przek[i][(i+d)%n]){
                T[i][(i+d)%n]=0;
                FOR(j,1,d-1){
                    if(przek[i][(i+j)%n] && przek[(i+j)%n][(i+d)%n]){
                        T[i][(i+d)%n]+=T[i][(i+j)%n]*T[(i+j)%n][(i+d)%n];
                        T[i][(i+d)%n]%=m;
                    }
                }
            }
        }
    }
    long long wyn=0;
    FOR(i,2,n-1){
        wyn+=T[1][i]*T[i][0];
        wyn%=m;
    }
    printf("%lld",wyn);
    return 0;
}


