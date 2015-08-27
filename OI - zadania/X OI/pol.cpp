#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v =(n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define SIZE(x) ((int)(x).size())

#define MAXK 101
#define MAXN 101
#define MAXQ 10001

const int INF = 1000000001;

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef pair<PII,int> PPIII;

int n,m,q,maxk;
int M[MAXN][MAXN][MAXK],D[MAXN][MAXN][MAXK];

struct{
    int c,d,k;
}queries[MAXQ];

void Merge(int* p1,int* p2){
    int res[MAXK];
    int a=0,b=0;
    REP(i,maxk){
            if(p1[a]<p2[b])
                res[i]=p1[a++];
            else res[i]=p2[b++];
    }
    REP(i,maxk){
        p1[i]=res[i];
    }
}

struct El{
    int a,b,w;
    El(int x,int y,int z) : a(x),b(y),w(z) {}
};

struct cmp{
    bool operator()(const El& a,const El& b){
        return  (a.w==b.w) ? ( (a.b==b.b) ? a.a<b.a : a.b < b.b  ) : a.w<b.w;
    }
};

void Add(int* p1,int* p2){
    if(p1[0]==INF || p2[0]==INF){
        REP(i,maxk) p1[i]=INF;
    } else{
    int res[MAXK];
        set<El,cmp> kopiec;
        REP(i,maxk){
            int w=p1[i]+p2[0];
            if(w>INF) w=INF;
            kopiec.insert( El(i,0,w));
        }
        REP(i,maxk){
            El x=*(kopiec.begin());
            kopiec.erase(kopiec.find(x));
            if(x.b+1<maxk)
                kopiec.insert(El(x.a,x.b+1, p1[x.a]+p2[x.b+1] ));
            res[i]=x.w;
        }
    REP(i,maxk)
        p1[i]=res[i];
    }
}

void Multi(int* p1){
    int res[MAXK];int pom[MAXK];
    REP(i,maxk){
        pom[i]=p1[i];
        res[i]=INF;
    }
    REP(i,maxk){
        Merge(res,pom);
        Add(pom,p1);
    }
    REP(i,maxk)
        p1[i]=res[i];
}

void Solve(){
    FOR(l,1,n){
        FOR(i,1,n)
            FOR(j,1,n)
                REP(k,maxk)
                    D[i][j][k]=M[i][j][k];
        Multi(M[l][l]);
        FOR(i,1,n){
            FOR(j,1,n)
                if(!(i==l && j==l)){
                    int temp[MAXK];
                    REP(k,maxk)
                        temp[k]=D[i][l][k];
                    Add(temp,D[l][j]);
                    Merge(M[i][j],temp);
                    Add(temp,M[l][l]);
                    Merge(M[i][j],temp);
                }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    maxk=MAXK;
    FOR(i,1,n)
        FOR(j,1,n)
                D[i][j][0]=M[i][j][0]=INF;
    REP(i,m){
        int a,b,d;
        scanf("%d%d%d",&a,&b,&d);
        M[a][b][0]=d;
    }
    FOR(i,1,n)
        FOR(j,1,n)
            REP(k,maxk-1)
                D[i][j][k+1]=M[i][j][k+1]=INF;
    Solve();
    scanf("%d",&q);
    REP(i,q){
        int c,d,k;
        scanf("%d%d%d",&queries[i].c,&queries[i].d,&queries[i].k);
        if(M[queries[i].c][queries[i].d][queries[i].k-1]!=INF){
            printf("%d\n",M[queries[i].c][queries[i].d][queries[i].k-1]);
        }else printf("-1\n");
    }
    return 0;
}
