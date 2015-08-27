#include <algorithm>
#include <cstdio>
#include <vector>
#include <memory.h>
#include <set>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define ST first
#define ND second
#define PB push_back

const int N = 100001;

int n,res;

vector<int> g[N];
int st[N];
bool winers[N],walka[N];

struct cmp{
    bool operator()(const int& a,const int& b){
        return (st[a]==st[b]) ? a<b : st[a]<st[b];
    }
};

void Solve(){
    set<int,cmp> kol;
    FOR(i,1,n)
        if(!walka[i])
            FOREACH(it,g[i])
                walka[*it]=true;
    int ind=-1;
    FOR(i,1,n)
        if(!walka[i]){
            ind=i;
            break;
        }
    FOR(i,1,n)
        kol.insert(i);
    kol.erase(ind);
    FOREACH(it,g[ind])
        if(kol.find(*it)!=kol.end()){
            kol.erase(*it);
            ++st[*it];
            kol.insert(*it);
        }
    winers[ind]=true;
    res=1;
    while(!kol.empty() && st[*kol.begin()]<res){
        ++res;
        int v=*kol.begin();
        winers[v]=true;
        kol.erase(v);
        FOREACH(it,g[v]){
            if(kol.find(*it)!=kol.end()){
            kol.erase(*it);
            ++st[*it];
            kol.insert(*it);
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        int t;scanf("%d",&t);
        REP(j,t){
            int v;scanf("%d",&v);
            g[i].PB(v);
        }
    }
    Solve();
    printf("%d ",res);
    FOR(i,1,n)
        if(winers[i])
            printf("%d ",i);
    return 0;
}
