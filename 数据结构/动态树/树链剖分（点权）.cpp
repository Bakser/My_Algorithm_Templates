//zkw线段树 bzoj1036 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 40100
#define INF 0x3f3f3f3f
#define MAX(a,b) (((a)>(b))?(a):(b))
struct hh
{
	int v,next;
}edges[N<<1];
struct seg_tree
{
	int maxx,sum;
}tree[N<<4];
int n,point[N],fir[N],top[N],size[N],fa[N],dep[N],tid[N],son[N],en,end,h,M;
char str[90];
bool flag;
inline void addedge(int u,int v)
{
	edges[++en].next=point[u];
	point[u]=en;
	edges[en].v=v;
}
inline void dfs(int x)
{
	size[x]=1;son[x]=0;
	for(int i=point[x];i!=-1;i=edges[i].next)
	if(edges[i].v!=fa[x]){
		dep[edges[i].v]=dep[x]+1;
		fa[edges[i].v]=x;
		dfs(edges[i].v);
		if(size[edges[i].v]>size[son[x]])son[x]=edges[i].v;
		size[x]+=size[edges[i].v];
	}
}
inline void make(int x,int anc)
{
	top[x]=anc;tid[x]=++end;/**/tree[end+M].sum=tree[end+M].maxx=fir[x];/*一处不同 */
	if(son[x]!=0)make(son[x],anc);
	for(int i=point[x];i!=-1;i=edges[i].next)
	if(edges[i].v!=fa[x]&&edges[i].v!=son[x])
	make(edges[i].v,edges[i].v);
}
inline void build()
{
	for(int i=M;i>=1;i--)
	{
		tree[i].sum=tree[i<<1].sum+tree[i<<1^1].sum;
		tree[i].maxx=MAX(tree[i<<1].maxx,tree[i<<1^1].maxx);
	}
}
inline void update(int x,int val)
{
	x+=M;
	tree[x].sum=tree[x].maxx=val;
	x>>=1;
	for(;x;x>>=1)
	{
		tree[x].sum=tree[x<<1].sum+tree[x<<1^1].sum;
		tree[x].maxx=MAX(tree[x<<1].maxx,tree[x<<1^1].maxx);
	}
}
inline int query(int s,int t)
{
	int res=0;
	if(flag)res=-INF;
	for(s=s+M-1,t=t+M+1;s^t^1;s>>=1,t>>=1)
	{
		if(~s&1){
			if(flag)res=MAX(res,tree[s^1].maxx);
			else res+=tree[s^1].sum;
		}
		if(t&1)
		{
			if(flag)res=MAX(res,tree[t^1].maxx);
			else res+=tree[t^1].sum;
		}
	}
	return res;
}
inline int ask(int x,int y)
{
	int f1=top[x],f2=top[y],res=0;
	if(flag)res=-INF;
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2]){swap(f1,f2);swap(x,y);}
		int tmp=query(tid[f1],tid[x]);
		if(flag)res=MAX(tmp,res);
		else res+=tmp;
		x=fa[f1];f1=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	int tmp=query(tid[x],tid[y]);//与边权的一处不同 边权:query(tid[son[x]],tid[y]); 
	if(flag)res=MAX(tmp,res);
	else res+=tmp;
	return res;
}
int main()
{
	scanf("%d",&n);
	memset(point,0xff,sizeof(point));
	en=-1;end=0;
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	for(int i=1;i<=n;i++)
	scanf("%d",&fir[i]);
	while((1<<h)-2<=n)h++;
	M=(1<<h)-1;
	dep[1]=0;fa[1]=0;
	dfs(1);
	make(1,1);
	build();
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int a,b;
		scanf(" %s%d%d",str,&a,&b);
		if(str[0]=='C')update(tid[a],b);
		if(str[0]=='Q')
		{
			if(str[1]=='M')flag=true,printf("%d\n",ask(a,b));
			if(str[1]=='S')flag=false,printf("%d\n",ask(a,b));
		}
	}
	return 0;
}
