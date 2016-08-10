#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N(3e5+200);
#define id(x) (tree+x)
struct hh{
    int val,sum,rev;
    hh *son[2],*pre;
    inline void push_down();
    inline void push_up();
    inline void sets(hh* x,int f){
        push_down();
        (son[f]=x)->pre=this;
        push_up();
    }
    inline int f(){return this==pre->son[1];}
    inline bool is_root(){return this!=pre->son[0]&&this!=pre->son[1];}
}tree[N],*pos[N];
int n,m,tot,a[N];
inline void hh::push_down(){
	if(this==id(0))return;
    if(rev){
        son[1]->rev^=1;son[0]->rev^=1;
        swap(son[1],son[0]);
        rev=0;
    }
}
inline void hh::push_up(){
    if(this!=id(0))sum=son[0]->sum^son[1]->sum^val;
}
inline hh* newnode(int val,hh* fa){
    tot++;
    hh* x=new hh;
    x->val=x->sum=val;x->rev=0;x->pre=fa;x->son[0]=x->son[1]=id(0);
    return x;
}
inline void rotate(hh* x){
    hh*const y=x->pre;
    if(!y->is_root())y->pre->push_down();
    y->push_down();x->push_down();
    int f(x->f());
    y->sets(x->son[!f],f);
    if(y->is_root())x->pre=y->pre;
    else y->pre->sets(x,y->f());
    x->sets(y,!f);
}
inline void splay(hh* x){
    for(;!x->is_root();rotate(x))
        if(x->pre->is_root());
        else if(x->f()==x->pre->f())rotate(x->pre);
        else rotate(x);
}
inline hh* assess(hh* x){
    hh* y(id(0));
    for(;x!=id(0);y=x,x=x->pre){
        splay(x);
        x->sets(y,1);
    }
    return y;
}
inline hh* evert(hh* x){
    assess(x)->rev^=1;
    splay(x);
}
inline hh* get_root(hh* x){
	for(x=assess(x);x->push_down(),x->son[0]!=id(0);x=x->son[0]);
    return x;
}
inline bool connect(hh* x,hh* y){
    hh* x2=get_root(y);
    hh* x1=get_root(x);
    return x1==x2;
}
inline void link(hh* x,hh* y){
    if(connect(x,y))return;
    evert(x);
    x->pre=y;
    assess(x);
}
inline void cut(hh* x,hh *y){
    if(!connect(x,y))return;
    evert(x);assess(y);
    splay(y);
    y->son[0]=x->pre=id(0);
    y->push_up();
}
inline int query(hh *x,hh *y){
	if(!connect(x,y))return 0;
    evert(x);assess(y);
    splay(y);return y->sum;
}
inline void modify(hh* x,int y){
    x->val=y;x->push_up();
    splay(x);
}
inline void read(int &x){
    char c=0;
    for(;c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+(c-'0');
}
int main(){
	id(0)->son[0]=id(0)->son[1]=id(0)->pre=id(0);id(0)->val=id(0)->sum=id(0)->rev=0;
    read(n);read(m);
    for(int i(1);i<=n;i++)read(a[i]),pos[i]=newnode(a[i],id(0));
    for(int op,x,y;m--;){
        read(op);read(x);read(y);
        switch(op){
            case 0:{printf("%d\n",query(pos[x],pos[y]));break;}
            case 1:{link(pos[x],pos[y]);break;}
            case 2:{cut(pos[x],pos[y]);break;}
            case 3:{modify(pos[x],y);break;}
        }
    }
    return 0;
}
