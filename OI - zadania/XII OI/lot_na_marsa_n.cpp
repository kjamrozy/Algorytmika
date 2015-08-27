#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define MP make_pair


typedef long long LL;
typedef pair<int,int> PII;

const int N = 1000001;

int n;
bool ds[N];
int p[N],d[N];
PII kol[2*N];

void Oblicz(){
    int b=0,e=-1;
    int sum = 0;LL obc=0;
    FOR(i,1,n){
        sum+=p[i]-d[i];
        while(b<=e && kol[e].ST>sum)
            --e;
        kol[++e]=MP(sum,i);
    }
    if(kol[b].ST>=0) ds[1]= true;
    FOR(i,2,n){
        if(kol[b].ND==i-1) b++;
        obc+=p[i-1]-d[i-1];
        LL c=sum+obc;
        while(b<=e && kol[e].ST-obc>sum)
            --e;
        kol[++e]=MP(c,LL(i-1));
        if(kol[b].ST-obc>=0) ds[i]= true;
    }
}

void Solve(){
    memset(ds,false,sizeof(ds));
    Oblicz();
    reverse(&d[1],&d[n+1]);
    reverse(&p[2],&p[n+1]);
    reverse(&ds[2],&ds[n+1]);
    Oblicz();
    reverse(&ds[2],&ds[n+1]);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n)
        scanf("%d%d",&p[i],&d[i]);
    Solve();
    FOR(i,1,n)
        if(ds[i]) puts("TAK");
        else puts("NIE");
    return 0;
}
