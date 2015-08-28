///Karol Jamrozy
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

#define MAXM 1000002

int kolory[MAXM];//klocki - tablica z rozwiazaniem, kolory - tablica z ilosciami klockow poszczegolnego koloru
int n,x,y,z,l,v,sum;//n - liczba kolorow, x - kolor pierwszego klocka, y - kolor ostatniego klocka, z - kolor wystepujacy najliczniej
vector<int> luki[MAXM];//luki w ktorych znajduja sie inne klocki


void Solve(){
    if(sum==1){
        if(x==y && kolory[x]==-1)
            printf("%d",x);
        else puts("0");
        return;
    }
    if(sum==2){
        if(x==y or kolory[x]!=0 or kolory[y]!=0)
            puts("0");
        else printf("%d %d",x,y);
        return;
    }
    if(kolory[x]<0 or kolory[y]<0){
        puts("0");
        return;
    }
    if(z==x){
        if(x!=y){
            if(sum-2-kolory[z]<kolory[z]){
                puts("0");
                return;
            }
            if(kolory[y]>0){
                --kolory[y];
                luki[0].PB(y);
            }else{
                FOR(i,1,n)
                if(i!=z && kolory[i]>0){
                    --kolory[i];
                    luki[0].PB(i);
                    break;
                }
            }
        }else{
            if(sum-2-kolory[z]<kolory[z]+1){
                puts("0");
                return;
            }
            FOR(i,1,n)
            if(i!=z && kolory[i]>0){
                --kolory[i];
                luki[0].PB(i);
                break;
            }
            FOR(i,1,n)
            if(i!=z && kolory[i]>0){
                --kolory[i];
                luki[kolory[z]].PB(i);
                break;
            }
        }
    }else if(z==y){
        if(sum-2-kolory[z]<kolory[z]){
            puts("0");
            return;
        }
        if(kolory[x]>0){
            --kolory[x];
            luki[kolory[z]].PB(x);
        }else{
            FOR(i,1,n)
            if(i!=z && kolory[i]>0){
                --kolory[i];
                luki[kolory[z]].PB(i);
                break;
            }
        }
    }else if(sum-2-kolory[z]<kolory[z]-1){
        puts("0");
        return;
    }
    int j=0;
    FOR(i,1,n)
        if(i!=z){
            while(kolory[i]>0){
                j%=kolory[z];
                if(j==kolory[z]-1 && (i==y or i==x)){
                    ++j;
                    j%=kolory[z];
                }
                luki[j+1].PB(i);
                ++j;
                --kolory[i];
            }
        }
        printf("%d ",x);
        FOREACH(it,luki[0])
            printf("%d ",*it);
        FOR(i,1,kolory[z]){
            printf("%d ",z);
            FOREACH(it,luki[i])
                printf("%d ",*it);
        }
        printf("%d ",y);
}

int main(){
    scanf("%d%d%d",&n,&x,&y);
    l=-1;sum=0;
    FOR(i,1,n){
        scanf("%d",&kolory[i]);
        sum+=kolory[i];
        if(i==x)
            --kolory[i];
        if(i==y)
            --kolory[i];
        if(kolory[i]>l or (kolory[i]==l && (i==x or i==y) )){
            l=kolory[i];
            z=i;
        }
    }
    Solve();
    return 0;
}
