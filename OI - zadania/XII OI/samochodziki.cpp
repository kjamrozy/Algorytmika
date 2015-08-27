#include <cstdio>
#include <set>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;

const int N=100001,P=500001,INF=1000000001;

int samo[N];

struct cmp{
    bool operator()( int*  a,int*  b){
        return (*a==*b) ? a>b : (*a)>(*b);
    }
};

int n,k,p,plan[P],czas[P],last[N],res;
set<int*,cmp> podloga;

void Solve(){
    res=0;
    FOR(i,1,p){
        if(SIZE(podloga)<k){
            if(podloga.find(&samo[plan[i]])!=podloga.end()){
                podloga.erase(&samo[plan[i]]);
            }else ++res;
            samo[plan[i]]=czas[i];
            podloga.insert(&samo[plan[i]]);
        }else{
            if(podloga.find(&samo[plan[i]])!=podloga.end()){
                podloga.erase(&samo[plan[i]]);
                samo[plan[i]]=czas[i];
                podloga.insert(&samo[plan[i]]);
            }else{
                ++res;
                podloga.erase(*podloga.begin());
                samo[plan[i]]=czas[i];
                podloga.insert(&samo[plan[i]]);
            }
        }
    }
    printf("%d",res);
}

int main(){
    scanf("%d%d%d",&n,&k,&p);
    FOR(i,1,p)
        scanf("%d",&plan[i]);
    FOR(i,1,n) last[i]=INF;
    FORD(i,p,1){
        czas[i]=last[plan[i]];
        last[plan[i]]=i;
    }
    Solve();
    return 0;
}
