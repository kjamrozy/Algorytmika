#include <iostream>
#include <cstdio>
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
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define MP make_pair


typedef long long LL;
typedef pair<LL,int> PLL;

const int N = 1000001;

int n;
bool ds[N];
int p[N],d[N],w[N*2],W[2*N];
int ile;

#define f1(x,y) (x+y)
#define f2(x,y) min(x,y)
#define wiele(x,n) (x)
#define LOG_MAX_N 30

void init(){
    ile=2;
    while(ile<n+2) ile<<=1;
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

void Oblicz(){
    int b=0,e=-1;
    int sum = 0;
    FOR(i,1,n){
        sum+=p[i]-d[i];
        insert(i,i,-query(i,i)+sum);
    }
    if(query(1,n)>=0) ds[1]= true;
    FOR(i,2,n){
        insert(i,n+1,-p[i-1]+d[i-1]);
        insert(0,i-2,-p[i-1]+d[i-1]);
        insert(i-1,i-1,-query(i-1,i-1)+sum);
        if(query(1,n)>=0) ds[i] = true;
    }
}

void Solve(){
    memset(ds,false,sizeof(ds));
    Oblicz();
    reverse(&d[1],&d[n+1]);
    reverse(&p[2],&p[n+1]);
    reverse(&ds[2],&ds[n+1]);
    Oblicz();
    reverse(&ds[2],&ds[n+1]);
}

int main(){
    scanf("%d",&n);
    init();
    FOR(i,1,n)
        scanf("%d%d",&p[i],&d[i]);
    Solve();
    FOR(i,1,n)
        if(ds[i]) puts("TAK");
        else puts("NIE");
    return 0;
}
