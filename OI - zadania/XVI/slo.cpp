#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;x++)
#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define ALL(c) (c).begin(),(c).end()
#define VAR(v,n) __typeof(n) v = (n)
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef pair<int,LL> PIL;
int n,mn;

PIL cykle[1000010];
PII minima[1000010];

template <class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e,E d = E()){
        g[b].PB(Ed(d,e));
    }
    int c;
    void Cykle(int s){
        g[s].c=c;
        ++cykle[c].ST;
        cykle[c].ND+=g[s].m;
        if(minima[c].ST>g[s].m){
            minima[c].ST=g[s].m;
            minima[c].ND=s;
        }
        int v=g[s][0].v;
        while(g[v].c==-1){
            g[v].c=c;
            ++cykle[c].ST;
            cykle[c].ND+=g[v].m;
            if(minima[c].ST>g[v].m){
                    minima[c].ST=g[v].m;
                    minima[c].ND=v;
            }
            v=g[v][0].v;
        }
    }
    LL wariant1(int c){
        return (cykle[c].ST-2)*g[minima[c].ND].m+cykle[c].ND;
    }
    LL wariant2(int c){
        return 2*(g[mn].m+g[minima[c].ND].m)+(cykle[c].ST-1)*g[mn].m+cykle[c].ND-g[minima[c].ND].m;
    }
    LL Ustawiaj(){
        LL wynik=0;
        REP(i,SIZE(g)){
            minima[i].ST=1000000001; /// OK
        }
        c=0;
        REP(i,SIZE(g)) if(g[i].c==-1) /// OK
        {
            Cykle(i); /// OK
            ++c; /// OK
        }
        REP(i,c){
            wynik+= (cykle[i].ST>1) ? min(wariant1(i),wariant2(i)) : 0; /// SEEMS LEGIT
        }
        return wynik;
    }
};

struct Vs{
    int m;
    int c;
    Vs() : c(-1) {}
};

struct Es{
};

int m1[1000010];

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> slonie(n);
    int pomw=100000001;
    REP(i,n){
        scanf("%d",&slonie.g[i].m);
        if(pomw>slonie.g[i].m){
            pomw=slonie.g[i].m;
            mn=i;
        }
    }
    REP(i,n)
        scanf("%d",&m1[i]);
    REP(i,n){
        int m2;
        scanf("%d",&m2);
        slonie.EdgeD(m1[i]-1,m2-1);
    }
    printf("%lld",slonie.Ustawiaj());
    return 0;
}
