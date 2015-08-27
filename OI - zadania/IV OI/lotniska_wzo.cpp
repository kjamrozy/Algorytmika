#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

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

typedef pair<int,int> PII;
typedef vector<PII> VPII;

const int N = 501;

int stopnie[N],kol[N][N],n,b[N],e[N];
bool kraw[N][N];

bool cmp(const int& a,const int& b){
    return stopnie[a]>stopnie[b];
}

int main(){
    memset(b,0,sizeof(b));
    memset(e,-1,sizeof(e));
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d",&stopnie[i]);
        kol[stopnie[i]][++e[stopnie[i]]]=i;
    }
    FORD(i,n,1){
        while(b[i]<=e[i]){
            int x=kol[i][b[i]++],m=i;
            VPII pom;
            int j=i;
            while(m--){
            while(!(b[j]<=e[j]))
                --j;
                int y=kol[j][b[j]++];
                pom.PB(MP(y,j));
                printf("%d %d\n",x,y);
            }
            FOREACH(it,pom)
                kol[it->ND-1][++e[it->ND-1]]=it->ST;
        }
    }
    return 0;
}
