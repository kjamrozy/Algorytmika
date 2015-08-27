#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

const int N = 2000001;

int x,y,n;
int l1[N],l2[N],pom[N];

void faza0(){
    if(pom[1]==2 && pom[2]==0){
        pom[2]=1;
        pom[1]=0;
    }
    if(pom[1]==0 && pom[2]==2){
        pom[1]=2;pom[2]=1;
    }
    if(pom[1]==2 && pom[2]==1){
        int ind=2;
        while(pom[ind]==1)
            ++ind;
        if((ind)%2){
            bool wart=0;
            FOR(i,2,ind+1){
                pom[i]=wart;
                wart=!wart;
            }
            pom[1]=1;
        }else{
            pom[1]=0;
            bool wart=1;
            FOR(i,2,ind){
                pom[i]=wart;
                wart=!wart;
            }
        }
    }
}

void faza1(){
    FORD(i,n-1,1)
        if(pom[i]==1 && pom[i+1]==1){
            pom[i+2]++;
            pom[i]=pom[i+1]=0;
            n=max(n,i+2);
        }
}

void faza11(){
    FOR(i,1,n-1)
        if(pom[i]==1 && pom[i+1]==1){
            pom[i+2]++;
            pom[i]=pom[i+1]=0;
            n=max(n,i+2);
        }
}

void faza2(){
    FOR(i,1,n){
        if(pom[i]==1 && pom[i+1]==1 && pom[i+2]==2){
            pom[i+3]++;
            pom[i+2]=pom[i]=1;
            pom[i+1]=0;
            n=max(n,i+3);
        }else if(pom[i]==1 && pom[i+1]==2){
            pom[i]=0;
            pom[i+1]=1;
            ++pom[i+2];
            n=max(i+2,n);
        }
    }
}

void faza3(){
    FOR(i,1,n){
        if(pom[i]==1 && pom[i+1]==1 && pom[i+2]==0 && pom[i+3]==2){
            pom[i]=pom[i+1]=0;
            pom[i+2]=1;pom[i+3]=2;
            n=max(n,i+3);
        }else if(pom[i]==1 && pom[i+1]==2 ){
            pom[i]=0;
            pom[i+1]=1;
            ++pom[i+2];
            n=max(i+2,n);
        }else if(pom[i]==1 && pom[i+1]==2 && pom[i+2]==1){
            pom[i]=0;
            pom[i+1]=1;
            pom[i+2]=2;
            n=max(n,i+2);
        }
    }
}
bool faza4(){
    bool t=false;
    FORD(i,n,1){
        if(pom[i]==1 && pom[i+1]==0 && pom[i+2]==2){
            pom[i]=2;
            pom[i+1]=pom[i+2]=1;
            n=max(n,i+2);
            t=true;
        }else if(pom[i]==0 && pom[i+1]==0 && pom[i+2]==2){
            pom[i]=pom[i+1]=pom[i+2]=1;
            n=max(n,i+2);
            t=true;
        }
    }
    return t;
}


void Solve(){
    FOR(i,1,x)
        pom[i]+=l1[i];
    FOR(i,1,y)
        pom[i]+=l2[i];
    n=1000001;
    faza1();
    faza2();
    faza4();
    faza0();
    faza3();
    faza1();
    faza11();
    while(!pom[n]) --n;
    printf("%d ",n);
    FOR(i,1,n)
        printf("%d ",pom[i]);
}

int main(){
    scanf("%d",&x);
    FOR(j,1,x)
        scanf("%d",&l1[j]);
    scanf("%d",&y);
    FOR(j,1,y)
        scanf("%d",&l2[j]);
    Solve();
    return 0;
}
