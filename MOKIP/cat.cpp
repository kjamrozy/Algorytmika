///********************************************************///
///*                                                      *///
///*  Autor: Karol Jamrozy                                *///
///*  Zadanie: Osadnicy z Catalonu                        *///
///*  Plik:cat.cpp                                        *///
///*  Zlozonosc: O(n)                                     *///
///*  Opis: Rozwiazanie za pomoca programowania           *///
///*  dynamicznego                                        *///
///*                                                      *///
///********************************************************///
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define FOR(x,b,e) for(int x=b;x<=e;x++)
#define FORD(x,b,e) for(int x=b;x>=e;x--)
#define REP(x,e) for(int x=0;x<e;x++)
#define SIZE(x) ( (int)(x).size())
#define ALL(c) (c).begin(),(c).end()
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)
#define ST first
#define ND second
#define PB push_back

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

int m;

vector<int>* adj;
int *c;
int* n;

void Osadnicy(int p,int v){
    c[v]=1;
    n[v]=0;
    printf("\n 1 \n");
    FOREACH(it,adj[v])
        if(*it!=p)
        {
            printf("\n 2 %d \n",*it);
            Osadnicy(v,*it);
            printf("\n 3 \n");
            n[v]+=max(c[*it],n[*it]);
            printf("\n 4 \n");
            c[v]+=n[*it];
            printf("\n 5 \n");
        }
    printf("\n endless \n");
}

int main()
{
    scanf("%d",&m);
    adj=new vector<int>[m];
    c=new int[m];
    n=new int[m];
    REP(i,m) c[i]=n[i]=0;
    printf("\n WSTYD? \n");
    REP(i,m-1){
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        adj[t1-1].PB(t2-1);
        adj[t2-1].PB(t1-1);
    }
    printf("\n LOL? \n");
    Osadnicy(-1,0);
    printf("%d",max(c[0],n[0]));
    delete [] n;
    delete [] c;
    delete [] adj;
    return 0;
}
