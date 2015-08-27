#include <algorithm>
#include <cstdio>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 100002
#define MAXM 1000002

int n;

int e1,e2,e3,stos1[2*MAXN],stos2[2*MAXN],res[MAXM];
bool klocek[MAXN];

void Solve(){
    FOR(i,1,n)
        klocek[i]=false;
    e1=e3=-1;
    while(e2>=0){
        if(klocek[stos2[e2]]){
            int k=stos2[e2--];
            while(stos1[e1]!=k){
                res[++e3]=e1+1;
                klocek[stos1[e1]]=false;
                stos2[++e2]=stos1[e1--];
            }
            --e1;
        }else{
            stos1[++e1]=stos2[e2--];
            klocek[stos1[e1]]=true;
        }
    }
}

int main(){
    scanf("%d",&n);
    e2=2*n-1;
    REP(i,2*n){
        int t;
        scanf("%d",&t);
        stos2[2*n-1-i]=t;
    }
    Solve();
    printf("%d\n",e3+1);
    FOR(i,0,e3)
        printf("%d\n",res[i]);
    return 0;
}
