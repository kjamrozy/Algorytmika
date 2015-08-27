#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 602
#define MAXK 52

int n,k;
int pociag[MAXN][MAXN];
int sprawdzanie[MAXN][MAXK];
int przedzialy[MAXN][MAXK];
vector<int> result;

void init(){
    FOR(i,1,n-2){
        pociag[0][i]+=pociag[0][i-1];
        pociag[i][0]+=pociag[i-1][0];
    }
    FOR(i,1,n-2)
        FOR(j,1,n-2)
            pociag[j][i]=pociag[j][i]+pociag[j][i-1]+pociag[j-1][i]-pociag[j-1][i-1];
}

/// (a,b)########
///      ########
///      ########
///      ########(c,d)

int Suma(int a,int b,int c,int d){
    if(a==0 && b==0){
        return pociag[c][d];
    }else if(b==0){
        return pociag[c][d]-pociag[a-1][d];
    }else if(a==0){
        return pociag[c][d]-pociag[c][b-1];
    }else return pociag[c][d]-pociag[a-1][d]-pociag[c][b-1]+pociag[a-1][b-1];
}

void Solve(){
    REP(i,n-1){
        int c=Suma(i,0,n-2,i);
        przedzialy[i][1]=c;
        REP(j,i){
            FOR(l,2,k){
                c=Suma(i,j+1,n-2,i);
                if(c+przedzialy[j][l-1]>przedzialy[i][l]){
                    sprawdzanie[i][l]=j;
                    przedzialy[i][l]=c+przedzialy[j][l-1];
                }
            }
        }
    }
    int il=min(n-1,k),maxval=0,maxv=0;
    REP(i,n-1)
        if(przedzialy[i][il]>maxval){
            maxval=przedzialy[i][il];
            maxv=i;
        }
    result.resize(il);
    FORD(i,il,1){
        result[i-1]=maxv+1;
        maxv=sprawdzanie[maxv][i];
    }
    for(vector<int>::iterator it=result.begin();it!=result.end();++it)///
        printf("%d ",*it);///
}

int main(){
    scanf("%d%d",&n,&k);
    REP(i,n){
        REP(j,n)
            pociag[i][j]=0;
        FOR(j,1,k)
            sprawdzanie[i][j]=przedzialy[i][j]=0;
    }
    REP(i,n-1)
        FOR(j,i,n-2)
            scanf("%d",&pociag[j][i]);
    init();
    Solve();
    return 0;
}
