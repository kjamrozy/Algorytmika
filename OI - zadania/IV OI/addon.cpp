#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <set>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define SIZE(x) ((int)(x).size())

const int N = 10001;

int n,wys=N;

int stab[N];
bool wyk[2*N];

vector<int> res;
set<int> worek;

void Solve(){
    int nast=2*stab[1];
    wys=stab[1];
    res.PB(stab[1]);
    FOR(i,2,n){//sprawdzamy kazda z wysokosci, az w koncu jakas bedzie zla
        if(stab[i]>nast)
                break;
        if(stab[i]<nast) res.PB(stab[i]);
        FOREACH(it,res) worek.insert(*it+stab[i]);
        if(stab[i]==nast){
            nast=*worek.begin();
            worek.erase(*worek.begin());
        }
        wys=stab[i];
    }
}
int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d",&stab[i]);
        wyk[stab[i]]=true;
    }
    Solve();
    printf("%d\n",wys);
    FOREACH(it,res)
        printf("%d\n",*it);
    return 0;
}
