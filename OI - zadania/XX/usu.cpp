#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;>=e;--x)

#define MAXN 1000001

int n,k,top;
int pref[MAXN],s1[MAXN],s2[MAXN],s3[MAXN];
int SumaGora(){
    if(top>=k){
        if(top==k)
            return pref[k];
        else return pref[top]-pref[top-k-1];
    }else return -1;
}

int ToInt(char c){
    if(c=='c')
        return k;
    else return -1;
}

void Ans(){
    ///s1 -> stos numerkow, s2-> stos wartosi, s3->stos wynikowy, pref->tablica sum prefiksowych z s2
    int t=-1;
    top=-1;
    char ciag[n];
    scanf("%s",ciag);
    REP(i,n){
        int val=ToInt(ciag[i]);
        s1[top+1]=i;
        s2[top+1]=val;
        ++top;
        pref[top]=val + (top>=1 ? pref[top-1] : 0);
        if(SumaGora()==0){
            REP(j,k+1){
                s3[++t]=s1[top-j];
            }
            top-=k+1;
        }
    }
    FOR(i,1,n/(k+1)){
        FOR(j,1,k+1){
            printf("%d ",s3[t--]+1);
        }
        printf("\n");
    }
}

int main(){
    scanf("%d%d",&n,&k);
    Ans();
    return 0;
}
