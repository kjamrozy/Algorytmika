#include <cstdio>
#include <set>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define SIZE(x) ((int)(x).size())
#define MP make_pair
#define PB push_back

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef long long LL;

const int N = 1000005;

int n,p,res,od[N],ndoj[N],najopt[N],c[N];
//od[i] - odleglosc stacji i od pkt docelowego
//ndoj[i] numer najblizszej stacji do ktorej przy pelnym baku nie da sie dojechac z stacji i

VPII zap[N];//pomocnicza tablica przy przetwarzaniu zapytan offline

struct cmp{
    bool operator()(const int& a,const int& b){
        return a>b;
    }
};

set<int,cmp> pula;//sluzy do zapytan offline

int Bin(int x){
    if(od[x]<=p) return n+2;//skoro da sie dojechac do konca to wszedzie sie da
    if(od[x]-od[n]<=p) return n+1;
    int a=x+1,b=n;
    while(a!=b){
        int c=(a+b)/2;
        if(od[x]-od[c]<=p) a=c+1;
        else b=c;
    }
    return a;
}

void Init(){
    memset(najopt,-1,sizeof(najopt));
    FORD(i,n-1,1)
        od[i]+=od[i+1];
    FOR(i,1,n)
        ndoj[i]=Bin(i);
    FOR(i,1,n){
        if(SIZE(pula)>0){
            while(*pula.begin()>c[i]){
                int v=*pula.begin();
                FOREACH(it,zap[v]){
                    if(it->ND>i)
                        najopt[it->ST]=i;
                }
                zap[v].clear();
                pula.erase(v);
            }
        }
        pula.insert(c[i]);
        zap[c[i]].PB(MP(i,ndoj[i]));
    }
}

void Jedz(int nr,int wbaku){
    if(nr==n+1) return;
    else if(najopt[nr]!=-1){
        res+=c[nr]*max(0,(od[nr]-od[najopt[nr]]-wbaku));
        wbaku-=od[nr]-od[najopt[nr]];
        Jedz(najopt[nr],max(0,wbaku));
    }else{
        if(od[nr]<=p){
            res+=(od[nr]-wbaku)*c[nr];
            return;
        }
        res+=(p-wbaku)*c[nr];
        Jedz(nr+1,p-(od[nr]-od[nr+1]));
    }
}

int main(){
    scanf("%d%d",&p,&n);
    FOR(i,1,n)
        scanf("%d%d",&c[i],&od[i]);
    Init();
    Jedz(1,0);
    printf("%d",res);
    return 0;
}
