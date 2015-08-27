#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second

typedef long long LL;
typedef vector<long long> VLL;

LL m,d;
int n;
VLL taks;

bool cmp(const LL& a,const LL& b){
    return a>b;
}

int main(){
    scanf("%lld%lld%d",&m,&d,&n);
    REP(i,n){
        LL c;
        scanf("%lld",&c);
        taks.PB(c);
    }
    LL minimalna=1000000000000000001ll;
    int ind=-1;
    REP(i,n){
        if(taks[i]>=m-d && taks[i]<minimalna){
            minimalna=taks[i];
            ind=i;
        }
    }
    if(ind==-1){
        puts("0");
    }else{
        swap(taks[ind],taks[n-1]);
        taks.pop_back();
        sort(taks.begin(),taks.end(),cmp);
        LL poz=0;
        REP(i,n-1){
            if(minimalna>=m-d+2*(d-poz)){
                printf("%d",i+1);
                return 0;
            }
            if(taks[i]>=2*(d-poz)){
                if(taks[i]>=m-d+2*(d-poz)){
                    printf("%d",i+1);
                }else{
                    printf("%d",i+2);
                }
                return 0;
            }else if(taks[i]>=d-poz){
                poz+=taks[i]-(d-poz);
            }else{
                puts("0");
                return 0;
            }
        }
        if(minimalna>=m-d+2*(d-poz)){
                printf("%d",n);
                return 0;
        }
        puts("0");
    }
    return 0;
}
