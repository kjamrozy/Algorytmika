#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define SIZE(x) ((int)(x).size())
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair

typedef long long LL;
typedef vector<int> VI;

int n;

template<class V,class E> struct Graph{
    struct Ed : E{
        int v;
        Ed(E p,int w) : E(p),v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeD(int b,int e, E d = E()){
        g[b].PB(Ed(d,e));
    }
    void Bfs(int s){
        FOREACH(it,g) it->t=it->s=-1;
        g[s].t=0;
        int qu[SIZE(g)],b,e;
        qu[b=e=0]=s;
        while(b<=e){
            s=qu[b++];
            FOREACH(it,g[s])
                if(g[it->v].t==-1){
                    g[qu[++e]=it->v].t=g[s].t+1;
                    g[it->v].s=s;
                }
        }
    }

    bool Valid(int v,int p){/// Valid sprawdza czy odnoga jest akceptowalna
        if(SIZE(g[v])==1)
            return true;///lisc czyli jest ok
        int l=0;
        FOREACH(it,g[v])
            if(SIZE(g[it->v])!=1 && it->v!=p){
                ++l;
                if(!Valid(it->v,v))
                    return false;
            }
        if(l==1 or l==0)
            return true;
        else return false;
    }

    int TypeOfLayer(int v,int p){
        if(v!=SIZE(g)-1 && v!=0){
            if(SIZE(g[v])==2)
                return 1;
        }else
            if(SIZE(g[v])==1)
                return 1;
        ///czyli A lub B, jezeli jest poprawny
        int branches=0;
        FOREACH(it,g[v])
            if(SIZE(g[it->v])!=1 && g[it->v].t!=g[v].t-1 && it->v!=p){
                ++branches;
                if(!Valid(it->v,v)) return 0;
            }
        switch(branches){
        case 0:
            return 2;
            break;
        case 1:
            return 2;
            break;
        case 2:
            return 3;
            break;
        default:
            return 0;
            break;
        }
    }

    bool Check(){
        Bfs(SIZE(g)-1);
        bool phase;
        int c=TypeOfLayer(0,0);
        int v=0;
        if(c==1)
            phase=1;
        else if(c==2)
            phase=0;
        else
            return false;
        int p=0;
        while(g[v].s!=-1){
            p=v;
            v=g[v].s;
            c=TypeOfLayer(v,p);
            if(c==3){
                if(!phase)
                    return false;
                phase=0;
            }else if(c==1)
                phase=1;
            else if(c==0)
                return false;
        }
        return true;
    }

    void TBranchFurther(VI& r,int v,int p,bool stage){
        if(stage){/// liscie ->reszta -> rdzen
            FOREACH(it,g[v])///liscie
                if(SIZE(g[it->v])==1 && it->v!=p)
                    r.PB(it->v+1);
            FOREACH(it,g[v])
                if(SIZE(g[it->v])!=1 && it->v!=p)
                    TBranchFurther(r,it->v,v,0);
            r.PB(v+1);///rdzen
        }else{ /// rdzen -> reszta ->liscie
            r.PB(v+1);///rdzen
            FOREACH(it,g[v])
                if(SIZE(g[it->v])!=1 && it->v!=p)
                    TBranchFurther(r,it->v,v,1);
            FOREACH(it,g[v])///liscie
                if(SIZE(g[it->v])==1 && it->v!=p)
                    r.PB(it->v+1);
        }
    }
    void TraverseBranch(VI& r,int v,int p, bool &phase){
        if(phase){
            r.PB(v+1);
            FOREACH(it,g[v])
                if(SIZE(g[it->v])!=1 && it->v!=p)
                    TBranchFurther(r,it->v,v,1);
            FOREACH(it,g[v])
                if(SIZE(g[it->v])==1 && it->v!=p)
                    r.PB(it->v+1);
        }else{
            FOREACH(it,g[v])
                if(SIZE(g[it->v])==1 && it->v!=p)
                    r.PB(it->v+1);
            FOREACH(it,g[v])
                if(SIZE(g[it->v])!=1 && it->v!=p)
                    TBranchFurther(r,it->v,v,0);
            r.PB(v+1);
        }
    }

    void Findway(VI& r){
        r.PB(1);///
        bool phase;///
        int v=0,p=-1;///
        int c=TypeOfLayer(0,-1);///
        if(c==3 or c==0){///
            puts("BRAK");///
            r.clear();///
            return;///
        }else if(c==2){///
            phase=0;///
            FOREACH(it,g[v])
                if(g[it->v].t!=g[v].t-1)
                    if(SIZE(g[it->v])!=1)
                        TraverseBranch(r,it->v,v,phase);
            FOREACH(it,g[v])///
                if(g[it->v].t!=g[v].t-1)
                    if(SIZE(g[it->v])==1)
                        r.PB(it->v+1);
        }
        else phase=1;///
        while(g[v].s!=SIZE(g)-1){///
            p=v;///
            v=g[v].s;///
            c=TypeOfLayer(v,p);///
            if(c==2){///
                if(phase){
                    FOREACH(it,g[v])///
                        if(SIZE(g[it->v])==1 && it->v!=p && g[it->v].t!=g[v].t-1)///
                            r.PB(it->v+1);///
                    FOREACH(it,g[v])///
                        if(SIZE(g[it->v])!=1 && it->v!=p && g[it->v].t!=g[v].t-1)///
                            TraverseBranch(r,it->v,v,phase);///
                    r.PB(v+1);
                }else{
                    r.PB(v+1);
                    FOREACH(it,g[v])///
                        if(SIZE(g[it->v])!=1 && it->v!=p && g[it->v].t!=g[v].t-1)///
                            TraverseBranch(r,it->v,v,phase);///
                    FOREACH(it,g[v])///
                        if(SIZE(g[it->v])==1 && it->v!=p && g[it->v].t!=g[v].t-1)///
                            r.PB(it->v+1);///
                }
            }else if(c==3){
                if(!phase){
                    r.clear();///
                    puts("BRAK");///
                    return;///
                }
                bool ex=false;
                FOREACH(it,g[v])///
                    if(SIZE(g[it->v])==1 && it->v!=p && g[it->v].t!=g[v].t-1)///
                        r.PB(it->v+1);///
                FOREACH(it,g[v])///
                    if(SIZE(g[it->v])!=1 && it->v!=p && g[it->v].t!=g[v].t-1){///
                        TraverseBranch(r,it->v,v,phase);///
                        if(!ex){
                            r.PB(v+1);
                            ex=true;
                            phase=0;
                        }
                    }
            }else if(c==1){///
                phase=1;///
                r.PB(v+1);///
            }///
            else{///
                r.clear();///
                puts("BRAK");///
                return;///
            }///
        }
        p=v;///
        v=g[v].s;///
        c=TypeOfLayer(v,p);///
        if(c==1){///
            r.PB(v+1);///
        }else if(c==3 or c==0){///
            r.clear();///
            puts("BRAK");///
            return;///
        }else{///
            if(phase){///
                FOREACH(it,g[v])///
                    if(it->v!=p)///
                        if(SIZE(g[it->v])==1)///
                            r.PB(it->v+1);
                FOREACH(it,g[v])///
                    if(it->v!=p)///
                        if(SIZE(g[it->v])!=1)///
                            TraverseBranch(r,it->v,v,phase);
                r.PB(v+1);
            }else{///
                r.clear();///
                puts("BRAK");///
                return;///
            }///
        }
    }

    void Ans(){
        if(Check()){
            VI res;
            Findway(res);
            FOREACH(it,res)
                printf("%d\n",*it);
        }else{
            puts("BRAK");
        }
    }
};

struct Vs{
    int t,s;
};
struct Es{
};

int main(){
    scanf("%d",&n);
    Graph<Vs,Es> graf(n);
    REP(i,n-1){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        graf.EdgeD(a,b);
        graf.EdgeD(b,a);
    }
    graf.Ans();
    return 0;
}

