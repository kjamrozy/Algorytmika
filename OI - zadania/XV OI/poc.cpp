#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int INF = 1000000005;

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
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

#define MAXN 1002
#define MAXL 102
#define MAXM 100002
#define ILE MAXM+5

LL BASE=1000000007,hash=57;
int n,l,m,ile,res[MAXN],w[16*MAXM];
map< LL , int > czas;
map<LL,VI> listy;
int ind[MAXN];
map<LL , vector< pair<PII,int> > > zap;
LL hpoc[MAXN],pot[MAXL];
char poc[MAXN][MAXL];

void insert(int a,int c){
    int va=ile+a;
    w[va]+=c;
    while(va!=0){
        va/=2;
        w[va]=max(w[va*2],w[va*2+1]);
    }
}

int query(int a,int b){
    int va=ile+a,vb=ile+b;
    int res= (va!=vb) ? max(w[va],w[vb]) : w[va];
    while(va/2!=vb/2){
        if(va%2==0) res=max(res,w[va+1]);
        if(vb%2==1) res=max(res,w[vb-1]);
        va/=2;vb/=2;
    }
    return res;
}

void Init(){
    pot[0]=1;
    FOR(i,1,l+1)
        pot[i]=pot[i-1]*hash;
    FOR(i,1,n){
        FOR(j,1,l)
            hpoc[i]=(hpoc[i]+pot[j-1]*int(poc[i][j]))%BASE;
        if(hpoc[i]<0) hpoc[i]+=BASE;
    }
    FOR(i,1,n){
        ind[i]=res[i]=1;
    }
}

void Zamiana(int p1,int w1,int p2,int w2,int mom){
    if(p1!=p2){
        (zap[hpoc[p1]]).PB(MP(MP(ind[p1],SIZE(listy[hpoc[p1]])), p1 ));
        listy[hpoc[p1]].PB(--czas[hpoc[p1]]);
        (zap[hpoc[p2]]).PB(MP(MP(ind[p2],SIZE(listy[hpoc[p2]])), p2 ));
        listy[hpoc[p2]].PB(--czas[hpoc[p2]]);
    }else{
        (zap[hpoc[p1]]).PB(MP(MP(ind[p1],SIZE(listy[hpoc[p1]])), p1 ));
        listy[hpoc[p1]].PB(--czas[hpoc[p1]]);
    }
    hpoc[p1]-=(pot[w1-1]*int(poc[p1][w1]))%BASE;
    hpoc[p1]+=(pot[w1-1]*int(poc[p2][w2]))%BASE;
    hpoc[p2]-=(pot[w2-1]*int(poc[p2][w2]))%BASE;
    hpoc[p2]+=(pot[w2-1]*int(poc[p1][w1]))%BASE;
    hpoc[p1]%=BASE;
    hpoc[p2]%=BASE;
    if(hpoc[p1]<0) hpoc[p1]+=BASE;
    if(hpoc[p2]<0) hpoc[p2]+=BASE;
    if(p1!=p2){
        listy[hpoc[p1]].PB(++czas[hpoc[p1]]);
        ind[p1]=SIZE(listy[hpoc[p1]]);
        listy[hpoc[p2]].PB(++czas[hpoc[p2]]);
        ind[p2]=SIZE(listy[hpoc[p2]]);
    }else{
        listy[hpoc[p1]].PB(++czas[hpoc[p1]]);
        ind[p1]=SIZE(listy[hpoc[p1]]);
    }
    swap(poc[p1][w1],poc[p2][w2]);
}

void Aktualizuj(){
    FOR(i,1,n){
        ind[i]=1;
    }
    FOR(i,1,n)
        ++czas[hpoc[i]];
    FOREACH(it,czas)
        listy[it->ST].PB(it->ND);
}

void Aktualizuj2(){
    FOR(i,1,n){
        (zap[hpoc[i]]).PB(MP(MP(ind[i],SIZE(listy[hpoc[i]])), i ));
    }
}

void init(int s){
    ile=1;
    while(ile/2<s) ile<<=1;
    FOR(i,1,2*ile) w[i]=0;
}

void Solve(){
    FOREACH(it,zap){
        init(SIZE((it->ND))+1);
        int j=1;
        FOREACH(it2,listy[it->ST]){
            insert(j,*it2);
            ++j;
        }
        FOREACH(it2,((it->ND))){
            res[it2->ND]=max(res[it2->ND],query(it2->ST.ST,it2->ST.ND));
        }
    }
    FOR(i,1,n)
        printf("%d\n",res[i]);
}

int main(){
    scanf("%d%d%d",&n,&l,&m);
    FOR(i,1,n)
        scanf("%s",poc[i]+1);
    Init();
    Aktualizuj();
    FOR(i,1,m){
        int p1,w1,p2,w2;
        scanf("%d%d%d%d",&p1,&w1,&p2,&w2);
        Zamiana(p1,w1,p2,w2,i);
    }
    Aktualizuj2();
    Solve();
    return 0;
}
