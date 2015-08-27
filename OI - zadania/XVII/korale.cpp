#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;x++)
#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)
#define PB push_back

typedef long long LL;
typedef vector<int> VI;

int n;
LL hash1[200002];
LL hash2[200002];
int ciag[200002];
LL hash=500029;
LL BASE=1000000007;
LL p[200002];

LL norm(int b,int e){
    LL p1=(hash1[b]-hash1[e+1]*p[e-b+1])%BASE;
    if(p1<0) p1+=BASE;
    return p1;
}

LL odw(int b,int e){
    LL p1;
    if(b!=0){
        p1=(hash2[e]-hash2[b-1]*p[e-b+1])%BASE;
        if(p1<0) p1+=BASE;
    }else{
        p1=hash2[e]%BASE;
        if(p1<0) p1+=BASE;
    }
    return p1;
}

int main(){
    scanf("%d",&n);
    REP(i,n){
        scanf("%d",&ciag[i]);
    }
    p[0]=1;
    FOR(i,1,n+1)
        p[i]=(p[i-1]*hash)%BASE;
    hash1[n-1]=ciag[n-1];
    FORD(i,n-2,0){
        hash1[i]=(hash1[i+1]*hash+ciag[i])%BASE;
    }
    hash2[0]=ciag[0];
    FOR(i,1,n-1){
        hash2[i]=(hash2[i-1]*hash+ciag[i])%BASE;
    }
    set<pair<LL,LL> > unikalne;
    VI res;
    int akt=0,ile=0;
    FOR(i,1,n){
        FOR(j,0,n/i-1){
            LL p1=norm(j*i,j*i+(i-1));
            LL p2=odw(j*i,j*i+(i-1));
            unikalne.insert(make_pair(min(p1,p2),max(p1,p2)));
        }
        if(unikalne.size()>akt){
            res.clear();
            res.PB(i);
            ile=1;
            akt=unikalne.size();
        }else{
            if(akt==unikalne.size()){
                ++ile;
                res.PB(i);
            }
        }
        unikalne.clear();
    }
    printf("%d %d \n",akt,ile);
    FOREACH(i,res)
        printf("%d ",*i);
    return 0;
}
