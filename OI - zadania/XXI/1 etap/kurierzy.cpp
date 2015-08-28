/// Karol Jamrozy
/// Literatura: Algorytmika praktyczna Nie tylko dla mistrzów - Piotr Stańczyk
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define SIZE(x) ((int)(x).size())
#define PB push_back

#define MAXN 500001

int paczki[MAXN],polowa[MAXN+1];//tablica na ciag paczek podanych na wejsciu, stablicowanie polow z roznych liczb
vector<int> kurierzy[MAXN];//vector paczek w kolejnosci od najwczesniejszych do najpozniejszych dla danej firmy
bool sprawdzani[MAXN];//tablica przechowujaca sprawdzanych kurierow dla jednego zapytania, ktorzy juz byli sprawdzani
long long rands[1000000];//tablica z losowymi liczbami(aby zbic nieco ukryta stala)
int n,m,r;

inline bool GTH(int c,int a,int b){// funkcja sprawdza czy firma dominuje
    return c>polowa[b-a+1];
}

int Bin1(int r,int c){
    int b=0,a=SIZE(kurierzy[c])-1;
    while(a!=b){
        int d=(a+b)/2;
        if(kurierzy[c][d]>=r)
            a=d;
        else b=d+1;
    }
    return a;
}

int Bin2(int r,int c){
    int a=0,b=SIZE(kurierzy[c])-1;
    if(kurierzy[c][a]>r) return -1;
    while(a!=b-1){
        int d=(a+b)/2;
        if(kurierzy[c][d]<=r)
            a=d;
        else b=d;
    }
    if(kurierzy[c][b]<=r)
        a=b;
    return a;
}

int Query(int x,int y){//odpowiada na zapytanie
    REP(i,40){
        int k=rands[r++]%(y-x+1)+x;
        r%=2*max(m,500);
        if(sprawdzani[paczki[k]]) continue;
        if(SIZE(kurierzy[paczki[k]])==0 or !(kurierzy[paczki[k]][0]<=y && kurierzy[paczki[k]][SIZE(kurierzy[paczki[k]])-1]>=x))
            continue;
        if(!GTH(SIZE(kurierzy[paczki[k]]),x,y)) continue;
        if(SIZE(kurierzy[paczki[k]])==1){
            if(GTH(1,x,y)) return paczki[k];
            else continue;
        }
        int p,kn;
        p=Bin1(x,paczki[k]);
        kn=Bin2(y,paczki[k]);
        if(kn==-1 or p==-1) continue;
        if(GTH(kn-p+1,x,y)){
            return paczki[k];
        }
    }
    return 0;
}

void Init(){
    FOR(i,1,n)
        if(ceil(double(i)/2)==floor(double(i)/2))
            polowa[i]=i/2;
        else polowa[i]=ceil(double(i)/2)-1;
    REP(i,2*max(m,500))
        rands[i]=rand();
    r=0;
}

int main(){
    srand(time(NULL));
    scanf("%d%d",&n,&m);
    Init();
    FOR(i,1,n){//wczytywanie danych
        scanf("%d",&paczki[i]);
        kurierzy[paczki[i]].PB(i);
    }
    FOR(i,1,m){//odpowiadanie na zapytania
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",Query(a,b));
    }
    return 0;
}
