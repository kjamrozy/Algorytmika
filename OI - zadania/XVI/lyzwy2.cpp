#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 200002

int d,m,n,k,ile;
long long sum[MAXN*4],pref[MAXN*4],suf[MAXN*4],maks[MAXN*4];

inline void insert(int a,int c){
    int va=ile+a;
    sum[va]+=c;
    maks[va]=pref[va]=suf[va]=max(sum[va],0ll);
    while(va!=0){
        va/=2;
        sum[va]=sum[va*2]+sum[va*2+1];
        maks[va]=max(maks[va*2],max(maks[va*2+1],suf[va*2]+pref[va*2+1]));
        pref[va]=max(sum[va*2]+pref[va*2+1],pref[va*2]);
        suf[va]=max(sum[va*2+1]+suf[va*2],suf[va*2+1]);
    }
}

void init(){
    ile=1;
    while(ile<n+1) ile<<=1;
    FOR(i,0,2*ile)
        maks[i]=sum[i]=pref[i]=suf[i]=0;
    FOR(i,1,n)
        insert(i,-k);
}

int main(){
    scanf("%d%d%d%d",&n,&m,&k,&d);
    init();
    REP(i,m){
        int x,r;
        scanf("%d%d",&r,&x);
        insert(r,x);
        if((long long)d*k>=maks[1]) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
