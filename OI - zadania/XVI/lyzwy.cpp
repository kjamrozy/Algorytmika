#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 200001

int d,m,n,k;

int rozmiary[MAXN],pom[MAXN];

void Ans(){
    int r=n;
    FOR(i,1,n)
        pom[i]=k;
    FORD(i,n,1){
        int x=rozmiary[i];
        while(x>0 && r>=i){
            if(r>i+d)
                r=i+d;
            int c=min(x,pom[r]);
            pom[r]-=c;
            x-=c;
            if(pom[r]==0) --r;
        }
        if(x>0){
            puts("NIE");
            return;
        }
    }
    puts("TAK");
}

int main(){
    scanf("%d%d%d%d",&n,&m,&k,&d);
    REP(i,m){
        int r,x;
        scanf("%d%d",&r,&x);
        rozmiary[r]+=x;
        Ans();
    }
    return 0;
}
