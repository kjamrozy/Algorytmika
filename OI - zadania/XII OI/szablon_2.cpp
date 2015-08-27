#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define REP(x,e) for(int x=0;x<e;++x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;

#define MAXN 500002

char napis[MAXN];
int pre[MAXN+1];

vector<int> prefsuf;

#define KMPH(z) while(k>0 && z[k]!=napis[q]) k=pre[k]; if(z[k]==napis[q]) ++k;

void Prefsuf(){
    int q,k=0;
    pre[1]=0;
    for(q=1;napis[q];++q){
        KMPH(napis);
        pre[q+1]=k;
    }
    int ps=0;
    k=strlen(napis);
    while(k>0)
        ++ps,k=pre[k];
    prefsuf.resize(ps);
    k=strlen(napis);
    FORD(i,ps-1,0){
        prefsuf[i]=k;
        k=pre[k];
    }
}

bool CzySzablon(int n){
    string str=napis;
    str=str.substr(0,n);
    int q,m,k=0;
    int last=-1;
    bool wyst[MAXN];
    REP(i,strlen(napis))
        wyst[i]=0;
    for(q=0;napis[q];++q){
        KMPH((str.c_str()));
        if(k==n){
            wyst[q-str.size()+1]=1;
            k=pre[k];
        }
    }
    for(q=0;q<strlen(napis);++q){
        if(wyst[q])
            last=q;
        if(q-last+1>n)
            return false;
    }
    return true;
}

int main(){
    assert(scanf("%s",napis));
    Prefsuf();
    int m=1;
    FOREACH(it,prefsuf)
        if(*it>=m)
        if(CzySzablon(*it)){
           printf("%d",*it);
           break;
        }else{
            m<<=1;
        }
    return 0;
}
