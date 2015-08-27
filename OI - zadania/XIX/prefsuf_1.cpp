#include <cstdio>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

#define MAXN 1000002

typedef long long LL;

int n;
char s[MAXN];
LL h[MAXN],pot[MAXN];
LL BASE=1000000007;
LL hash = 313;

void init(){
    pot[0]=1;
    FOR(i,1,n/2+1){
        pot[i]=(pot[i-1]*hash)%BASE;
    }
    h[n-1]=(int)s[n-1];
    FORD(i,n-2,0)
        h[i]=(h[i+1]*hash+(int)s[i])%BASE;
}

LL Hash(int a,int b){
    LL result=(h[a]-h[b+1]*pot[b-a+1])%BASE;
    if(result<0) result+=BASE;
    return result;
}

int Solve(){
    FORD(i,n/2-1,0){
        LL slowo2=Hash(0,i);
        if(slowo2==Hash(n-1-i,n-1))
            return i+1;
        FOR(j,1,i){
            LL slowo;
            slowo=Hash(n-1-i+j,n-1);
            slowo+=(Hash(n-1-i,n-1-i+j-1)*pot[i-j+1]);
            slowo%=BASE;
            if(slowo==slowo2)
                return i+1;
        }
    }
    return 0;
}

int main(){
    scanf("%d",&n);
    assert(scanf("%s",s));
    init();
    printf("%d",Solve());
    return 0;
}
