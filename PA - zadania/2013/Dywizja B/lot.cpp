#include <cstdio>
#include <iostream>

using namespace std;

#define FOR(x,b,e) for(int x=b;x<=e;x++)

#define MAX_N 500001

int n,r;
char lit[MAX_N];

int main(){
    scanf("%d",&n);
    scanf("%s",lit);
    FOR(i,0,n){
        int t=1;
        int j=i+1;
        while(j<n && lit[j]==lit[i])
        {
            ++t;
            ++j;
        }
        i=j-1;
        r+=t/2;
    }
    printf("%d",r);
    return 0;
}
