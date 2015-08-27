#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define PB push_back
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;

#define MAXN 1000001
#define MAXE 30

const int alph = (int)'z'-(int)'a'+1;
const int INF = 1000000001;

int n;
char slowo[MAXN];
VI wyst[MAXE];// miejsca wystapienia dla liter a...z

inline char Alphabet(int x){
    return char(x+(int)'a');
}

inline int Number(char x){
    return (int)x-(int)'a';
}

int Solve(){
    FOR(i,1,n)
        wyst[Number(slowo[i])].PB(i);
    int res=0;
    REP(i,alph){
        if(SIZE(wyst[i])){
        REP(j,alph){
            if(i!=j){
                int sum=0,minimum=INF,ostatnie=0;
                vector<int>::iterator it1=wyst[i].begin(),it2=wyst[j].begin();
                while(it1!=wyst[i].end() && it2!=wyst[j].end()){
                    if(*it1<*it2){
                        ++sum;
                        res=max(res,sum-minimum);
                        ++it1;
                    }else{
                        minimum=min(ostatnie,minimum);
                        --sum;
                        ostatnie=sum;
                        res=max(res,sum-minimum);
                        ++it2;
                    }
                    if(it1==wyst[i].end()){
                        while(it2!=wyst[j].end()){
                            minimum=min(ostatnie,minimum);
                            --sum;
                            ostatnie=sum;
                            res=max(res,sum-minimum);
                            ++it2;
                        }
                    }
                    if(it2==wyst[j].end()){
                        while(it1!=wyst[i].end()){
                            ++sum;
                            res=max(res,sum-minimum);
                            ++it1;
                        }
                    }
                }
        }
        }
    }
}
    return res;
}
int main(){
    scanf("%d%s",&n,slowo+1);
    printf("%d",Solve());
    return 0;
}
