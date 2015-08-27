#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

typedef long long LL;

LL f[20];

LL n,k;

LL fi(int x){
    f[0]=1;
    f[1]=1;
    FOR(i,2,x){
        FOR(j,0,i-1)
            f[i]+=f[j]*f[i-1-j];
    }
    return f[x];
}

void GenerujKod(char lit,int glb,LL num){
    if(glb==2){
        if(num==2)
            printf("%c%c",char(lit+1),char(lit));
        else
            printf("%c%c",char(lit),char(lit+1));
    }else if(glb==1){
        printf("%c",lit);
    }else if(glb!=0){
        FOR(i,0,glb-1){
            if(f[i]*f[glb-1-i]<num){
                num-=f[i]*f[glb-1-i];}
            else{
                printf("%c",lit+i);
                num-=1;
                GenerujKod(lit,i,( (glb-1-i!=0) ? num/f[glb-1-i]+1 : num+1 ) );
                GenerujKod(char(lit+i+1),glb-1-i,((i!=0) ? (num%f[glb-1-i]+1) : (num)+1 ));
                return;
            }
        }
    }
}

int main(){
    scanf("%lld%lld",&n,&k);
    fi(k);
    GenerujKod('a',k,n);
    return 0;
}
