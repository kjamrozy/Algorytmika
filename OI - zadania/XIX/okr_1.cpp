#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <assert.h>

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second

using namespace std;

typedef long long LL;

#define MAXN 500002

const LL BASE = 1000000007;
const LL hash = 311;
int n,q;
LL h[MAXN],pot[MAXN];
char wiersz[MAXN];

void init(){
    h[n-1]=(int)wiersz[n-1];
    FORD(i,n-1,0)
        h[i]=((int)wiersz[i]+hash*h[i+1])%BASE;
    pot[0]=1;
    FOR(i,1,n+1)
        pot[i]=(pot[i-1]*hash)%BASE;
}

LL Hasz(int a,int b){
    LL result;
    result=(h[a]-h[b+1]*pot[b-a+1])%BASE;
    if(result<0) result+=BASE;
    return result;
}

int Odpowiedz(int a,int b){
    int altok=b+1;
    int dlg=b-a+1;
    FOR(i,1,sqrt(b-a+1)){
        if(dlg%i==0 && Hasz(a,b-i)==Hasz(a+i,b))
            return i;
        else if(dlg%i==0 && Hasz(a+(b-a+1)/i,b)==Hasz(a,b-(b-a+1)/i))
                altok=(b-a+1)/i;
    }
    return min(b-a+1,altok);
}

int main(){
    scanf("%d%s%d",&n,wiersz,&q);
    init();
    assert(0);
    REP(i,q){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",Odpowiedz(a-1,b-1));
    }
    return 0;
}
