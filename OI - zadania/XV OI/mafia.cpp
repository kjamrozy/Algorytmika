#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;

const int N = 1000001;

int n,pnum,rmax,rmin,skl,l;
int cel[N],pord[N],sk[N],licz[N],liscie[N];
bool vs[N],vs1[N],zywy[N];
VI gv[N];

void Zaznacz(int x){
    vs[x]=true;++l;
    if(sk[x]<0) sk[x]=-2;
    if(!SIZE(gv[x])) liscie[skl]++;
    FOREACH(it,gv[x])
        if(!vs[*it])
            Zaznacz(*it);
}

void PostOrder(int x){
    if(!vs1[x]){
        vs1[x]=true;
        FOREACH(it,gv[x])
            PostOrder(*it);
        pord[++pnum]=x;
    }
}

int LiczMin(bool faza){
    FOR(i,0,pnum)
        zywy[pord[i]]=true;
    int j;
    if(faza)
        j=pnum;
    else j=0;
    FOR(i,0,pnum){
        if(zywy[pord[j]]){
            zywy[cel[pord[j]]]=false;
        }
        ++j;j%=pnum+1;
    }
    int res=0;
    FOR(i,0,pnum)
        if(!zywy[pord[i]]) ++res;
    return res;
}

void Naznacz(int x){
    sk[x]=-2;
    int next=cel[x];
    while(sk[next]==-1){
        sk[next]=-2;
        next=cel[next];
    }
    l=0;
    sk[next]=skl;
    next=cel[next];
    while(sk[next]==-2){
        sk[next]=skl;
        next=cel[next];
    }
    while(!vs[next]){
        Zaznacz(next);
        next=cel[next];
    }
    licz[skl]=l;
    if(l>1){
    pnum=-1;
    PostOrder(next);
    rmin+=min(LiczMin(0),LiczMin(1));
    }else{
        rmin+=1;
    }
    ++skl;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d",&cel[i]);
        gv[cel[i]].PB(i);
    }
    skl=0;
    FOR(i,1,n) sk[i]=-1;
    FOR(i,1,n)
        if(sk[i]==-1){
            Naznacz(i);
            if(licz[skl-1]>1)
                rmax+=min(licz[skl-1]-1,licz[skl-1]-liscie[skl-1]);
            else rmax+=1;
        }
    printf("%d %d",rmin,rmax);
    return 0;
}
