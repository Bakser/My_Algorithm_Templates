#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N(1e5+200);
typedef pair<int,int> pii;
#define id(x) (tree+x)
struct hh{
    hh *son[2],*pre;
    int size,val;
    bool rev;
    inline void push_down();
    inline void sets(hh* x,int f);
    inline int f();
    inline void push_up();
}tree[N],*root,*pos[N];
int n,a[N],tot;
pii b[N];
inline void hh::push_down(){
	if(this==id(0))return;
    if(rev){
        son[0]->rev^=1;son[1]->rev^=1;
        swap(son[0],son[1]);rev=0;
    }
}
inline void hh::sets(hh* x,int f){
    push_down();(son[f]=x)->pre=this;
    push_up();
}
inline void hh::push_up(){
    size=son[0]->size+son[1]->size+1;
}
inline int hh::f(){
    return this==pre->son[1];
}
inline hh* newnode(int val,hh* fa){
    tot++;id(tot)->val=val;
    id(tot)->pre=fa;id(tot)->size=1;id(tot)->rev=0; id(tot)->son[0]=id(tot)->son[1]=id(0);
    return id(tot);
}
inline hh* build(int l,int r,hh* fa){
	if(l>r)return id(0);
    if(l==r)return pos[a[l]]=newnode(a[l],fa);
    int mid(l+r>>1);
	hh* x=pos[a[mid]]=newnode(a[mid],fa);
    x->son[0]=build(l,mid-1,x);
	x->son[1]=build(mid+1,r,x);
	x->push_up();
    return x;
}
inline void rotate(hh* x){
    hh* y(x->pre);
    if(y->pre!=id(0))y->pre->push_down();
    y->push_down();
    x->push_down();
    int f(x->f());
    y->sets(x->son[!f],f);
    if(y->pre==id(0))x->pre=id(0);
    else y->pre->sets(x,y->f());
    x->sets(y,!f);
}
inline void splay(hh* x,const hh* goal){
    for(;x->pre!=goal;rotate(x))
        if(x->pre->pre==goal);
        else if(x->f()==x->pre->f())rotate(x->pre);
        else rotate(x);
    if(goal==id(0))root=x;
}
inline hh* select(int k){
    hh* x=root;
    while(x!=id(0)){
    	x->push_down();
        int tmp=x->son[0]->size;
        if(k==tmp+1)break;
        else if(k<=tmp)x=x->son[0];
        else k-=tmp+1,x=x->son[1];
    }
    return x;
}
inline void read(int &x){
    char c=0;
    for(;c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+(c-'0');
}
int main(){
    read(n);id(0)->size=0;
    for(int i(1);i<=n;i++)read(a[i]),b[i]=pii(a[i],i);
    sort(b+1,b+n+1);
	for(int i(1);i<=n;i++)a[b[i].second]=i;a[0]=a[n+1]=0;
    root=build(0,n+1,id(0));
    for(int i(1),ans;i<=n;i++){
        splay(pos[i],id(0));
        printf("%d",ans=pos[i]->son[0]->size);
        printf(i<n?" ":"\n");
        hh* x=select(ans+2);hh* y=select(i);
        splay(x,id(0));
        splay(y,root);
        root->son[0]->son[1]->rev^=1;
    }
    return 0;
}
