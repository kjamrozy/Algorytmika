#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

typedef pair<int,int> PII;
typedef long long LL;

const int N = 601;
const int M = 10001;

int n,m,sumz;
int zp[N][N],fp[N][N],x[N],y[N],fx[M],fy[M],w[M];

int det(int x1,int y1,int x2,int y2,int x3,int y3){
    return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

int Trojkat(int a,int b,int c){
    return sumz-fp[a][b]-fp[b][c]-fp[c][a];
}

int main(){
    scanf("%d",&n);
    REP(i,n)
        scanf("%d%d",&x[i],&y[i]);
    scanf("%d",&m);
    REP(i,m){
        scanf("%d%d%d",&fx[i],&fy[i],&w[i]);
        sumz+=w[i];
    }
    REP(i,m){
        int t=1;
        REP(j,n){
            int d;
            while(j!=t && (d=det(x[j],y[j],fx[i],fy[i],x[t],y[t]))>=0){
                t=(t+1)%n;
            if(d==0)
                zp[j][t]+=w[i];
            }
            if(j!=t)
                fp[j][t]+=w[i];
        }
    }
    REP(i,n)
        REP(j,n-1)
            fp[i][(i+j+1)%n]+=fp[i][(i+j)%n];
    int res=sumz;
    REP(i,n)
        FOR(j,1,n-2)
            FOR(k,j+1,n-1)
                res=max(Trojkat(i,(i+j)%n,(i+k)%n),res);
    printf("%d",res);
    return 0;
}
