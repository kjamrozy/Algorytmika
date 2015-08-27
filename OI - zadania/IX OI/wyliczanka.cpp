#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second
#define MP make_pair

typedef long long LL;

int GCDW(int a,int b,LL& l,LL& k){
    if(!a){
        l=0;
        k=1;
        return b;
    }
    int d = GCDW(b%a,a,k,l);
    l-=k*(b/a);
    return d;
}

bool congr(LL a, LL b, LL p, LL q, LL &c, LL &r) {
    LL x, y;
    r = GCDW(p, q, x, y);
    p/=r;q/=r;
    if ((a-b)%r) return 0;
    c = a*y*q+b*x*p;
    r = p*q*r;
    c%=r;
    if (c < 0) c += r;
    return 1;
}

const int N = 21;

int n;
int kol[N];

int main(){
    scanf("%d",&n);
    REP(i,n) scanf("%d",&kol[i]);
    LL c=0,r=1;
    int ind=0;
    FOR(i,1,n-1){
        int d=1,p=ind;
        FOR(j,0,n-1){
            if(kol[(p+j)%n]>i) ++d;
            if(i==kol[(p+j)%n]){
                ind=(p+j+1)%n;
                break;
            }
        }
        if(!congr(d%(n-i+1),c,n-i+1,r,c,r)){
            puts("NIE");
            return 0;
        }
    }
    c%=r;
    if(c<=0) c+=r;
    printf("%d",c);
    return 0;
}
