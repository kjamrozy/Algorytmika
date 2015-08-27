/** O(n log n) **/
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())

#define MAXN 500002

typedef vector<int> VI;
typedef long long LL;
typedef vector<LL> VLL;

int u[MAXN],v[MAXN],licz[MAXN],num[MAXN];///licz przechowuje ilosc wystapien kodonu, num - tablica ktory z kolei to kodon tego typu
VI wyst1[MAXN],wyst2[MAXN];
VLL sumpref[MAXN];/// wyst1 - vector wystepowan kodonow w u, wyst2 -'- w v
LL pot1[MAXN+1],pothasz1a[MAXN],pothasz2a[MAXN];///stablicowane potegi, tablice haszy sufiksow

int n,m,q,maxu,maxv;

const LL BASE=1000000007;
const LL hash=1000003;

LL Hasz1(int a,int b){
    LL slowo;
        if(b==n){
        slowo=pothasz1a[a];
    }else{
        slowo=((pothasz1a[a]- (((pot1[b-a+1]*pothasz1a[b+1]))%BASE) )%BASE);
        if(slowo<0) slowo+=BASE;
    }
    return (slowo%BASE);
}

LL Hasz2(int a,int b){
    LL slowo;
        if(b==m){
        slowo=pothasz2a[a];
    }else{
        slowo=(pothasz2a[a]-(((pot1[b-a+1]*pothasz2a[b+1]))%BASE) )%BASE;
        if(slowo<0) slowo+=BASE;
    }
    return (slowo%BASE);
}

void init(){
    pot1[0]=1;
    FOR(i,1,max(m,n)+1)
        pot1[i]=((pot1[i-1]*hash)%BASE);

    pothasz1a[n]=(u[n]%BASE);
    FORD(i,n-1,1)
        pothasz1a[i]=(u[i]+((hash*pothasz1a[i+1])%BASE))%BASE;

    pothasz2a[m]=(v[m]%BASE);
    FORD(i,m-1,1)
        pothasz2a[i]=(v[i]+((hash*pothasz2a[i+1])%BASE))%BASE;

    FOR(i,1,maxu){
        if(wyst1[i].size()>0){
            sumpref[i][SIZE(sumpref[i])-1]=1;
            FORD(j,SIZE(sumpref[i])-2,0)
            {
                sumpref[i][j]=(1+(sumpref[i][j+1]*pot1[wyst1[i][j+1]-wyst1[i][j]])%BASE)%BASE;
            }
        }
    }
}

inline bool CzyRowne(int a,int b,int c,int d){
    LL slowo1=Hasz1(a,b),slowo2=Hasz2(c,d);
    return slowo1==slowo2;
}

int NwpB(int h,int j){
    if(u[h]!=v[j]) return 0;
    int dlugosc=0;
    int a=0,b=min(n-h+1,m-j+1);
    if(CzyRowne(h,h+b-1,j,j+b-1)) return b;
    while(a!=b){
        int c=(a+b)/2;
        if(CzyRowne(h,h+c-1,j,j+c-1)){
            dlugosc=c;
            a=c+1;
        }else b=c;
    }
    return dlugosc;
}

inline LL SumP(int a,int b,int z){
    if(b==SIZE(sumpref[z])-1){
        return (sumpref[z][a]%BASE);
    }
    else{
        LL wynik=(sumpref[z][a]-(((pot1[wyst1[z][b+1]-wyst1[z][a] ]%BASE)*sumpref[z][b+1])%BASE))%BASE;
        if(wynik<0) wynik+=BASE;
        return (wynik%BASE);
    }
}

int GranicaB1(int z,int poz){///najmniejszy wiekszy badz rowny poz
    int wynik=SIZE(wyst1[z])-1;
    if(wyst1[z][0]>=poz) return 0;
    if(wyst1[z][SIZE(wyst1[z])-1]<poz) return -1;
    int a=0,b=SIZE(wyst1[z])-1;
    while(a!=b){
        int c=(a+b)/2;
        if(wyst1[z][c]<poz)
            a=c+1;
        else{
            wynik=c;
            b=c;
        }
    }
    return wynik;
}

int GranicaB2(int z,int poz){///najwiekszy mniejszy badz rowny poz
    int wynik=0;
    if(wyst1[z][SIZE(wyst1[z])-1]<=poz) return SIZE(wyst1[z])-1;
    if(wyst1[z][0]>poz) return -1;
    int a=0,b=SIZE(wyst1[z])-1;
    while(a!=b){
        int c=(a+b)/2;
        if(wyst1[z][c]<=poz){
            wynik=c;
            a=c+1;
        }else b=c;
    }
    return wynik;
}

void Odpowiedz(int a,int b,int l){
    LL slowo1=Hasz1(a,a+l-1),slowo2=Hasz2(b,b+l-1);
    if(slowo1==slowo2){
        puts("TAK");
        return;
    }
    int dlg=NwpB(a,b);
    int s1=u[a+dlg],s2=v[b+dlg];
    int z1=GranicaB1(s1,a),z2=GranicaB2(s1,a+l-1);
    LL od=( (SumP(z1,z2,s1)*pot1[wyst1[s1][z1]-a])%BASE )%BASE;
    slowo1=(slowo1 - ((od*s1)%BASE) +
           ( ( (slowo1 - ((od*s1)%BASE))<0 ) ? BASE : 0 )
            + ((od*s2)%BASE) )%BASE;
    if(slowo1<0) slowo1+=BASE;
    if((slowo1%BASE)==(slowo2%BASE)){
        puts("TAK");
    }else puts("NIE");
}

int main(){
    maxu=maxv=0;///inicjalizacja zmiennych

    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d",&u[i]);
        ++licz[u[i]];
        maxu=max(maxu,u[i]);
    }
    FOR(i,1,maxu){
        wyst1[i].resize(licz[i]);
        sumpref[i].resize(licz[i]);
        licz[i]=0;
    }
    FOR(i,1,n){
        wyst1[u[i]][num[u[i]]++]=i;
    }
    FOR(i,1,maxu){///zeruje tablice num
        num[i]=0;
    }

    scanf("%d",&m);
    FOR(j,1,m){
        scanf("%d",&v[j]);
        ++licz[v[j]];
        maxv=max(maxv,v[j]);
    }
    FOR(i,1,maxv){
        wyst2[i].resize(licz[i]);
    }
    FOR(i,1,m){
        wyst2[v[i]][num[v[i]]++]=i;
    }

    init();///inicjalizacja

    scanf("%d",&q);
    REP(i,q){
        int a,b,l;
        scanf("%d%d%d",&a,&b,&l);
        Odpowiedz(a,b,l);
    }
    return 0;
}
