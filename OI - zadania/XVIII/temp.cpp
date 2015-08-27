#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

#define MAXN 1000000
int y[MAXN];

#define f1(x, y) (x + y)
#define f2(x, y) max(x, y)
#define wiele(x, n) (x)
#define PUSTY 0

#define MAX_N 1000001
#define LOG_MAX_N 35

int w[1<<21], W[1<<21];
int n;
int ile;

inline void insert(int a, int b, int c) {
  int va = ile + a, vb = ile + b;
  w[va] = f1(w[va], c);
  if (a != b) w[vb] = f1(w[vb], c);
  int d = 0;
  while (va != 1) {
    if (va / 2 != vb / 2) {
      if (va %2 == 0) w[va + 1] = f1(w[va + 1], c);
      if (vb %2 == 1) w[vb - 1] = f1(w[vb - 1], c);
    }
    va /= 2; vb /= 2;
    W[va] = f2(f1(W[2 * va],wiele(w[2 * va], (1 << d))),
               f1(W[2 * va + 1],wiele(w[2 * va + 1], (1 << d))));
    W[vb] = f2(f1(W[2 * vb],wiele(w[2 * vb], (1 << d))),
               f1(W[2 * vb + 1],wiele(w[2 * vb + 1], (1 << d))));
    d++;
  }
}

#define droga(l) do { \
  int w##l = 0, v##l = ile + l; \
  while (v##l != 0) { \
    pom##l[w##l++] = w[v##l]; \
    v##l /= 2; \
  } \
  for (int j = w##l - 2; j >= 0; j--) \
    pom##l[j] = f1(pom##l[j], pom##l[j + 1]); \
} while (0)

inline int query(int a, int b) {
  int poma[LOG_MAX_N], pomb[LOG_MAX_N];
  droga(a); droga(b);
  int va = ile + a, vb = ile + b;
  int wynik = ((va != vb) ? f2(poma[0], pomb[0]) : poma[0]);
  int d = 0;
  while (va / 2 != vb / 2) {
    if (va % 2 == 0) wynik = f2(wynik, f1(wiele(f1(poma[d + 1], w[va + 1]), (1 << d)), W[va + 1]));
    if (vb % 2 == 1) wynik = f2(wynik, f1(wiele(f1(pomb[d + 1], w[vb - 1]), (1 << d)), W[vb - 1]));
    va /= 2; vb /= 2;
    d++;
  }
  return wynik;
}

void init() {
  ile = 2;
  while (ile < n) ile *= 2;
  for (int i = 1; i < 2*ile; i++) w[i] = W[i] = PUSTY;
}

int Solve(){
    int p=0,q=0,res=1;
    FOR(i,1,n-1){
        while(p<=q && query(p,q)>y[i])
            ++p;
        q=i;
        res=max(res,q-p+1);
    }
    return res;
}

int main(){
    scanf("%d",&n);
    init();
    REP(i,n){
        int t;
        scanf("%d%d",&t,&y[i]);
        insert(i,i,t);
    }
    printf("%d",Solve());
    return 0;
}
