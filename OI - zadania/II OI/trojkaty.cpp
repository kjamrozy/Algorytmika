#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

const int N = 1000001;

int dlg[N],poz;

inline bool Trojkat(int a,int b,int c){
    return a+b>c && c+a>b && b+c>a;
}

int main(){
    int t;poz=0;
    do{
        scanf("%d",&t);
        dlg[poz++]=t;
    }while(t);
    sort(&dlg[0],&dlg[poz]);
    REP(i,poz-2)
        if(Trojkat(dlg[i],dlg[i+1],dlg[i+2])){
            printf("%d %d %d\n",dlg[i],dlg[i+1],dlg[i+2]);
            return 0;
        }
    puts("NIE");
    return 0;
}
