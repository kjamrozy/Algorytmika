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
#define MP make_pair
#define SIZE(x) ((int)(x.size()))

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;

const int BASE=1000000000,BD=9;

struct BigNum{
    #define REDUCE() while(len>1 && !cyf[len-1]) --len;

    int len,al;
    LL* cyf;
    BigNum(int v=0,int l=2) : len(1),al(l),cyf(new LL[l]){
        REP(x,l) cyf[x]=0;
        if((cyf[0]=v)>=BASE) przen(1);
    }
    BigNum(const BigNum& a) : len(a.len),al(a.len),cyf(new LL[a.len]){
        REP(x,a.len) cyf[x]=a.cyf[x];
    }
    ~BigNum(){
        delete cyf;
    }
    void Res(int l){
        if(l>al){
            LL* n = new LL[l=max(al*2,l)];
            REP(x,l) n[x] = (x>=al) ? 0 : cyf[x];
            delete cyf;
            cyf=n;
            al=l;
        }
    }
    void przen(int p) {
        int x = 0;
        for (; x < p || cyf[x] < 0 || cyf[x] >= BASE; x++) {
            Res(x + 2);
            if (cyf[x] < 0) {
                LL i = (-cyf[x] - 1) / BASE + 1;
                cyf[x] += i * BASE;
                cyf[x + 1] -= i;
            } else if (cyf[x] >= BASE) {
                LL i = cyf[x] / BASE;
                cyf[x] -= i * BASE;
                cyf[x + 1] += i;
            }
        }
        len = max(len, x + 1);
        REDUCE();
    }
    void operator*=(int a){
        REP(x,len) cyf[x]*=a;
        przen(len);
    }
    void write(){
        printf("%d",int(cyf[len-1]));
        FORD(x,len-2,0)
            printf("%0*d",BD,int(cyf[x]));
    }
};

const int ALF=30,N=10010;

int roz[ALF],num[ALF],dlg1,dlg2,l;
VI g[N];
int s1[N],s2[N];
char slowo[N+1];
bool vs[N];

#define ZERO (num[l])
#define JEDEN (num[l]+1)

bool Dfs(int v){
    vs[v]=true;
    FOREACH(it,g[v])
        if(!vs[*it])
            Dfs(*it);
}

void Solve(){
    int wyk=0;
    BigNum res(1);
    Dfs(ZERO);
    if(vs[JEDEN]){
        printf("0\n");
        return;
    }
    Dfs(JEDEN);
    REP(i,JEDEN+1)
        if(!vs[i]){
            Dfs(i);
        ++wyk;
    }

    REP(i,wyk)
        res*=2;
    res.write();
    printf("\n");
}

int main(){
    int z;scanf("%d",&z);
    REP(h,z){
        scanf("%d",&l);
        REP(i,l)
            scanf("%d",&roz[i]);
        FOR(i,1,l)
            num[i]=num[i-1]+roz[i-1];
        int d1=0,d2=0,t;
        scanf("%d %s",&t,slowo);
        int r=0;
        REP(i,t){
            if(slowo[i]=='0'){
                s1[r++]=ZERO;
            }else if(slowo[i]=='1'){
                s1[r++]=JEDEN;
            }else{
                REP(j,roz[slowo[i]-'a']){
                    s1[r++]=num[slowo[i]-'a']+j;
                }
            }
        }
        d1=r;
        scanf("%d %s",&t,slowo);
        r=0;
        REP(i,t){
            if(slowo[i]=='0'){
                s2[r++]=ZERO;
            }else if(slowo[i]=='1'){
                s2[r++]=JEDEN;
            }else{
                REP(j,roz[slowo[i]-'a']){
                    s2[r++]=num[slowo[i]-'a']+j;
                }
            }
        }
        d2=r;
        if(d1!=d2){
            printf("0\n");
        }else{
            REP(i,JEDEN+1){
                g[i].clear();
                vs[i]=false;
            }
            REP(i,d1){
                g[s1[i]].PB(s2[i]);
                g[s2[i]].PB(s1[i]);
            }
            Solve();
        }
    }
    return 0;
}
