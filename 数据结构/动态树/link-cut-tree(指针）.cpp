//bzoj2631
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef unsigned int LL;
#define N 100010
#define MOD 51061
#define id(x) (lct+x)
template<class T>
T read(T &x)
{
	char c=0;x=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')(x*=10)+=(c-'0'),c=getchar();
	return x;
}
LL n;
struct hh
{
	hh *pre,*son[2];
	LL val,sum,size,add,mul;
	bool rev,empty;
	hh():empty(0),rev(0),val(1),sum(1),size(1),add(0),mul(1){}
	inline void refresh(int _add,LL _mul)
	{
		if(empty)return;
		val=(val*_mul+_add)%MOD;
		sum=(sum*_mul+_add*size)%MOD;
		mul=(mul*_mul)%MOD;
		add=(add*_mul+_add)%MOD;
	}
	inline void push_down()
	{
		if(empty)return;
		if(rev)
		{
			son[0]->rev^=1;
			son[1]->rev^=1;
			swap(son[0],son[1]);
			rev=0;
		}
		if(add!=0||mul!=1)
		{
			son[0]->refresh(add,mul);
			son[1]->refresh(add,mul);
		}
		add=0;
		mul=1;
	}
	inline void push_up()
	{
		if(empty)return;
		size=son[0]->size+1+son[1]->size;
		sum=(son[0]->sum+val+son[1]->sum)%MOD;
	}
	inline bool root()
	{
		return (pre->son[0]!=this&&pre->son[1]!=this);
	}
	inline void set(hh *x,int f)
	{
		push_down();
		(son[f]=x)->pre=this;
		push_up();
	}
	inline bool f()
	{
		return this==pre->son[1];
	}
}lct[N];
inline void rotate(hh *x)
{
	hh *y(x->pre);
	if(!y->root())y->pre->push_down();
	y->push_down();
	x->push_down();
	int f(x->f());
	y->set(x->son[!f],f);
	if(y->root())x->pre=y->pre;
	else y->pre->set(x,y->f());
	x->set(y,!f);
}
inline void splay(hh *x)
{
	for(;!x->root();rotate(x))
	if(x->pre->root());
	else if(x->f()==x->pre->f())rotate(x->pre);
	else rotate(x);
}
inline hh* access(hh* x)
{
	hh *y(lct);
	for(;x!=lct;y=x,x=x->pre)
	{
		splay(x);
		x->set(y,1);
	}
	return y;
}
inline void print(hh *x)
{
	if(x==lct)return;
	printf("%d %d %d\n",x-lct,x->val,x->sum);
	print(x->son[0]);
	print(x->son[1]);
}
inline void evert(hh* x)
{
	access(x)->rev^=1;
	splay(x);
}
int main()
{
	LL q;
	lct->pre=lct->son[0]=lct->son[1]=lct;
	lct->empty=1;lct->size=lct->val=lct->sum=0;
	read(n);read(q);
	for(int i=1;i<=n;i++)
		id(i)->pre=id(i)->son[0]=id(i)->son[1]=lct;
	for(LL i=1,u,v;i<n;i++)
	{
		read(u);read(v);
		evert(id(u));
		id(u)->pre=id(v);
	}
	while(q--)
	{
		char opt;
		LL u,v,x,y;
		scanf(" %c",&opt);
		evert(id(read(u)));read(v);
		if(opt=='/')printf("%u\n",access(id(v))->sum);
		else if(opt=='+')access(id(v))->refresh(read(x),1);
		else if(opt=='*')access(id(v))->refresh(0,read(x));
		else
		{
			read(x);read(y);
			access(id(v));
			splay(id(v));
			id(v)->son[0]=id(u)->pre=lct;
			id(v)->push_up();
			evert(id(x));
			id(x)->pre=id(y);
		}
	}
	return 0;
}
