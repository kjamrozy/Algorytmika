///Karol Jamrozy
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 3003

int n;
int plansza[MAXN][3];
bool wyst[3*MAXN+1];

void Wypisz(){
    REP(i,3){
        REP(j,n){
            printf("%d ",plansza[j][i]);
        }
        printf("\n");
    }
    exit(0);
}

void Dfs(int i,int j){
    if(plansza[i][j]==3*n){
        Wypisz();
    }
    if(wyst[plansza[i][j]+1]){
        if(j>0 && plansza[i][j-1]==plansza[i][j]+1){
            Dfs(i,j-1);
            plansza[i][j-1]=plansza[i][j]+1;
        }
        if(j<2 && plansza[i][j+1]==plansza[i][j]+1){
            Dfs(i,j+1);
            plansza[i][j+1]=plansza[i][j]+1;
        }
        if(i>0 && plansza[i-1][j]==plansza[i][j]+1){
            Dfs(i-1,j);
            plansza[i-1][j]=plansza[i][j]+1;
        }
        if(i<n-1 && plansza[i+1][j]==plansza[i][j]+1){
            Dfs(i+1,j);
            plansza[i+1][j]=plansza[i][j]+1;
        }
    }else{
    if(j>0 && plansza[i][j-1]==0){
        plansza[i][j-1]=plansza[i][j]+1;
        Dfs(i,j-1);
    }
    if(j<2 && plansza[i][j+1]==0){
        plansza[i][j+1]=plansza[i][j]+1;
        Dfs(i,j+1);
    }
    if(i>0 && plansza[i-1][j]==0){
        plansza[i-1][j]=plansza[i][j]+1;
        Dfs(i-1,j);
    }
    if(i<n-1 && plansza[i+1][j]==0){
        plansza[i+1][j]=plansza[i][j]+1;
        Dfs(i+1,j);
    }
    }
    plansza[i][j]=0;
}

void Solve(){
    FOR(i,1,3*n)
        wyst[i]=false;
    REP(i,3)
        REP(j,n)
            wyst[plansza[j][i]]=true;
    REP(i,3)
        REP(j,n)
            if((plansza[j][i]==0 && !wyst[1]) or plansza[j][i]==1){
                bool czy=false;
                czy=plansza[j][i];
                plansza[j][i]=1;
                Dfs(j,i);
                plansza[j][i]=czy;
            }
}

int main(){
    scanf("%d",&n);
    REP(i,3)
        REP(j,n)
            scanf("%d",&plansza[j][i]);
    Solve();
    return 0;
}
