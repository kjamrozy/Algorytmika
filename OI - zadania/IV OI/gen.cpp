#include <iostream>
#include <cstdio>
#include <algorithm>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define PB push_back
#define SIZE(x) ((int)(x).size())
#define MP make_pair

const int N=10001,ALF=26,L=101,INF=1000000001;

int n,w[L][L],s[L][L],gen[ALF][ALF];
char reg[4],txt[L+1];

int Sklej(int a,int b){
    int res=0;
    REP(i,ALF)
        REP(j,ALF)
            if(a&(1<<i) && b&(1<<j))
                res|=gen[i][j];
    return res;
}

void Ans(){
    int super='S'-'A';
    super=1<<super;
    scanf("%s",txt);
    int l=strlen(txt);
    REP(i,l)
        w[i][i]=1<<(txt[i]-'A');
    FOR(i,1,l-1)
        FOR(j,0,l-1-i){
            w[j][j+i]=0;
            FOR(k,0,i-1){
                w[j][j+i]|=Sklej(w[j][j+k],w[j+k+1][j+i]);
            }
        }
        if(w[0][0]&super) s[0][0]=1;
        else s[0][0]=INF;
    FOR(i,1,l-1){
        s[0][i]=INF;
        if(w[0][i]&super) s[0][i]=1;
        else FOR(j,0,i-1){
            if(w[i-j][i]&super)
                if(1+s[0][i-j-1]<s[0][i]) s[0][i]=1+s[0][i-j-1];
        }
    }
    if(s[0][l-1]==INF) puts("NIE");
    else printf("%d\n",s[0][l-1]);
}

int main(){
    scanf("%d",&n);
    REP(i,n){
        scanf("%s",reg);
        gen[reg[1]-'A'][reg[2]-'A']|=1<<(reg[0]-'A');
    }
    int k;scanf("%d",&k);
    REP(i,k) Ans();
    return 0;
}
