#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define REP(x,e) for(int x=0;x<e;++x)
#define FOR(x,b,e) for(int x=b;x<=e;++x)
#define FORD(x,b,e) for(int x=b;x>=e;--x)

struct AVLNode{
    AVLNode* up,*left,*right;
    int key,bf,cnt;
};

void DFSRelease(AVLNode * v)
{
  if(v)
  {
    DFSRelease(v->left);
    DFSRelease(v->right);
    delete v;
  }
}

void cnt_act(AVLNode* v){
    v->cnt=0;
    if(v->right) v->cnt+=v->right->cnt+1;
    if(v->left) v->cnt+=v->left->cnt+1;
}

void RR(AVLNode* &root,AVLNode *A){
    AVLNode* B = A->right,*p=A->up;
    A->right=B->left;
    if(A->right) A->right->up=A;
    B->left=A;
    B->up=p;
    A->up=B;
    if(p){
        if(A==p->left) p->left=B; else p->right=B;
    }else root=B;
    if(B->bf==-1) A->bf=B->bf=0;
    else A->bf=-1,B->bf=1;
    cnt_act(A);
    cnt_act(B);
}

void LL(AVLNode * &root,AVLNode* A){
    AVLNode* B=A->left,*p=A->up;
    A->left=B->right;
    if(A->left) A->left->up=A;
    B->right = A;
    B->up=p;
    A->up=B;
    if(p){
        if(p->left==A) p->left=B; else p->right=B;
    }else root=B;
    if(B->bf==1) A->bf=B->bf=0;
    else A->bf=1,B->bf=-1;
    cnt_act(A);
    cnt_act(B);
}

void RL(AVLNode* &root,AVLNode *A){
    AVLNode* B = A->right,*C = B->left, *p = A->up;
    B->left=C->right;
    if(B->left) B->left->up=B;
    A->right=C->left;
    if(A->right) A->right->up=A;
    C->left=A;
    C->right=B;
    A->up=B->up=C;
    C->up=p;
    if(p){
        if(p->left==A) p->left=C;else p->right=C;
    }else root=C;
    if(C->bf==-1) A->bf=1; else A->bf=0;
    if(C->bf==1) B->bf=-1; else B->bf=0;
    C->bf=0;
    cnt_act(A);
    cnt_act(B);
    cnt_act(C);
}

void LR(AVLNode* &root,AVLNode* A){
    AVLNode* B=A->left,*C=B->right,*p=A->up;
    B->right=C->left;
    if(B->right) B->right->up=B;
    A->left=C->right;
    if(A->left) A->left->up=A;
    C->right=A;
    C->left=B;
    C->up=p;
    A->up=B->up=C;
    if(p){
        if(p->left==A) p->left=C; else p->right=C;
    }else root=C;
    if(C->bf==-1) B->bf=1; else B->bf=0;
    if(C->bf==1) A->bf=-1; else A->bf=0;
    C->bf=0;
    cnt_act(A);
    cnt_act(B);
    cnt_act(C);
}

void tree_act(AVLNode* v){
    while(v){
        cnt_act(v);
        v=v->up;
    }
}

void insertAVL(AVLNode * & root, int k){
  AVLNode * w,* p,* r;
  bool t;
  w = new AVLNode;
  w->left = w->right = w->up =  NULL;
  w->cnt = w->bf =0;
  w->key  = k;
  p = root;
  if(!p) root = w;
  else{
    while(true)
      if(k < p->key){
        if(!p->left){
          p->left = w;
          break;
        }
        p = p->left;
      }else{
        if(!p->right){
          p->right = w;
          break;
        }
        p = p->right;
      }
    w->up = p;
    p->cnt++;
    if(p->bf){ p->bf = 0;
        r=p->up;
        tree_act(r);
    }
    else{
      if(p->left == w)
        p->bf = 1;
      else
        p->bf = -1;
      r = p->up;
      t = false;
      while(r){
        if(r->bf){
          t = true;
          break;
        };
        if(r->left == p) r->bf =  1;
        else             r->bf = -1;
        p = r;
        cnt_act(r);
        r=r->up;
      }
      if(t){
        if(r->bf == 1){
          if(r->right == p) r->bf = 0;
          else if(p->bf == -1) LR(root,r);
          else                 LL(root,r);
        }else{
          if(r->left == p) r->bf = 0;
          else if(p->bf == 1) RL(root,r);
          else                RR(root,r);
        }
      }
      tree_act(r);
    }
  }
}

int cnt_greater(AVLNode* v,int k){
    int res=0;
    while(v){
        if(k>v->key){
            v=v->right;
        }else{
            if(v->right)
            res+=v->right->cnt+1;
            if(v->key>k) ++res;
            v=v->left;
        }
    }
    return res;
}

int n;
long long wynik;

struct node{
    node* left,*right;
    AVLNode* s;
    node() : left(NULL),right(NULL),s(NULL) {}
};

node* root;

long long DfsCompute(AVLNode* ro,AVLNode* v){
    long long res=0;
    res+=cnt_greater(ro,v->key);
    if(v->right)
        res+=DfsCompute(ro,v->right);
    if(v->left)
        res+=DfsCompute(ro,v->left);
    return res;
}

void DfsAdd(AVLNode* &ro,AVLNode* v){
    if(v->right)
        DfsAdd(ro,v->right);
    if(v->left)
        DfsAdd(ro,v->left);
    insertAVL(ro,v->key);
}

void Wczytaj(node* doc){
    int t;scanf("%d",&t);
    if(t==0){
        doc->right=new node;
        doc->left=new node;
        Wczytaj(doc->left);
        Wczytaj(doc->right);
        long long inv=0;
        long long l=doc->left->s->cnt+1,r=doc->right->s->cnt+1;
        if(doc->left->s->cnt < doc->right->s->cnt){
            doc->s=doc->right->s;
            inv=DfsCompute(doc->s,doc->left->s);
            DfsAdd(doc->s,doc->left->s);
            DFSRelease(doc->left->s);
        }else{
            doc->s=doc->left->s;
            inv=DfsCompute(doc->s,doc->right->s);
            DfsAdd(doc->s,doc->right->s);
            DFSRelease(doc->right->s);
        }
        wynik+=min(inv,r*l-inv);
    }else insertAVL(doc->s,t);
}

int main(){
    scanf("%d",&n);
    root = new node;
    Wczytaj(root);
    printf("%lld",wynik);
    return 0;
}
