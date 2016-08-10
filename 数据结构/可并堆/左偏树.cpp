//bzoj2809 
#include<cstdio>
#include<iostream>
#define N 100100
#define MAX(a,b) (((a)>(b))?(a):(b))
typedef unsigned long long LL;
template<class T>
T read(T &x)
{
	x=0;
	static char c(0);
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())(x*=10)+=c-'0';
	return x;
}
class node
{
	public:
		int val,dis,size;
		LL sum;
		node* son[2];
}*tree[N],hh[N];
struct db
{
	int next,v;
}edges[N];
int n,m,tot,point[N];
LL lead[N],ans(0);
inline void addedge(int u,int v)
{
	if(!u)return;
	static int en(0);
	edges[++en].next=point[u];edges[en].v=v;point[u]=en;
}
inline void newnode(node* &x,int val)
{
	x=hh+(++tot);
	x->sum=x->val=val;
	x->size=1;x->dis=0;
	x->son[0]=x->son[1]=hh;
}
inline node* merge(node* a,node* b)
{
	if(a==hh)return b;
	if(b==hh)return a;
	if(a->val<b->val)std::swap(a,b);
	a->son[1]=merge(a->son[1],b);
	if(a->son[0]->dis<a->son[1]->size)
		std::swap(a->son[0],a->son[1]);
	a->dis=a->son[1]->dis+1;
	a->sum=a->son[0]->sum+a->son[1]->sum+a->val;
	a->size=a->son[0]->size+a->son[1]->size+1;
	return a;
}
inline node* dfs(int u)
{
	for(int i=point[u];i;i=edges[i].next)
		tree[u]=merge(tree[u],dfs(edges[i].v));
	while((tree[u]->sum)>m)
		tree[u]=merge(tree[u]->son[0],tree[u]->son[1]);
	ans=MAX(ans,lead[u]*tree[u]->size);
	return tree[u];
}
int main()
{
	read(n);read(m);
	hh->sum=hh->val=hh->size=0;hh->dis=-1;
	hh->son[0]=hh->son[1]=hh;
	for(int i=1,tmp;i<=n;i++)
	{
		addedge(read(tmp),i);
		newnode(tree[i],read(tmp));
		read(lead[i]);
	}
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
