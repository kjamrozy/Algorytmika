#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ALL(c) (c).begin,(c).end()
#define SIZE(x) ((int)(x).size())

const int N = 6001;

int n,fw[N][3],scal[N];
char col[N];
bool act[N];

struct kod{
    int v,k1,k2,k3;
    kod(int w,int a,int b,int c) : v(w),k1(a),k2(b),k3(c) {}
};

vector<int> ot[N];

bool Podobne(int u,int v){
        if(col[u]!=col[v]) return false;
        if(fw[u][0]!=fw[v][0]) return false;
        if(fw[u][1]!=fw[v][1]) return false;
        if(fw[u][2]!=fw[v][2]) return false;
    return true;
}

void Likwiduj(int u,int v){
    if(u!=v){
    act[v]=false;
        FOREACH(it,ot[v]){
            if(act[*it]){
                if(fw[*it][0]==v) fw[*it][0]=u;
                if(fw[*it][1]==v) fw[*it][1]=u;
                if(fw[*it][2]==v) fw[*it][2]=u;
                ot[u].PB(*it);
            }
        }
    }
}

bool cmp(const int& a,const int& b)const{
    return (col[a]==col[b]) ? ((fw[a][0]==fw[b][0]) ? ( (fw[a][1]==fw[b][1]) ? ( (fw[a][2]==fw[b][2]) ? a>b  : fw[a][2]>fw[b][2] ) : fw[a][1]>fw[b][1] ) : fw[a][0]>fw[b][0] ) : col[a]>col[b];
}

void Solve(){
    FORD(i,n,2){
        if(act[i]){
            sort(ot[i].begin(),ot[i].end(),cmp);
            VAR(it,ot[i].begin());
            while(it!=ot[i].end()){
                int x=*it;
                ++it;
                while(it!=ot[i].end() && Podobne(x,*it)){
                    Likwiduj(x,*it);
                    ++it;
                }
            }
        }
    }
    int res=0;
    FOR(i,1,n)
        if(act[i]) ++res;
    printf("%d",res);
}

int main(){
    scanf("%d",&n);
    memset(act,true,sizeof(act));
    memset(scal,-1,sizeof(scal));
    FOR(i,1,n-1){
        char lit[5];
        scanf("%s%d%d%d",lit,&fw[i][0],&fw[i][1],&fw[i][2]);
        col[i]=lit[0];
        if(fw[i][0]!=fw[i][1] && fw[i][0]!=fw[i][2])
            ot[fw[i][0]].PB(i);
        if(fw[i][1]!=fw[i][2])
            ot[fw[i][1]].PB(i);
        ot[fw[i][2]].PB(i);
    }
    Solve();
    return 0;
}
