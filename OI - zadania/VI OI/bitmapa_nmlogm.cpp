//#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <memory.h>
#include <cstring>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end;++i)
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=185,M=185;

int n,m,ile;
bool bmap[M][N];
int res[M][N];
int up[M][N],down[M][N],w[4*M],W[4*M];
char txt[M];

#define f1(x,y) (x+y)
#define f2(x,y) min(x,y)
#define wiele(x,n) (x)
#define LOG_MAX_N 15

void init(){
    ile=2;
    while(ile<m+1) ile<<=1;
    FOR(i,1,ile*2-1) w[i]=W[i]=0;
}

inline void insert(int a,int b,int c){
    int va=ile+a,vb=ile+b;
    int d=0;
    w[va]=f1(w[va],c);
    if(va!=vb) w[vb]=f1(w[vb],c);
    while(va!=1){
        if(va/2!=vb/2){
            if(va%2==0) w[va+1]=f1(w[va+1],c);
            if(vb%2==1) w[vb-1]=f1(w[vb-1],c);
        }
        va/=2;vb/=2;
        W[va] = f2(f1(W[va*2],wiele(w[va*2],1<<d)),
                   f1(W[va*2+1],wiele(w[va*2+1],1<<d)));
        W[vb] = f2(f1(W[vb*2],wiele(w[vb*2],1<<d)),
                   f1(W[vb*2+1],wiele(w[vb*2+1],1<<d)));
        ++d;
    }
}

#define droga(l)do{\
    int w##l=0,v##l=ile+l;\
    while(v##l!=0){\
        pom##l[w##l++]=w[v##l];\
        v##l/=2;}\
    FORD(i,w##l-2,0) pom##l[i]=f1(pom##l[i],pom##l[i+1]);\
}while(0)

inline int query(int a,int b){
    int poma[LOG_MAX_N],pomb[LOG_MAX_N];
    droga(a);droga(b);
    int va=ile+a,vb=ile+b;
    int wynik=(va!=vb) ? f2(poma[0],pomb[0]) : poma[0];
    int d=0;
    while(va/2!=vb/2){
        if(va%2==0) wynik=f2(wynik,f1(W[va+1],wiele(f1(w[va+1],poma[d+1]),1<<d)));
        if(vb%2==1) wynik=f2(wynik,f1(W[vb-1],wiele(f1(w[vb-1],pomb[d+1]),1<<d)));
        va/=2;vb/=2;
        ++d;
    }
    return wynik;
}

void Solve(){
    init();
    FORD(i,n+1,0)
        FOR(j,1,m) down[j][i]=up[j][i]=-1,res[j][i]=n+m;
    FORD(i,n,1){
        FOR(j,1,m){
            up[j][i]=up[j][i+1];
            if(bmap[j][i]) up[j][i]=i,res[j][i]=0;
        }
        FOR(j,1,m){
            if(up[j][i]==-1)
                insert(j,j,-query(j,j)+m+n);
            else insert(j,j,-query(j,j)+abs(i-up[j][i]));
        }
        FOR(j,1,m)
            insert(j+1,m+1,1);
        FOR(j,1,m){
            res[j][i]=min(res[j][i],query(1,m));
            insert(0,j,1);
            insert(j+1,m+1,-1);
        }
    }
    FOR(i,1,n){
        FOR(j,1,m){
            down[j][i]=down[j][i-1];
            if(bmap[j][i]) down[j][i]=i,res[j][i]=0;
        }
        FOR(j,1,m){
            if(down[j][i]==-1)
                insert(j,j,-query(j,j)+m+n);
            else insert(j,j,-query(j,j)+abs(i-down[j][i]));
        }
        FOR(j,1,m)
            insert(j+1,m+1,1);
        FOR(j,1,m){
            res[j][i]=min(res[j][i],query(1,m));
            insert(0,j,1);
            insert(j+1,m+1,-1);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FORD(i,n,1){
        scanf("%s",txt);
        REP(j,strlen(txt))
            bmap[j+1][i]=(txt[j]=='0') ? 0 : 1;
    }
    Solve();
    FORD(i,n,1){
        FOR(j,1,m)
            printf("%d ",res[j][i]);
        printf("\n");
    }
    return 0;
}
