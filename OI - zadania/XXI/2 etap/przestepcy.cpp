///Karol Jamrozy
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>

#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x) ///
#define FOR(x,b,e) for(int x=b;x<=e;++x) ///
#define FORD(x,b,e) for(int x=b;x>=e;--x) ///
#define VAR(v,n) __typeof(n) v = (n) ///
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i) ///
#define PB push_back ///
#define ST first ///
#define ND second ///
#define MP make_pair ///
#define SIZE(x) ((int)(x).size()) ///

typedef pair<int,int> PII; ///
typedef vector<int> VI; ///
typedef long long LL; ///

#define f1(x,y) max(x,y)
#define f2(x,y) max(x,y)
#define wiele(x,n) (x)

const int PUSTY = 0,MAX_LOG_N = 33,N = 1000001,K = 1000001;

int n,k,ile,m,l,res,trasawp[K],koldom[N];
//vector<bool> vs(N,0);
bool vs[N],vs2[N];


int last[K],_next[K];
int kon[N];


PII lw[K];

int main(){
    scanf("%d%d",&n,&k);///
    FOR(i,1,n)///
        scanf("%d",&koldom[i]);///
    scanf("%d%d",&m,&l);///
    FOR(i,1,m)///
        scanf("%d",&trasawp[i]);///
    FOR(i,1,k)///
        lw[i]=MP(-1,-1);///
    memset(_next,-1,sizeof(_next));
    FOR(i,1,m-1){
        _next[trasawp[i]]=trasawp[i+1];
    }

    memset(last,-1,sizeof(last));
    memset(kon,-1,sizeof(kon));
    FOR(i,1,n){
        if(koldom[i]==trasawp[m]){
            kon[i]=i;
        }
    }
    FORD(i,n,1){
        if(_next[koldom[i]]!=-1 && last[_next[koldom[i]]]!=-1){
            kon[i]=kon[last[_next[koldom[i]]]];
        }
        if(last[trasawp[1]]!=-1){
            lw[koldom[i]].ST=kon[last[trasawp[1]]];
        }
        last[koldom[i]]=i;
    }


        FOR(i,1,l)
        scanf("%d",&trasawp[i]);///
    memset(_next,-1,sizeof(_next));
    FOR(i,1,l-1){
        _next[trasawp[i]]=trasawp[i+1];
    }

    memset(last,-1,sizeof(last));
    memset(kon,-1,sizeof(kon));
    FOR(i,1,n){
        if(koldom[i]==trasawp[l]){
            kon[i]=i;
        }
    }
    FOR(i,1,n){
        if(_next[koldom[i]]!=-1 && last[_next[koldom[i]]]!=-1){
            kon[i]=kon[last[_next[koldom[i]]]];
        }
        if(last[trasawp[1]]!=-1){
            lw[koldom[i]].ND=kon[last[trasawp[1]]];
        }
        last[koldom[i]]=i;
    }

    sort(&lw[1],&lw[k+1]);
//        /**/
//    FOR(i,1,k)
//        cout<<lw[i].ST<<" "<<lw[i].ND<<endl;
//    /**/

    int wsk=1;///
    FOR(i,1,k){///
        if(lw[i]==MP(-1,-1)) continue;
        if(lw[i].ST!=-1 && lw[i].ND!=-1 &&  lw[i].ST<=lw[i].ND){///
            wsk=max(wsk,lw[i].ST);///
            while(wsk<=lw[i].ND){///
                if(koldom[wsk]==trasawp[l]){ vs[wsk]=true;///
                    ++res;///
                }
                ++wsk;///
            }///
            if(wsk>n) break;///
        }
    }

    printf("%d\n",res);///
    FOR(i,1,n)///
        if(vs[i])///
            printf("%d ",i);///
    return 0;
}
