#include <cstdio>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 500003

typedef long long LL;

LL hash=97,BASE=1000000007;
LL pot[MAXN],hashe[MAXN];
char tekst[MAXN];
int n,q,pierw[MAXN];

void Init(){
    pot[0]=1;
    FOR(i,1,n){
        pot[i]=(pot[i-1]*hash)%BASE;
        pierw[i]=-1;
    }
    pierw[1]=1;
    FORD(i,n,1) hashe[i]=(hashe[i+1]*hash+(int)tekst[i])%BASE;
    FOR(i,2,n){
        if(pierw[i]==-1){
            int d=i;
            while(d<=n){
                pierw[d]=i;
                d+=i;
            }
        }
    }
}

LL Hash(int a,int b){
    LL res=(hashe[a]-(hashe[b+1]*pot[b-a+1])%BASE)%BASE;
    if(res<0) res+=BASE;
    return res;
}

int Okres(int a,int b){
    int m=b-a+1,l=1;
    while(m!=l){
        int d=1,k=pierw[m/l];
        while((m/l)%(d*k)==0)
            d*=k;
        if( Hash(a+(m/k),b)==Hash(a,b-(m/k)) )
            m/=k;
        else l*=d;
    }
    return m;
}

int main(){
    scanf("%d",&n);
    scanf("%s",tekst+1);
    Init();
    scanf("%d",&q);
    while(q--){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",Okres(a,b));
    }
    return 0;
}
