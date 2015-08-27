#include <algorithm>
#include <cstdio>

using namespace std;

#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define REP(x,e) for(int x=0;x<e;x++)

#define MAXN 251

int n[MAXN][MAXN];
int l,r;

void init(){
    FOR(i,1,l)
        n[i][0]=n[i][0]+n[i-1][0];
    FOR(i,1,l)
        n[0][i]=n[0][i]+n[0][i-1];
    FOR(i,1,l-1)
        FOR(j,1,l-1)
            n[j][i]=n[j][i]+n[j-1][i]+n[j][i-1]-n[j-1][i-1];
}

int suma(int xp,int xk,int yp,int yk){
    if(xp && yp){
        return n[xk][yk]-n[xp-1][yk]-n[xk][yp-1]+n[xp-1][yp-1];
    }else if(xp){
        return n[xk][yk]-n[xp-1][yk];
    }else if(yp){
        return n[xk][yk]-n[xk][yp-1];
    }else{
        return n[xk][yk];
    }
}

int main(){
    scanf("%d %d",&l,&r);
    REP(i,l)
        REP(j,l)
            scanf("%d",&n[j][i]);
    init();
    REP(i,l)
        REP(j,l){
            printf("%d",suma(max(0,j-r),min(j+r,l-1),max(0,i-r),min(i+r,l-1)));
            (j==l-1) ? printf("\n") : printf(" ");
        }
    return 0;
}
