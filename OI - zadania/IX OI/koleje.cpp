#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define FOR(x,b,e) for(int x=b;x<=e;x++)

#define f1(x,y) ((x)+(y))
#define f2(x,y) max(x,y)
#define wiele(x,n) (x)
#define PUSTY 0

#define MAXN 60001
#define MAXLOGN 30

int w[MAXN*4],W[MAXN*4];
int ile,n,m,z;
char* res;

inline void insert(int a,int b,int c){
    int va=ile+a,vb=ile+b;
    w[va]=f1(w[va],c);
    if(va!=vb) w[vb]=f1(w[vb],c);
    int d=0;
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
        d++;
    }
}

#define droga(l)\
do{\
    int w##l=0,v##l=ile+l;\
    while(v##l!=0){\
        pom##l[w##l++]=w[v##l];\
        v##l/=2;\
    }\
    FORD(j,w##l-2,0) pom##l[j]=f1(pom##l[j],pom##l[j+1]);\
}while(0)

inline int query(int a,int b){
    int poma[MAXLOGN],pomb[MAXLOGN];
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

void init(){
    ile=1;
    while(ile<n) ile<<=1;
    FOR(i,1,ile*2) w[i]=W[i]=PUSTY;
}

int main(){
    scanf("%d%d%d",&n,&m,&z);
    init();
    res=new char[z];
    REP(x,z){
        int p,k,l;
        scanf("%d%d%d",&p,&k,&l);
        if(query(p,k-1)+l<=m){
            res[x]='T';
            insert(p,k-1,l);
        }
        else res[x]='N';
    }
    REP(x,z)
        printf("%c\n",res[x]);
    delete [] res;
    return 0;
}
