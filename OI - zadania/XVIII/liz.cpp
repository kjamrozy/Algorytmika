#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 1000002
#define MAXK 2000002

int n,m;
int lizak[MAXN],bliska_prawa[MAXN],bliska_lewa[MAXN],sumpref[MAXN],
lewy_kraniec[MAXK],prawy_kraniec[MAXK];
char ciag[MAXN];
int calosc;

void Prepare(){
    REP(i,n)/// przepisanie liter na koszt segmentu
        lizak[i+1]= (ciag[i]=='T') ? 2 : 1;
    FOR(i,1,n*2)
        lewy_kraniec[i]=prawy_kraniec[i]=-1;
    calosc=0;
    FOR(i,1,n){
        calosc+=lizak[i];
        lewy_kraniec[calosc]=i;
    }
    calosc=0;
    FORD(i,n,1){
        calosc+=lizak[i];
        prawy_kraniec[calosc]=i;
    }
    sumpref[0]=0;
    FOR(i,1,n)
        sumpref[i]=sumpref[i-1]+lizak[i];
    int najblizsza=-1;
    FOR(i,1,n){
        bliska_lewa[i]=najblizsza;
        if(lizak[i]==1)
            najblizsza=i;
    }
    najblizsza=-1;
    FORD(i,n,1){
        bliska_prawa[i]=najblizsza;
        if(lizak[i]==1)
            najblizsza=i;
    }
}

inline int Suma(int a,int b){
    return sumpref[b]-sumpref[a-1];
}

void Answer(int k){
    if(k>calosc or k>n*2){
        puts("NIE");
        return;
    }else if(calosc==k){
        printf("%d %d\n",1,n);
        return;
    }
    if(lewy_kraniec[k]!=-1){
        printf("%d %d\n",1,lewy_kraniec[k]);
        return;
    }else if(prawy_kraniec[k]!=-1){
        printf("%d %d\n",prawy_kraniec[k],n);
        return;
    }
    int l=1,r=lewy_kraniec[k+1];
    if(bliska_prawa[r]!=-1){
        r=bliska_prawa[r]-1;
        int sum=Suma(l,r);///cos wiekszego od k
        if(lewy_kraniec[sum-k]!=-1){
            printf("%d %d\n",lewy_kraniec[sum-k]+1,r);
            return;
        }else{
            printf("%d %d\n",lewy_kraniec[sum-k+1]+1,r+1);
            return;
        }
    }
    l=prawy_kraniec[k+1],r=n;
    if(bliska_lewa[l]!=-1){
        l=bliska_lewa[l]+1;
        int sum=Suma(l,r);///cos wiekszego od k
        if(prawy_kraniec[sum-k]!=-1){
            printf("%d %d\n",l,prawy_kraniec[sum-k]-1);
            return;
        }else{
            printf("%d %d\n",l-1,prawy_kraniec[sum-k+1]-1);
            return;
        }
    }
    puts("NIE");
}

int main(){
    scanf("%d%d%s",&n,&m,ciag);
    Prepare();
    REP(i,m){
        int k;
        scanf("%d",&k);
        Answer(k);
    }
}
