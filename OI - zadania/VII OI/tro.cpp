#include <iostream>
#include <vector>

using namespace std;

#define MAXN 360001

struct wyn{
    int x,y,z;
    wyn(int x,int y, int z) : x(x),y(y),z(z) {}
};

bool wag[MAXN];
vector<wyn> res;
int main()
{
    ios_base::sync_with_stdio(0);
    int p,q,n;
    cin>>p>>q>>n;
    int akt=1;
    while(akt<=n){
        if(!wag[akt]){
        if(!wag[akt+min(p,q)]){
            res.push_back(wyn(akt,akt+min(p,q),akt+p+q));
            wag[akt]=wag[akt+min(p,q)]=wag[akt+p+q]=1;
            akt++;
        }else if(!wag[akt+max(p,q)]) {
            res.push_back(wyn(akt,akt+max(p,q),akt+q+p));
            wag[akt]=wag[akt+max(p,q)]=wag[akt+p+q]=1;
            akt++;
        }else akt++;
        }else akt++;
    }
    cout<<res.size()<<endl;
    for(int i=0;i<res.size();i++)
        cout<<res[i].x<<" "<<res[i].y<<" "<<res[i].z<<endl;
    return 0;
}
