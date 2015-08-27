#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

typedef long long LL;

#define Cycle(a,n) (a<0) ? (a+n) : ((a>=n) ? (a-n) : a)

struct POINT{
    int x,y;
    POINT(int x=0,int y=0) : x(x),y(y) {}
};

LL Det(POINT a,POINT b,POINT c){
    return LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*LL(c.x-a.x);
}

LL sqr(int a){
    return LL(a)*LL(a);
}

int main(){
    int t;
    scanf("%d",&t);
    FOR(wielokat,1,t){
        int n;
        scanf("%d",&n);
        vector<POINT>  v(2*n);
        REP(i,n){
            scanf("%d%d",&v[i*2].x,&v[i*2].y);
            v[i*2].x<<=1;
            v[i*2].y<<=1;
        }
        vector<LL> rep(n*4,0);
        REP(i,n){
            v[i*2+1].x=(v[2*i].x+v[Cycle(2*i+2,n*2)].x) >> 1;
            v[i*2+1].y=(v[2*i].y+v[Cycle(2*i+2,2*n)].y) >> 1;
        }
        REP(i,2*n){
            rep[2*i] = sqr(v[i].x - v[Cycle(i-1, 2*n)].x) + sqr(v[i].y - v[Cycle(i-1, 2*n)].y);
            rep[2*i+1] = LL(2) * Det(v[i], v[Cycle(i-1, 2*n)], v[Cycle(i+1, 2*n)]);
        }
        vector<int> rad(n*8,0);
        int i=1,j=0,k;
        while(i  < 8*n) {
            while(i+j+1 < 8*n && i - j > 0 && rep[Cycle(i-j-1,4*n)] == rep[Cycle(i+j+1,4*n)]) j++;
            for(rad[i]=j, k=0; ++k<=j && rad[i-k]!=j-k;) rad[i+k] = min(rad[i-k], j-k);
                j = max(0, j - k);
                i += k;
        }
        int res = 0;
        REP(i,2*n) if(rad[2*i+1+2*n] >= 2*n) res++;
            printf("%d\n", res/2);
    }
    return 0;
}
