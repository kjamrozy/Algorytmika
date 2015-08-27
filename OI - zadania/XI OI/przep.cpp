#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define SIZE(x) ((int)(x).size())
#define ND second
#define MP make_pair
#define PB push_back

#define MAXN 18

const int INF=1000000000;

int w,n;
int sz[MAXN],c[MAXN],wart[1<<17];

inline int Numer(bool* tab){
    int res=0;
    REP(i,n)
        res+=tab[i]*(1<<i);
    return res;
}

int dziel(bool kogo[]);

int dobierz(int waga,bool kogo[],int x){
    bool temp[n];
    if(x>=n){
        return dziel(kogo);
    }else{
        memcpy(temp,kogo,sizeof(temp));
        int res=dobierz(waga,temp,x+1);
        if(kogo[x] && waga-c[x]>=0){
            kogo[x]=false;
            res=min(res,dobierz(waga-c[x],kogo,x+1));
        }
        return res;
    }
}

int dziel(bool kogo[]){
    int x=Numer(kogo);
    if(wart[x]!=-1) return wart[x];
    int d=0,di=-1;
    REP(i,n)
        if(kogo[i] && c[i]<w && sz[i]>d)
            d=sz[i],di=i;
    kogo[di]=false;
    return (wart[x]=(d+dobierz(w-c[di],kogo,0)));
}

void Solve(){
    bool baj[n];
    REP(i,n) baj[i]=true;
    wart[0]=0;
    printf("%d",dziel(baj));
}

int main(){
    scanf("%d%d",&w,&n);
    REP(i,n)
        scanf("%d%d",&sz[i],&c[i]);
    memset(wart,-1,sizeof(wart));
    Solve();
    return 0;
}
