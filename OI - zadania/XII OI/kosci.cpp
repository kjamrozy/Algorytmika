#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <cassert>

using namespace std;

#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define REP(x,e) for(int x=0;x<e;++x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define MP make_pair
#define ALL(c) (c).begin(),(c).end()
#define ST first
#define ND second
#define SIZE(x) ((int)(x).size())
#define PB push_back

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

const int N = 10001,M=10001;

VPII g[N];
PII kraw[M];
int out[N],n,m,k,ex;
bool res[M],vs[N];

bool Dfs(int s){
    vs[s]=true;
    if(out[s]<ex){
        ++out[s];
        return true;
    }
    REP(i,SIZE(g[s]))
        if(!vs[g[s][i].ST] && Dfs(g[s][i].ST)){
                g[g[s][i].ST].PB(MP(s,g[s][i].ND));
                swap(g[s][i],g[s][SIZE(g[s])-1]);
                g[s].pop_back();
                return true;
            }
    return false;
}

bool Szczesciarz(int x){
    memset(out,0,sizeof(out));
    FOR(i,0,n) g[i].clear();
    ex=x;
    FOR(i,1,m){
        memset(vs,false,sizeof(vs));
        if(out[kraw[i].ST]==x && out[kraw[i].ND]==x){
            if(!Dfs(kraw[i].ST)){
                if(!Dfs(kraw[i].ND))
                    return false;
                else --out[kraw[i].ND];
            }else --out[kraw[i].ST];
        }
        if(out[kraw[i].ST]<=out[kraw[i].ND]){
            ++out[kraw[i].ST];
            g[kraw[i].ST].PB(MP(kraw[i].ND,i));
            res[i]=1;
        }else {
            ++out[kraw[i].ND];
            g[kraw[i].ND].PB(MP(kraw[i].ST,i));
            res[i]=0;
        }
    }
    int maxx=0;
    FOR(i,1,n) maxx=max(maxx,out[i]);
    return true;
}

void Przetworz(){
    int check=0;
    FOR(i,1,n){
        check+=SIZE(g[i]);
        k=max(k,SIZE(g[i]));
        FOREACH(it,g[i])
            if(it->ST==kraw[it->ND].ST)
                res[it->ND]=0;
            else res[it->ND]=1;
    }
}

void Solve(){
    if(m==0){
        printf("0");
        return;
    }
    int a=1,b=m;
    while(a!=b){
        int c=(a+b)/2;
        if(Szczesciarz(c)) b=c;
        else a=c+1;
    }
    Szczesciarz(a);
    k=a;
    Przetworz();
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m)
        scanf("%d%d",&kraw[i].ST,&kraw[i].ND);
        Przetworz();
    Solve();
    printf("%d\n",k);
    FOR(i,1,m)
        printf("%d\n",res[i]);
    return 0;
}
