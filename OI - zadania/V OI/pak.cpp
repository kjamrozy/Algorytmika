#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <memory.h>

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
#define MP make_pair

typedef vector<int> VI;

const int N  = 10005,Q=1005;

VI pudelka[Q];
int kon[Q];

int n,q;

bool cmp(const int& a,const int& b){
    return a>b;
}

int main(){
    scanf("%d",&n);
    REP(i,n){
        int r,w;scanf("%d%d",&r,&w);
        pudelka[r].PB(w);
    }
    int maxq=0;
    scanf("%d",&q);
    REP(i,q){
        int r,il;scanf("%d%d",&r,&il);
        maxq=max(r,maxq);
        kon[r]=il;
    }
    int res=0;
    FOR(i,0,maxq){
        sort(pudelka[i].begin(),pudelka[i].end(),cmp);
        while(kon[i]){
            if(!SIZE(pudelka[i])){
                puts("NIE");
                return 0;
            }
            res+=pudelka[i].back();
            pudelka[i].pop_back();
            --kon[i];
        }
        while(SIZE(pudelka[i])>=2){
            int w=pudelka[i].back();
            pudelka[i].pop_back();
            w+=pudelka[i].back();
            pudelka[i].pop_back();
            pudelka[i+1].PB(w);
        }
    }
    printf("%d",res);
    return 0;
}
