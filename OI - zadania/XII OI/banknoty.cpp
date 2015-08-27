#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

const int N = 201;
const int K = 20001;
const int INF = 1000000001;

int b[N],c[N][K],s[K],r[K],res[N],n,k;

void Solve(){
    FOR(i,1,k) s[i]=-1,r[i]=INF;
    r[0]=0;
    FOR(i,1,n)
        if(c[i][0] && r[b[i]]==INF){
            r[b[i]]=1;
            s[b[i]]=i;
        }
    FOR(j,1,k){
        if(r[j]!=INF){
            FOR(i,1,n){
                c[i][j]=c[i][j-b[s[j]]];
                if(b[i]==b[s[j]]) --c[i][j];
            }
            FOR(i,1,n)
                if(c[i][j] && j+b[i]<=k && r[j]+1 < r[j+b[i]] ){
                    r[j+b[i]]=r[j]+1;
                    s[j+b[i]]=i;
                }
        }
    }
    printf("%d\n",r[k]);
    int x=k;
    while(x){
        res[s[x]]++;
        x-=b[s[x]];
    }
    FOR(i,1,n)
        printf("%d ",res[i]);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n)
        scanf("%d",&b[i]);
    FOR(i,1,n)
        scanf("%d",&c[i][0]);
    scanf("%d",&k);
    Solve();
    return 0;
}
