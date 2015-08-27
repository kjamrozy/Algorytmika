#include <cstdio>
#include <algorithm>

using namespace std;

#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define REP(x,e) for(int x=0;x<e;x++)

#define f1(x,y) ((x)+(y))
#define f2(x,y) max(x,y)
#define wiele(x,n) (x)
#define PUSTY 0

#define MAXM 30001
#define MAXN 10001

int w[MAXM+1],_W[MAXM*4],_w[MAXM*4];
int _n=30000,n,ile;

struct Event{
    int a,b;
}Events[MAXN];

bool cmp(Event n1,Event n2){
    return (n1.a==n2.a) ? (n1.b<n2.b) : (n1.a<n2.a);
}

inline void insert(int a, int b,int c){
    int va=ile+a,vb=ile+b;
    _w[va]=f1(_w[va],c);
    if (va!=vb) _w[vb]=f1(_w[vb],c);
    while(va!=1){
        if(va/2!=vb/2){
            if (va%2 == 0) _w[va+1]=f1(_w[va+1],c);
            if (vb%2 == 1) _w[vb-1]=f1(_w[vb-1],c);
        }
        va/=2;vb/=2;
        _W[va] = f2(f1(_W[va*2],_w[va*2]),
                   f1(_W[va*2+1],_w[va*2+1]));
        _W[vb] = f2(f1(_W[vb*2],_w[vb*2]),
                   f1(_W[vb*2+1],_w[vb*2+1]));
    }
}

#define droga(l)\
do{\
    int w##l=0,v##l=ile+l;\
    while(v##l!=0){\
    pom##l[w##l++]=_w[v##l];\
    v##l/=2;\
    }\
    FORD(j,w##l-2,0) pom##l[j]=f1(pom##l[j],pom##l[j+1]);\
}while(0);

inline int query(int a,int b){
    int poma[30],pomb[30];
    droga(a);droga(b);
    int va=ile+a,vb=ile+b;
    int wynik = (va!=vb) ? f2(poma[0],pomb[0]) : poma[0];
    int d=0;
    while(va/2!=vb/2){
        if(va%2== 0)  wynik=f2(wynik, f1(f1(_W[va+1],poma[d+1]),_w[va+1]));
        if(vb%2== 1)  wynik=f2(wynik, f1(f1(_W[vb-1],pomb[d+1]),_w[vb-1]));
        va/=2;vb/=2;
        d++;
    }
    return wynik;
}

void init(){
    ile=1;
    while(ile<_n) ile<<=1;
    FOR(i,1,ile*2) _w[i]=_W[i]=PUSTY;
}

int main()
{
    scanf("%d",&n);
    REP(i,n) scanf("%d%d",&Events[i].a,&Events[i].b);
    sort(&Events[0],&Events[n],cmp);
    init();
//    REP(i,n) printf("%d %d\n",Events[i].a,Events[i].b);
    REP(i,n+1){
        w[Events[i].b]=max(w[Events[i].b], Events[i].b-Events[i].a+query(0,Events[i].a));
        int val=query(Events[i].b,Events[i].b);
        insert(Events[i].b,Events[i].b,-val);
        insert(Events[i].b,Events[i].b,w[Events[i].b]);
    }
    FOR(i,Events[n].b,MAXM+1) w[i]=max(w[i],w[i-1]);
    printf("%d",w[MAXM+1]);
    return 0;
}
