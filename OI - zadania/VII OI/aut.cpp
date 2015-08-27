#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

typedef pair<int,int> PII;

const int N = 10001;

int perm[N],pot[1001],licz[N],all[N];
bool wyst[1001],vs[N];
int n,pi,pm,e;

void Prepare(){
    pot[0]=1;
    wyst[1]=true;
    int x=1;
    while(!wyst[pot[x]=(pot[x-1]<<1)%1000])
        wyst[pot[x++]]=true;;
    pi=x;
    FOR(i,1,x)
        if(pot[i]==pot[pi]){
            pm=i;
            break;
        }
}

int Pot(int x){
    if(x>pi){
        int res=pot[pi];
    FOR(i,1,(x-pi)%(pi-pm)){
        res<<=1;
        res%=1000;
    }
        return res;
    }else return pot[x];
}

int GCD(int x, int y) {
    while (y) swap(x %= y, y);
    return x;
}

int Zlicz(int x){
    int l=1;
    vs[x]=true;
    int v=perm[x];
    while(!vs[v]){
        ++l;vs[v]=true;
        v=perm[v];
    }
    return l;
}

void Cykle(){
    FOR(i,1,n)
        if(!vs[i])
            ++licz[Zlicz(i)];
}

int Solve(){
    Cykle();
    int grom=0;
    e=-1;
    FOR(i,1,n)
        if(licz[i])
            all[++e]=i;
    FOR(i,0,e){
        if(all[i]%2==0) return 0;
        grom+=licz[all[i]]*(((all[i]*(all[i]-1))/2)/all[i]);
        FOR(j,i+1,e){
            grom+=licz[all[i]]*licz[all[j]]*GCD(all[i],all[j]);
        }
        grom+=all[i]*((licz[all[i]]*(licz[all[i]]-1))/2);
    }
    return Pot(grom);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n)
        scanf("%d",&perm[i]);
    Prepare();
    printf("%d\n",Solve());
    return 0;
}
