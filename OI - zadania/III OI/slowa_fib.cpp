#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <cstring>
#include <iostream>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v= (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
#define PB push_back
#define SIZE(x) ((int)(x).size())

typedef long long LL;

const int N = 201,L=32;

LL hash=107,BASE=1000000007;

int n,l;
char slowo[33];
string fib[N];

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef long long LL;
typedef vector<PII> VPII;

struct BigNum {
    #define REDUCE() while(len>1 && !cyf[len-1]) --len;
    static const int BASE=1000000000,BD=9;
    int al, len;
    LL*cyf;
    BigNum(int v = 0, int l = 2) : cyf(new LL[l]),al(l),len(1)   {
        REP(x, al) cyf[x] = 0;
        if ((cyf[0] = v) >= BASE) przen(1);
    }
    BigNum(const BigNum & a) : len(a.len), al(a.len), cyf(new LL[al]) {
        REP(x, al) cyf[x] = a.cyf[x];
    }
    ~BigNum(){
        delete cyf;
    }
    void Res(int l) {
        if (l > al){
            LL *n = new LL[l = max(l, 2 * al)];
            REP(x, l) n[x] = x >= al ? 0 : cyf[x];
            delete cyf;
            cyf = n;
            al = l;
        }
    }
    void przen(int p) {
        int x = 0;
        for (; x < p || cyf[x] < 0 || cyf[x] >= BASE; x++) {
            Res(x + 2);
            if (cyf[x] < 0) {
                LL i = (-cyf[x] - 1) / BASE + 1;
                cyf[x] += i * BASE;
                cyf[x + 1] -= i;
            } else if (cyf[x] >= BASE) {
                LL i = cyf[x] / BASE;
                cyf[x] -= i * BASE;
                cyf[x + 1] += i;
            }
        }
        len = max(len, x + 1);
        REDUCE();
    }
    #define OPER1(op) bool operator op (const BigNum &a) const
    OPER1(==) {
        if (a.len != len) return 0;
        REP(x, len) if (cyf[x] != a.cyf[x]) return 0;
        return 1;
    }
    OPER1(<) {
        if (len != a.len) return len < a.len;
        int x = len - 1;
        while (x && a.cyf[x] == cyf[x]) x--;
        return cyf[x] < a.cyf[x];
    }
    OPER1(>) {
        return a < *this;
    }
    OPER1(<=) {
        return !(a < *this);
    }
    OPER1(>=) {
        return !(*this < a);
    }
    OPER1(!=) {
        return !(*this == a);
    }
    BigNum & operator=(int a) {
        REP(x, len) cyf[x] = 0;
        len = 1;
        if (cyf[0] = a >= BASE) przen(1);
        return *this;
    }
    void operator+=(int a) {
        cyf[0] += a;
        przen(1);
    }
    void operator-=(int a) {
        cyf[0] -= a;
        przen(1);
    }
    void operator*=(int a) {
        REP(x, len) cyf[x] *= a;
        przen(len);
    }
    int operator/=(int a) {
        LL w = 0;
        FORD(p, len - 1, 0) {
            w = w * BASE + cyf[p];
            cyf[p] = w / a;
            w %= a;
        }
        REDUCE();
        return w;
    }
    int operator%(int a) {
        LL w = 0;
        FORD(p, len - 1, 0) w = (w * BASE + cyf[p]) % a;
        return w;
    }

    #define OPER2(op) BigNum& operator op (const BigNum &a)
    OPER2(+=){
        Res(a.len);
        REP(x,a.len) cyf[x]+=a.cyf[x];
        przen(a.len);
        return *this;
    }
    OPER2(-=) {
        REP(x, a.len) cyf[x] -= a.cyf[x];
        przen(a.len);
        return *this;
    }
    OPER2(*=) {
        BigNum c(0, len + a.len);
        REP(x, a.len) {
            REP(y, len) c.cyf[y + x] += cyf[y] * a.cyf[x];
            c.przen(len + x);
        }
        *this = c;
        return *this;
    }
    OPER2(/=){
        int n = max(len - a.len + 1, 1);
        BigNum d(0, n), prod;
        FORD(i, n - 1, 0) {
            int l = 0, r = BASE - 1;
            while (l < r) {
                int m = (l + r + 1) / 2;
                if (*this < prod + (a * m << i)) r = m - 1;
                else l = m;
            }
            prod += a * l << i;
            d.cyf[i] = l;
            if (l) d.len = max(d.len, i + 1);
        }
        *this = d;
        return *this;
    }
    OPER2(%=) {
        BigNum v = *this;
        v /= a;
        v *= a;
        *this -= v;
        return *this;
    }
    OPER2(=) {
        Res(a.len);
        FORD(x, len - 1, a.len) cyf[x] = 0;
        REP(x, a.len) cyf[x] = a.cyf[x];
        len = a.len;
        return *this;
    }
    void read(const VI& v,int p){
        *this=0;
        FORD(x,SIZE(v)-1,0){
            *this*=p;
            *this+=v[x];
        }
    }
    BigNum & operator=(string a) {
        int s = a.length();
        *this = 0;Res(len = s / BD + 1);
        REP(x, s) cyf[(s - x - 1) / BD] = 10 * cyf[(s - x - 1) / BD] + a[x] - '0';
        REDUCE();
        return *this;
    }
    void write() const {
        printf("%d", int (cyf[len - 1]));
        FORD(x, len - 2, 0) printf("%0*d", BD, int (cyf[x]));
    }
    void write(char *buf) const {
        int p = sprintf(buf, "%d", int (cyf[len - 1]));
        FORD(x, len - 2, 0) p += sprintf(buf + p, "%0*d", BD, int (cyf[x]));
    }
    VI write(int pod) const {
        VI w;
        BigNum v;
        v = *this;
        while (v.len > 1 || v.cyf[0]) w.PB(v /= pod);
        return w;
    }
    BigNum& operator>>=(int n){
        if(n>len) n=len;
        REP(x,len-n) cyf[x]=cyf[x+n];
        FOR(x,len-n,len-1) cyf[x]=0;
        len-=n;
        if(len==0) len=1;
        return *this;
    }
    BigNum & operator<<=(int n) {
        if (cyf[0] == 0 && len == 1) return *this;
        Res(len + n);
        FORD(x, len - 1, 0) cyf[x + n] = cyf[x];
        REP(x, n) cyf[x] = 0;
        len += n;
        return *this;
    }
    BigNum sqrt() {
        int n = (len + 1) / 2;
        BigNum a(0, n), sq;
        FORD(i, n - 1, 0) {
            int l = 0, r = BASE - 1;
            while (l < r) {
                int m = (l + r + 1) / 2;
                if (*this < sq + (a*2  * m << i) + (BigNum(m) * m << 2 * i)) r = m -1;
                else l = m;
            }
            sq += (a*2* l << i) + (BigNum(l) * l << 2 * i);
            a.cyf[i] = l;
            a.len = n;
        }
        return a;
    }
    #define OPER3(op) BigNum operator op(const BigNum &a) \
    const {BigNum w=*this; w op ## = a; return w; }
    #define OPER4(op) BigNum operator op(int a) \
    {BigNum w = *this; w op ## = a; return w; }
    OPER3(+);
    OPER3(-);
    OPER3(*);
    OPER3(/);
    OPER3(%);
    OPER4(<<);
    OPER4(>>);
};

void Init(){
    fib[1]=" b";
    fib[2]=" a";
    fib[3]=" ab";
    fib[4]=" aba";
    fib[5]=" abaab";
    fib[6]=" abaababa";
    fib[7]=" abaababaabaab";
    fib[8]=" abaababaabaababaababa";
    fib[9]=" abaababaabaababaababaabaababaabaab";
    fib[10]=" abaababaabaababaababaabaababaabaababaababaabaababaababa";
}

bool pref[L][N],suf[L][N];
int pot[64];
BigNum wyst[N];
LL hashe1[64],hashe2[64],slow[33];

LL Hash(int a,int b,LL* tab){
    LL res=(tab[a]-(tab[b+1]*pot[b-a+1])%BASE)%BASE;
    if(res<0) res+=BASE;
    return res;
}

void Solve(){
    if(n==0) return;
    l=strlen(slowo)-1;
    pot[0]=1;
    FOR(i,1,64)
        pot[i]=(pot[i-1]*hash)%BASE;
    FORD(i,l,1) slow[i]=(slow[i+1]*hash+int(slowo[i]))%BASE;
    LL haslo=Hash(1,l,slow);
    if(n<11){
        FORD(i,SIZE(fib[n])-1,1) hashe1[i]=(hashe1[i+1]*hash+int(fib[n][i]))%BASE;
        FOR(i,1,SIZE(fib[n])-l){
            if(Hash(i,i+l-1,hashe1)==haslo) wyst[n]+=1;
        }
        return;
    }
    FORD(i,SIZE(fib[9])-1,1) hashe1[i]=(hashe1[i+1]*hash+int(fib[9][i]))%BASE;
    FORD(i,SIZE(fib[10])-1,1) hashe2[i]=(hashe2[i+1]*hash+int(fib[10][i]))%BASE;
    FOR(i,0,l-2){
        if(Hash(SIZE(fib[10])-1-i,SIZE(fib[10])-1,hashe2)==Hash(1,1+i,slow)) suf[i+1][10]=true;
        if(Hash(1,1+i,hashe2)==Hash(l-i,l,slow)) pref[i+1][10]=true;
        if(Hash(SIZE(fib[9])-1-i,SIZE(fib[9])-1,hashe1)==Hash(1,1+i,slow)) suf[i+1][9]=true;
        if(Hash(1,1+i,hashe1)==Hash(l-i,l,slow)) pref[i+1][9]=true;
    }
    FOR(i,1,SIZE(fib[9])-l){
            if(Hash(i,i+l-1,hashe1)==haslo) wyst[9]+=1;
        }
            FOR(i,1,SIZE(fib[10])-l){
            if(Hash(i,i+l-1,hashe2)==haslo) wyst[10]+=1;
        }
    FOR(i,11,n){
        wyst[i]=wyst[i-1]+wyst[i-2];
        FOR(j,1,l-1)
            pref[j][i]=pref[j][i-1],suf[j][i]=suf[j][i-2];
        FOR(j,1,l-1){
            if(suf[j][i-1] && pref[l-j][i-2])
                wyst[i]+=1;
        }
    }
}

int main(){
    slowo[0]=' ';
    scanf("%s %d",slowo+1,&n);
    Init();
    Solve();
    wyst[n].write();
    return 0;
}
