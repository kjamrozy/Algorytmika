/// Karol Jamrozy
/// Literatura: Algorytmika praktyczna Nie tylko dla mistrzów - Piotr Stańczyk
#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 1000001

int sum_pref[MAXN],salatka[MAXN],zera[MAXN],last[2*MAXN],nextj[MAXN],q[MAXN];
char owoce[MAXN];
int n;

void Init(){
    sum_pref[0]=0;
    FOR(i,1,n){
        sum_pref[i]=sum_pref[i-1] + ((owoce[i-1]=='p') ? 1 : -1);
        nextj[i]=zera[i]=-1;
    }
    FOR(i,1,2*n)
        last[i]=-1;
    int lj=-1;
    FORD(i,n,1){
        nextj[i]=lj;
        if(owoce[i-1]=='p')
            zera[i]=last[n+sum_pref[i]-1];
        else{
            zera[i]=last[n+sum_pref[i]+1];
            lj=i;
        }
        last[n+sum_pref[i]]=i;
        if(owoce[i-1]=='p' && last[n+sum_pref[i]-2]>i)
            salatka[i]=last[n+sum_pref[i]-2]-i;
        else if(owoce[i-1]=='p' && sum_pref[n]-sum_pref[i-1]>=0) salatka[i]=n-i+1;
        else salatka[i]=-1;
    }
}

int Skracaj(int v,int r){
    int poz=nextj[zera[v]],val=zera[v];
    int b,e;
    q[b=e=0]=v;
    while(poz!=-1 && zera[poz]!=-1 && zera[poz]<=r ){
        val=zera[q[++e]=poz];
        poz=nextj[zera[poz]];
    }
    REP(i,e)
        zera[q[i]]=val;
    return val;
}

int Solve(){
    int res=0;
    FOR(i,1,n){//petla wykona sie O(n) razy
        if(salatka[i]!=-1){
            if(nextj[i]==-1){
                res=max(res,n-i+1);
                break;
            }else if(nextj[i]>i+salatka[i]-1){
                res=max(res,salatka[i]);
            }else if(zera[nextj[i]]>i+salatka[i]-1){
                res=max(res,nextj[i]-i);
            }else if(zera[nextj[i]]==-1){
                res=max(res,min(i+salatka[i]-1,nextj[i]-1)-i+1);
            }
            else{
                int v=Skracaj(nextj[i],i+salatka[i]-1);//,zera[nextj[i]]);
                if(nextj[v]==-1){
                    res=max(res,n-i+1);
                    break;
                }else{ res=max(res,min(i+salatka[i]-1,nextj[v]-1)-i+1);
                }
            }
        }
    }
    return res;
}

int main(){
    scanf("%d%s",&n,owoce);
    Init();
    printf("%d",Solve());
    return 0;
}
