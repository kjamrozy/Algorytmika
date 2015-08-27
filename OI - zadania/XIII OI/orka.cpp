#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define PB push_back
#define SIZE(x) ((int)(x).size())

typedef long long LL;

const int N = 2001,M=2001;

int k,n,m,zad;
bool faza;

LL pole[M][N];

LL Suma(int a,int b,int c,int d){
    return pole[b][d]-pole[a-1][d]-pole[b][c-1]+pole[a-1][c-1];
}

int Oraj(int a,int b,int c,int d){
    if(a>b or c>d) return 0;
    if(faza){///poziomo
        if(Suma(a,b,c,c)<=k)
            return 1+Oraj(a,b,c+1,d);
        if(Suma(a,b,d,d)<=k)
            return 1+Oraj(a,b,c,d-1);
        if(zad && Suma(a,a,c,d)<=k){
            --zad;
            return 1+Oraj(a+1,b,c,d);
        }
        if(Suma(b,b,c,d)<=k)
            return 1+Oraj(a,b-1,c,d);
    }else{///pionowo
        if(Suma(a,a,c,d)<=k)
            return 1+Oraj(a+1,b,c,d);
        if(Suma(b,b,c,d)<=k)
            return 1+Oraj(a,b-1,c,d);
        if(zad && Suma(a,b,c,c)<=k){
            --zad;
            return 1+Oraj(a,b,c+1,d);
        }
        if(Suma(a,b,d,d)<=k)
            return 1+Oraj(a,b,c,d-1);
    }
    return m+n;
}

int Solve(){
    int res=m+n;
    faza=1;
    FOR(i,0,m){
        zad=i;
        res=min(res,Oraj(1,m,1,n));
    }
    faza=0;
    FOR(i,0,n){
        zad=i;
        res=min(res,Oraj(1,m,1,n));
    }
    return res;
}

int main(){
    scanf("%d%d%d",&k,&m,&n);
    FOR(i,1,n)
        FOR(j,1,m)
            scanf("%lld",&pole[j][i]);
    FOR(i,1,n)
        FOR(j,1,m)
            pole[j][i]=pole[j][i]+pole[j-1][i]+pole[j][i-1]-pole[j-1][i-1];
    printf("%d",Solve());
    return 0;
}
