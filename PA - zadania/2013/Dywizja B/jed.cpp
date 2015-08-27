#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define ST first
#define ND second

typedef pair<int,int> PII;

#define MAXN 300001

int n;
int p1[MAXN+1],p2[MAXN+1],p3[MAXN+1];///permutacja odwrotna do tablic b1,b2,b3
PII w[MAXN];


int pos(int x){
    if(x<0)
        return (n-abs(x))%n;
    else return x%n;
}

bool cmp(PII a,PII b){
    return (a.ST==b.ST) ? ( (a.ND==b.ND) ? a<b : a.ND<b.ND ) : a.ST<b.ST;
}

bool r(PII a,PII b){
    return (a.ST==b.ST) && (a.ND==b.ND);
}

int main(){
    ios_base::sync_with_stdio(0);
//    scanf("%d",&n);
    cin>>n;
    REP(i,n){
        int t;
        cin>>t;
//        scanf("%d",&t);
        p1[t]=i;
    }
    REP(i,n){
        int t;
        cin>>t;
//        scanf("%d",&t);
        p2[t]=i;
    }
    REP(i,n){
        int t;
        cin>>t;
//        scanf("%d",&t);
        p3[t]=i;
    }

    int wynik=1;

    ///przygotowanie tablicy w
    FOR(i,1,n){
        w[i-1]=make_pair(pos(p2[i]-p1[i]),pos(p3[i]-p2[i]));
    }

    sort(&w[0],&w[n],cmp);

    int t=1;
    FOR(i,1,n-1){
        if(r(w[i],w[i-1]))
            ++t;
        else{
            wynik=max(wynik,t);
            t=1;
        }
    }

   wynik=max(wynik,t);
   cout<<wynik;
   //printf("%d",wynik);
}
