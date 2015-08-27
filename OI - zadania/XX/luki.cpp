#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x<=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define SIZE(x) ((int)(x).size())
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back

#define MAXN 300002

int n;
int r[MAXN];
vector<int> v[MAXN];

int Koszt(int a,int p,int k){
    int koszt=-k+SIZE(v[a])-1;
    REP(i,SIZE(v[a]))
        if(v[a][i]!=p)
            koszt+=Koszt(v[a][i],a,k);
    return max(0,koszt);
}

bool CzyStarczy(int k){
    int sum=0;
    REP(i,SIZE(v[0]))
        sum+=Koszt(v[0][i],0,k)+1;
    return sum<=k;
}

int Solve(){
    if(SIZE(v[0])==0) return 0;
    int a=1,b=n;
    while(a!=b){
        int c=(a+b)/2;
        if(CzyStarczy(c))
            b=c;
        else
            a=c+1;
    }
    return a;
}

int main(){
    scanf("%d",&n);
    REP(i,n-1){
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        v[t1-1].PB(t2-1);
        v[t2-1].PB(t1-1);
    }
    printf("%d",Solve());
    return 0;
}
