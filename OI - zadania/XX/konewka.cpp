#include<iostream>
#include <algorithm>
#include <iostream>

#define REP(x,e) for(int x=0;x<e;x++)
#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)

#define f1(x,y) ((x)+(y))
#define f2(x,y) max(x,y)
#define wiele(x,n) ((x))
#define PUSTY 0

#define MAXN 300001
#define LOGMAXN 25

int w[MAXN*4],W[MAXN*4],DOJRZ[MAXN*4];

int ile,N,K;
bool offline=false;

using namespace std;

inline void insert(int a, int b,int c){
    int va=ile+a,vb=ile+b;
    w[va]=f1(w[va],c);
    if (va!=vb) w[vb]=f1(w[vb],c);
    int d=0;
    while(va!=1){
        if(va/2!=vb/2){
            if(va%2==0) w[va+1]=f1(w[va+1],c);
            if(vb%2==1) w[vb-1]=f1(w[vb-1],c);
        }
        va/=2;vb/=2;
        W[va]=f2(f1(W[va*2],wiele(w[va*2],1<<d)),
                 f1(W[va*2+1],wiele(w[va*2+1],1<<d)));
        W[vb]=f2(f1(W[vb*2],wiele(w[vb*2],1<<d)),
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

int query(int a,int b){
    int poma[LOGMAXN],pomb[LOGMAXN];
    droga(a);droga(b);
    int va=ile+a,vb=ile+b;
    int wynik= (va!=vb) ? f2(poma[0],pomb[0]) : poma[0];
    int d=0;
    while(va/2!=vb/2){
        if(va%2==0) wynik=f2(wynik,f1(W[va+1],wiele(f1(w[va+1],poma[d+1]),1<<d)));
        if(vb%2==1) wynik=f2(wynik,f1(W[vb-1],wiele(f1(w[vb-1],pomb[d+1]),1<<d)));
        va/=2;vb/=2;
        d++;
    }
    return wynik;
}

void Ekstrakcja(){
    //dopoki maksimum w dzrzewie jest wieksze lub rowne K
    while(W[1]+w[1]>=K){
        //niech ad bedze korzeniem drzewa
        int ad=1;
        //schodzimy az do naszego najwyzszego doroslego drzewka
        while(ad<ile){
            if((W[ad*2]+w[ad*2])>(W[ad*2+1]+w[ad*2+1])){
                ad=ad*2;
            }else{
                ad=ad*2+1;
            }
        }
        //ustawiamy temu drzewku doroslosc w drzewie(+,+)
        DOJRZ[ad]=1;
        //zas w drzewie(+,max) ustawiamu mu taka wartosc, aby juz nigdy nie stalo sie dorosle
        w[ad]=-900000;
        int d=0;
        //idac do korzenia aktualizujemy w drzewach (+,max) i (+,+) poszczegolne zmienne
        while(ad!=1){
            ad/=2;
            W[ad] = f2(f1(W[ad*2],wiele(w[ad*2],1<<d)),
                       f1(W[ad*2+1],wiele(w[ad*2+1],1<<d)));
            DOJRZ[ad] = f1(DOJRZ[ad*2],DOJRZ[ad*2+1]);
            d++;
        }
    }
}

//inicjacja poszczegolnych zmiennych
void inicjuj(int n, int k, int *D)
{
    N = n, K = k;
    ile=1;
    while(ile<N) ile<<=1;
    FOR(i,1,ile*2) w[i]=W[i]=DOJRZ[i]=PUSTY;
    REP(i,n) insert(i,i,D[i]);
}

//podlewa drzewka
void podlej(int a, int b)
{
    Ekstrakcja();
    insert(a,b,1);
}

//proste pytanie o sume z przedzialu
int dojrzale(int a, int b)
{
    //dokonujemy ew. ekstrakcji(sciecia) drzewa
    Ekstrakcja();
    //standardowe zapytanie
    int va=ile+a,vb=ile+b;
    int wynik=(va!=vb) ? f1(DOJRZ[va],DOJRZ[vb]) : DOJRZ[va];
    while(va/2!=vb/2){
        if(va%2==0) wynik=f1(wynik,DOJRZ[va+1]);
        if(vb%2==1) wynik=f1(wynik,DOJRZ[vb-1]);
        va/=2;vb/=2;
    }
    return wynik;
}
