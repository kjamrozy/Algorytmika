#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)
#define VAR(v,n) __typeof(n) v = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(x) ((int)(x).size())
#define ST first
#define ND second
#define PB push_back

typedef long long LL;

struct Point{
    int x,y;
    Point(int x=0,int y=0) : x(x),y(y) {}
};

struct Node{
    int x,y;//num - indeks na liscie przeciec
    int* moj,*pol;//dowiazania z indeksami
    bool wej;//0 - wyjscie, 1 - wejscie do srodka prostokata
    Node(int x=0,int y=0,bool wej=false) : x(x),y(y),moj(NULL),pol(NULL),wej(wej) {}
};

const int N = 5001;

vector<Node> obwod;//punkty przeciec na obwodzie
int x1,x2,y1,y2,l,n,res,dow[2*N],u;
Point p[N];
bool vs[2*N];

int Bok(Point a){//funkcja okreslajaca na ktorym boku lezy wierzcholek, zakladamy, ze nie dostajemy wierzcholkow bedacych wierzcholkami wielokata
    if(a.x==x1){
        return 3;
    }else if(a.x==x2){
        return 1;
    }else if(a.y==y1){
        return 2;
    }else if(a.y==y2){
        return 0;
    }
}

bool NaObwodzie(Node a,Node b){//pomocnicza funkcja do porownywania
    int x=Bok(Point(a.x,a.y));
    if(x==0){
        return a.x<b.x;
    }else if(x==1){
        return a.y>b.y;
    }else if(x==2){
        return a.x>b.x;
    }else{
        return a.y<b.y;
    }
}

bool cmp(const Node& a,const Node& b){//sortuje wierzcholki zgodnie z ich kolejnoscia na obwodzie
    return (Bok(Point(a.x,a.y))==Bok(Point(b.x,b.y))) ? (NaObwodzie(a,b)) : Bok(Point(a.x,a.y))<Bok(Point(b.x,b.y));
}

LL det(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

bool Outside(Point a){
    if(det(Point(x1,y2),a,Point(x2,y2))<0) return 1;
    if(det(Point(x2,y2),a,Point(x2,y1))<0) return 1;
    if(det(Point(x2,y1),a,Point(x1,y1))<0) return 1;
    if(det(Point(x1,y1),a,Point(x1,y2))<0) return 1;
    return 0;
}

bool Test1(){//sprawdza czy wielokat zawiera sie calkowicie w
    REP(i,n)
        if(Outside(p[i])) return false;
    return true;
}

bool Test2(){//sprawdza czy prostokat zawiera sie calkowicie w wielokacie
    REP(i,n){
        if(det(p[i],Point(x1,y1),p[(i+1)%n])>0) return false;
        if(det(p[i],Point(x1,y2),p[(i+1)%n])>0) return false;
        if(det(p[i],Point(x2,y1),p[(i+1)%n])>0) return false;
        if(det(p[i],Point(x2,y2),p[(i+1)%n])>0) return false;
    }
    return true;
}


bool Zawiera(Point a){
    REP(i,n)
         if(det(p[i],Point(x1,y1),p[(i+1)%n])>0) return false;
    return true;
}

bool NaOdcinku(Point& p1,Point& p2,Point& p3){
    if (min(p1.x,p2.x)<=p3.x && p3.x<=max(p1.x,p2.x) && min(p1.y,p2.y)<=p3.y && p3.y<=max(p1.y,p2.y))
        return true;
    else return false;
}

bool Przecina(Point a,Point b,Point c,Point d){//sprawdzam czy odc ab, przecina odcinek cd
    LL  d1=det(c,d,a),
        d2=det(c,d,b),
        d3=det(a,b,c),
        d4=det(a,b,d);
    if( ((d1<0 && d2>0) || (d1>0 && d2<0)) && ((d3<0 && d4>0) || (d3>0 && d4<0))) return true;
    else if(d1==0 && NaOdcinku(c,d,a))
        return true;
    else if(d2==0 && NaOdcinku(c,d,b))
        return true;
    else if(d3==0 && NaOdcinku(a,b,c))
        return true;
    else if(d4==0 && NaOdcinku(a,b,d))
        return true;
    return false;
}

bool Przecina0(Point a,Point b){
    return (Przecina(a,b,Point(x1,y2),Point(x2,y2))  && a.x!=x1 && a.x!=x2);
}

bool Przecina1(Point a,Point b){
    return (Przecina(a,b,Point(x2,y2),Point(x2,y1))  && a.y!=y1 && a.y!=y2);
}

bool Przecina2(Point a,Point b){
    return (Przecina(a,b,Point(x2,y1),Point(x1,y1))  && a.x!=x1 && a.x!=x2);
}

bool Przecina3(Point a,Point b){
    return (Przecina(a,b,Point(x1,y1),Point(x1,y2))  && a.y!=y1 && a.y!=y2);
}

int Solve(){
    u=-1;
    res=0;
    if(Test1() or Test2()){
        return 1;
    }
    int fi=-1;//fi - jakikolwiek wierzcholek lezacy poza prostokatem, na pewno istnieje taki
    REP(i,n)
        if(Outside(p[i])){
            fi=i;
            break;
        }
    bool faza=0;//poczatkowo jestesmy poza prostokatem - faza - 0
    Node* a=NULL,*ap=NULL;
    REP(i,n){//petla przechodzaca po wierzcholkach i dodajaca wierzcholki grafowe,zaczynamy od fi
        int x=(fi+i)%n;//aktualny wierzcholek
        if(p[x].x==p[(x+1)%n].x){//odcinek pionowy
            if(p[x].y<p[(x+1)%n].y){//idziemy w gore
                if(faza){
                    if(Przecina0(p[x],p[(x+1)%n]) && max(p[x].y,p[(x+1)%n].y)>=y2 ){
                        ap=new Node;
                        ap->x=p[x].x;ap->y=y2;
                        ap->wej=true;
                        a->moj=ap->pol=&dow[++u];
                        a->pol=ap->moj=&dow[++u];
                        obwod.PB(*a);
                        obwod.PB(*ap);
                        delete a;delete ap;
                        a=ap=NULL;
                        faza=0;
                    }
                }else{
                    if(Przecina2(p[x],p[(x+1)%n]) && max(p[x].y,p[(x+1)%n].y)>y1){
                        a=new Node;
                        a->x=p[x].x;a->y=y1;
                        faza=1;
                        if(Przecina0(p[x],p[(x+1)%n]) && max(p[x].y,p[(x+1)%n].y)>=y2){
                            ap=new Node;
                            ap->x=p[x].x;ap->y=y2;
                            ap->wej=true;
                            a->moj=ap->pol=&dow[++u];
                            a->pol=ap->moj=&dow[++u];
                            obwod.PB(*a);
                            obwod.PB(*ap);
                            delete a;delete ap;
                            a=ap=NULL;
                            faza=0;
                        }
                    }
                }
            }else{//idziemy w dol
                if(faza){
                    if(Przecina2(p[x],p[(x+1)%n]) && min(p[x].y,p[(x+1)%n].y)<=y1){
                        ap=new Node;
                        ap->x=p[x].x;ap->y=y1;
                        ap->wej=true;
                        a->moj=ap->pol=&dow[++u];
                        a->pol=ap->moj=&dow[++u];
                        obwod.PB(*a);
                        obwod.PB(*ap);
                        delete a;delete ap;
                        a=ap=NULL;
                        faza=0;
                    }
                }else{
                    if(Przecina0(p[x],p[(x+1)%n]) && min(p[x].y,p[(x+1)%n].y)<y2){
                        a=new Node;
                        a->x=p[x].x;a->y=y2;
                        faza=1;
                        if(Przecina2(p[x],p[(x+1)%n] )&& min(p[x].y,p[(x+1)%n].y)<=y1){
                            ap=new Node;
                            ap->x=p[x].x;ap->y=y1;
                            ap->wej=true;
                            a->moj=ap->pol=&dow[++u];
                            a->pol=ap->moj=&dow[++u];
                            obwod.PB(*a);
                            obwod.PB(*ap);
                            delete a;delete ap;
                            a=ap=NULL;
                            faza=0;
                        }
                    }
                }
            }
        }else{//w inym wypadku jest to odc. poziomy
          if(p[x].x<p[(x+1)%n].x){//idziemy w prawo
                if(faza){
                    if(Przecina1(p[x],p[(x+1)%n]) && max(p[x].x,p[(x+1)%n].x)>=x2){
                        ap=new Node;
                        ap->y=p[x].y;ap->x=x2;
                        ap->wej=true;
                        a->moj=ap->pol=&dow[++u];
                        a->pol=ap->moj=&dow[++u];
                        obwod.PB(*a);
                        obwod.PB(*ap);
                        delete a;delete ap;
                        a=ap=NULL;
                        faza=0;
                    }
                }else{
                    if(Przecina3(p[x],p[(x+1)%n]) && max(p[x].x,p[(x+1)%n].x)>x1){
                        a=new Node;
                        a->y=p[x].y;a->x=x1;
                        faza=1;
                        if(Przecina1(p[x],p[(x+1)%n]) && max(p[x].x,p[(x+1)%n].x)>=x2){
                            ap=new Node;
                            ap->y=p[x].y;ap->x=x2;
                            ap->wej=true;
                            a->moj=ap->pol=&dow[++u];
                            a->pol=ap->moj=&dow[++u];
                            obwod.PB(*a);
                            obwod.PB(*ap);
                            delete a;delete ap;
                            a=ap=NULL;
                            faza=0;
                        }
                    }
                }
            }else{//idziemy w lewo
                if(faza){
                    if(Przecina3(p[x],p[(x+1)%n]) && min(p[x].x,p[(x+1)%n].x)<=x1){
                        ap=new Node;
                        ap->y=p[x].y;ap->x=x1;
                        ap->wej=true;
                        a->moj=ap->pol=&dow[++u];
                        a->pol=ap->moj=&dow[++u];
                        obwod.PB(*a);
                        obwod.PB(*ap);
                        delete a;delete ap;
                        a=ap=NULL;
                        faza=0;
                    }
                }else{
                    if(Przecina1(p[x],p[(x+1)%n]) && min(p[x].x,p[(x+1)%n].x)<x2){
                        a=new Node;
                        a->y=p[x].y;a->x=x2;
                        faza=1;
                        if(Przecina3(p[x],p[(x+1)%n]) && min(p[x].x,p[(x+1)%n].x)<=x1){
                            ap=new Node;
                            ap->y=p[x].y;ap->x=x1;
                            ap->wej=true;
                            a->moj=ap->pol=&dow[++u];
                            a->pol=ap->moj=&dow[++u];
                            obwod.PB(*a);
                            obwod.PB(*ap);
                            delete a;delete ap;
                            a=ap=NULL;
                            faza=0;
                        }
                    }
                }
            }
        }
    }
    sort(obwod.begin(),obwod.end(),cmp);
    l=SIZE(obwod);
    REP(i,l)
        *obwod[i].moj=i;
    REP(i,l){
        if(!vs[i] && !obwod[i].wej){
            ++res;
            vs[i]=true;
            int v=*obwod[i].pol;
            vs[v]=true;
            v=*obwod[v].moj-1;
            v%=l;
            if(v<0) v+=l;
            while(v!=i){//kiedys tu w koncu wroce
                vs[v]=true;
                v=*obwod[v].pol;
                vs[v]=true;
                v=*obwod[v].moj-1;
                v%=l;
                if(v<0) v+=l;
            }
        }
    }
    return res;
}

int main(){
    scanf("%d%d%d%d%d",&x1,&y2,&x2,&y1,&n);
    REP(i,n)
        scanf("%d%d",&p[i].x,&p[i].y);
    printf("%d",Solve());
}
