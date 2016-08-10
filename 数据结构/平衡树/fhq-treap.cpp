#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX(a,b) (((a)>(b))?(a):(b))
const int N(1e4);
class hh
{
	public:
		int key,val,sum,maxv,add,size;
		bool rev;
		hh* son[2];
		hh(int _key=0,int _val=0):key(_key),val(_val){rev=maxv=sum=size=add=0;}
		inline void push_down();
		inline void push_up();
}tree[N];
hh *root;
inline int random()
{
	static int seed(978263132);
	seed+=(seed<<2)+5;
	return seed;
}
inline hh* newnode(int key,int val)
{
	static int tot(0);
	hh* x(tree+(++tot));
	x->key=key;x->val=x->sum=x->maxv=val;
	x->son[0]=x->son[1]=tree;
	x->rev=x->add=0;
	x->size=1;
	return x;
}
inline void hh::push_down()
{
	if(this==tree)return;
	if(rev)swap(son[0],son[1]),rev=0;
	if(add)val+=add,maxv+=add,sum+=add*size;
}
inline void hh::push_up()
{
	if(this==tree)return;
	size=son[0]->size+son[1]->size+1;
	maxv=MAX(MAX(val,son[0]->maxv),son[1]->maxv);
}
inline hh* merge(hh* x,hh* y)
{
	if(x==tree||y==tree)return x!=tree?y:x;
	x->push_down();y->push_down();
	if(x->key<y->key){(x->son[1]=merge(x->son[1],y))->push_up();return x;}
	else{(x->son[0]=merge(x->son[0],y))->push_up();return y;}
}
inline void split(hh* x,int k,hh* &l,hh* &r)
{
	if(!k)l=tree,r=x;
	else if(k==x->size)l=x,r=tree;
	else
	{
		x->push_down();
		if(x->son[0]->size>=k)
		{
			r=x;
			split(x->son[0],k,x,r->son[0]);
		}
		else
		{
			l=x;
			split(x->son[1],k-(x->son[0]->size)-1,l->son[1],r);
			l->push_up();
		}
	}
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	root=tree;
	for(int i(1);i<=n;i++)
		root=merge(root,newnode(random(),0));
	while(m--)
	{
		int op,L,R,x;
		scanf("%d%d%d",&op,&L,&R);
		hh* l,r;
//		split(root,L-1,l,r);
		if(op==1)
		{
			
		}
		else;
	}
	return 0;
}
