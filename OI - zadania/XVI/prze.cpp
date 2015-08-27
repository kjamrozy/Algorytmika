#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

#define ALL(c) (c).begin(),(c).end()
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
typedef pair<int,int> PII;
typedef vector<PII> VPII;

const int ALPH = 'z'-'a'+2;
const int HASZ = 'z'-'a'+1;
const int N = 405;

int n,m,d,pk,kk;

int kol[N*N*ALPH],od[N][N][ALPH],prev[N][N][ALPH];
vector< pair<char,int> > g[N],gt[N];
char lit[N][N],res[N*N+3];
int gpoz[N][ALPH];


void Do_kol(int a,int b,int c,int dis,int s){
    if(od[a][b][c]==-1){
        od[a][b][c]=dis;
        prev[a][b][c]=s;
        kol[kk++] = (a | (b << 9) | (c << 18));
    }
}

void Z_kol(int& a,int& b,int& c){
    int x = kol[pk++];
    a = x & 511;
    b = (x >> 9) & 511;
    c = x >> 18;
}

void Bfs(){
    REP(i,n) Do_kol(i,i,HASZ,0,-1);
    REP(i,n) REP(j,n) if(lit[i][j]) Do_kol(i,j,HASZ,1,-1);
    while(pk<kk){
        int a,b,c,dis;
        Z_kol(a,b,c);
        dis=od[a][b][c];
        if(c==HASZ){
            FOREACH(it,gt[a])
                Do_kol(it->ND,b,it->ST-'a',dis+1,a);}
        else{ FOR(i,gpoz[b][c],gpoz[b][c+1]-1)
            Do_kol(a,g[b][i].ND,HASZ,dis+1,b);}
    }
}

void Przetworz(int a,int b){
    int pocz=0,kon=od[a][b][HASZ]-1;
    res[kon+1]=0;
    while(pocz<kon){
        int p=prev[a][b][HASZ];
        int zn = res[pocz++]=res[kon--]=lit[p][b];
        b=p;
        zn-='a';
        a=prev[a][p][zn];
    }
    if(pocz==kon)
        res[pocz]=lit[a][b];
}

int main(){
    scanf("%d %d",&n,&m);
    REP(i,n) REP(j,n) REP(k,ALPH) od[i][j][k]=-1;
    REP(i,m){
        int a,b,c;
        char z[10];
        scanf("%d %d %s",&a,&b,z);
        --a;--b;
        lit[a][b]=z[0];
        g[a].PB(MP(z[0],b));
        gt[b].PB(MP(z[0],a));
    }
    REP(i,n){
        sort(ALL(g[i]));
        sort(ALL(gt[i]));
        int poz=-1,lg=SIZE(g[i]);
        REP(j,lg)
            while(poz<g[i][j].ST-'a')
                gpoz[i][++poz]=j;
        while(poz<=HASZ)
            gpoz[i][++poz]=lg;
    }
    Bfs();
    int last;scanf("%d%d",&d,&last);--last;
    REP(i,d-1){
        int doc;scanf("%d",&doc);--doc;
        if(od[last][doc][HASZ]==-1){
            printf("-1\n");
        }else{
            Przetworz(last,doc);
            printf("%d %s\n",od[last][doc][HASZ],res);
        }
        last=doc;
    }
    return 0;
}
