#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1000000005;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define PB push_back

#define MAXN 1000002

int n,p,q,x,y,sum,r,k,ki,sumpref[MAXN];
char ciag[MAXN];

void Init(){
    sumpref[0]=p;
    k=INF;
    ki=-1;
    FOR(i,1,n){
        sumpref[i]= (ciag[i]=='+') ? sumpref[i-1]+1 : sumpref[i-1]-1;
        if(sumpref[i]<=k){
            k=sumpref[i];
            ki=i;
        }
    }
    sumpref[n+1]=sumpref[n];
    r=sumpref[n]-q;
}

void Solve(){
    Init();
    int res=x*(abs(r)/2);
    k-=min(r,0);
    if(2*x<y){
        if(k<0){
            res+=2*x*((abs(k)+1)/2);
        }
        printf("%d",res);
        return;
    }else{
        int opt=0;
        if(k<0){
        opt=2*x*((abs(k)+1)/2);
        FORD(i,n+1,ki+1){
            if( (n+1-i)*y+2*x*(max(0,(abs(k)+1-(sumpref[n+1]-sumpref[i-1]))/2)) <opt){
                opt=(n+1-i)*y+2*x*(max(0,(abs(k)+1-(sumpref[n+1]-sumpref[i-1]))/2));
            }
        }
        }
        printf("%d",res+opt);
    }
}

int main(){
    scanf("%d%d%d%d%d",&n,&p,&q,&x,&y);
    scanf("%s",ciag+1);
    Solve();
    return 0;
}
