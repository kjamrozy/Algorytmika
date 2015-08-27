#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

const int N = 501;

int stopnie[N],kol[N],n;
bool kraw[N][N];

bool cmp(const int& a,const int& b){
    return stopnie[a]>stopnie[b];
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d",&stopnie[i]);kol[i]=i;
    }
    FOR(k,1,n){
        int i=1;
        sort(&kol[1],&kol[n+1],cmp);
        if(stopnie[kol[i]])
        FOR(j,1,n)
            if(i!=j && !kraw[kol[i]][kol[j]] && stopnie[kol[i]] && stopnie[kol[j]]){
                --stopnie[kol[i]];--stopnie[kol[j]];
                kraw[kol[i]][kol[j]]=kraw[kol[j]][kol[i]]=true;
                printf("%d %d\n",kol[i],kol[j]);
            }
    }
    return 0;
}
