#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second

using namespace std;

typedef vector<int> VI;

#define MAXM 1000001

int n,m;
VI l[MAXM];

int BinSearch(VI& r,int val){
    if(SIZE(r)==0) return -1;
    else if(r[SIZE(r)-1]<=val) return -1;
    int a=0,b=SIZE(r)-1;
    while(a!=b){
        int c=(a+b)/2;
        if(r[c]<=val)
            a=c+1;
        else b=c;
    }
    return r[b];
}

int main(){
    scanf("%d",&m);
    FOR(i,1,m){
        int v;
        scanf("%d",&v);
        l[v].PB(i);
    }
    scanf("%d",&n);
    REP(i,n){
        int r,v=-1;
        scanf("%d",&r);
        bool ok=true;
        REP(j,r){
            int s;
            scanf("%d",&s);
            v=BinSearch(l[s],v);
            if(v==-1){
                ++j;
                ok=false;
                for(;j<r;++j){
                    int t;
                    scanf("%d",&t);
                }
            }
        }
        if(ok) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
