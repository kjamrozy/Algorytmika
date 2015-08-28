//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x) ///
#define FOR(x,b,e) for(int x=b;x<=e;++x) ///
#define FORD(x,b,e) for(int x=b;x>=e;--x) ///
#define VAR(v,n) __typeof(n) v =(n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef long long LL;
typedef vector<PII> VPII;

const int N = 1000005,Q=27,K=1000007;

int n,q;
int wys[N],wyn[N],b[2],e[2],
res[K];

PII kol[2][2*N];

/// ///
void PopKol(bool kt,int x){
    if(b[kt]<=e[kt] && kol[kt][b[kt]].ND==x)
        ++b[kt];
}

/// ///
int KolIns(bool kt,int wart,int x){
    while(b[kt]<=e[kt] && kol[kt][e[kt]].ST>wart)
        --e[kt];
    kol[kt][++e[kt]]=MP(wart,x);
}

int Ans(int k){
    if(res[k]==-1){
//        cout<<"Obliczam dla k="<<k<<endl;
        int lekka=0;
        wyn[n]=0;
        bool kt=0;
        b[0]=b[1]=0;
        e[0]=e[1]=-1;
//        cout<<0<<" ";
        KolIns(kt,wys[n],n);
        FORD(i,n-1,1){
//            cout<<"teraz dla i:"<<i<<endl;
//            if(b[kt]>e[kt]) cout<<"eeee?"<<endl;
            if(wys[i]>kol[kt][b[kt]].ST) wyn[i]=lekka;
            else wyn[i]=lekka+1;
//            cout<<kol[kt][b[kt]].ST<<endl;
            PopKol(kt,i+k);
            PopKol(!kt,i+k);
            if(lekka==wyn[i])
                KolIns(kt,wys[i],i);
            else KolIns(!kt,wys[i],i);
            if(b[kt]>e[kt]){//jezeli kolejka jest pusta
                b[kt]=0;
                e[kt]=-1;
                kt=!kt;
                lekka++;
            }
//            cout<<wyn[i]<<" ";//endl;
        }
//        cout<<endl<<endl;
        return res[k]=wyn[1];
    }else return res[k];
}



int main(){
    scanf("%d",&n);///
    FOR(i,1,n) scanf("%d",&wys[i]);///
    scanf("%d",&q);///
    memset(res,-1,sizeof(res));///
    FOR(i,1,q){///
        int a;scanf("%d",&a);///
        printf("%d\n",Ans(a));///
    }
    return 0;
}
