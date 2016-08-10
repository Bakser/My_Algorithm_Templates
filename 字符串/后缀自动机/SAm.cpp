#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N(1e5);
struct sam_node
{
	sam_node *pre,*son[27];
	int val;
}sam[N<<1],*root,*last;
int n,tot;
inline sam_node* newnode(int val)
{
	sam_node* x=sam+(++tot);
	x->val=val;
	return x;
}
inline void add(int x)
{
	sam_node *p=last,*np=newnode(p->val+1);
	for(;p&&!p->son[x];p=p->pre)p->son[x]=np;
	if(!p)np->pre=root;
	else
	{
		sam_node *q=p->son[x];
		if(p->val+1==q->val)np->pre=q;
		else
		{
			sam_node *nq=newnode(p->val+1);
			memcpy(nq->son,q->son,sizeof(q->son));
			nq->pre=q->pre;
			q->pre=np->pre=nq;
			for(;p&&p->son[x]==q;p=p->pre)p->son[x]=nq;
		}
	}
	last=np;
}
int main()
{
	return 0;
}

